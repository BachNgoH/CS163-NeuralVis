#include <iostream>
#include "Eigen/Dense"
#include "DeepLearning/Tensor.h"
//#include "DeepLearning/MLP.h"
#include "utils.h"
#include "DeepLearning/Loss.h"
#include "DeepLearningV2/MLP.h"

using namespace std;

auto make_model(int in_channels,
                int out_channels,
                int hidden_units_per_layer,
                int hidden_layers,
                float lr) {
    vector<int> units_per_layer;
    units_per_layer.push_back(in_channels);
    for(int i = 0; i < hidden_layers; i++)
        units_per_layer.push_back(hidden_units_per_layer);

    units_per_layer.push_back(out_channels);
    nn::MLP model(units_per_layer, 0.001f);
    return model;
}

int argmax(MatrixXd x, int col){
    int maxIdx = 0;
    double maxVal = x(0, col);
    for(int i = 1; i < x.rows(); i++){
        if(x(i, col) > maxVal){
            maxVal = x(i, col);
            maxIdx = i;
        }
    }
    return maxIdx;
}

double get_accuracy(MatrixXd pred, MatrixXd label){
    double acc = 0.0;
    for(int i = 0; i < pred.cols(); i++){
        acc += argmax(pred, i) == argmax(label, i);
    }
    return acc;
}

int main() {
    int batch_size = 128;
    MNISTDataset dataset(batch_size);

    int in_channels = 784, out_channels = 10;
    int hidden_units_per_layer = 32, hidden_layers = 3;
    float lr{0.001f};

    auto model = make_model(
            in_channels,
            out_channels,
            hidden_units_per_layer,
            hidden_layers,
            lr);
    int max_iter = 100;


    for (int i = 0; i < max_iter; i++){
        double epoch_loss = 0.0;
        double epoch_acc = 0.0;
        for(int batch_idx = 0; batch_idx < dataset.num_lines / dataset.batch_size; batch_idx++){
        //for(int batch_idx = 0; batch_idx < 5000 / 64; batch_idx++){
            auto batch_data = dataset.loadData(batch_idx);
            MatrixXd x = get<0>(batch_data).transpose();
            MatrixXd label = get<1>(batch_data).transpose();
            MatrixXd y_hat = model.forward(x);
            double loss = model.backward(label);
            double accuracy = get_accuracy(y_hat, label);
            epoch_loss += loss;
            epoch_acc += accuracy;
        }
        model.save_weights("../checkpoint/model_weights.bin");
        cout << "EPOCH [" << i << "] " << "LOSS [" << epoch_loss / dataset.num_lines << "], ACC [" << epoch_acc / dataset.num_lines << "]" << endl;
    }


    return 0;
}
