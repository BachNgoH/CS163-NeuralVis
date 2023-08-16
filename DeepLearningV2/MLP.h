//
// Created by LENOVO on 7/19/2023.
//
#pragma once

#ifndef NEURALVISUALIZER_MLP_H
#define NEURALVISUALIZER_MLP_H
#include <fstream>
#include <iostream>
#include "../Eigen/Dense"
#include <utility>
#include <vector>
using namespace Eigen;

namespace  nn {
    inline auto sigmoid(MatrixXd &x){
        for(int i = 0; i < x.rows(); i++)
            for(int j = 0; j < x.cols(); j++)
                x(i, j) = 1.0f / (1 + exp(-x(i, j)));

        return x;
    }

    inline auto d_sigmoid(MatrixXd x){
        MatrixXd res(x.rows(), x.cols());
        for(int i = 0; i < x.rows(); i++)
            for(int j = 0; j < x.cols(); j++)
                res(i, j) = x(i, j) * (1 - x(i, j));

        return res;
    }

    inline auto softmax(MatrixXd x){
        MatrixXd res(x.rows(), x.cols());
        for(int i = 0; i < x.cols(); i++){
            double expSum = 0.0;
            for(int j = 0; j < x.rows(); j++)
                expSum += exp(x(j, i));

            for(int j = 0; j < x.rows(); j++)
                res(j, i) = exp(x(j, i)) / expSum;
        }
        return res;
    }

    class MLP {
    public:
        std::vector<int> units_per_layer;
        std::vector<MatrixXd> bias;
        std::vector<MatrixXd> weights;
        std::vector<MatrixXd> activations;
        std::vector<MatrixXd> gradient;

        float lr;

        MLP(): units_per_layer(), weights(), bias(), activations(), lr() {}
        MLP(std::vector<int> units_per_layer, float lr=.001f) :
            units_per_layer(units_per_layer),
            weights(),
            bias(),
            activations(),
            lr(lr) {

            for(size_t i = 0; i < units_per_layer.size() - 1; i++){
                int in_channels = units_per_layer[i];
                int out_channels = units_per_layer[i+1];

                auto w = MatrixXd::Random(out_channels, in_channels);
                weights.push_back(w);

                auto b = MatrixXd::Random(out_channels, 1);
                bias.push_back(b);

                activations.resize(units_per_layer.size());
            }
        }

        double crossEntropyLoss(MatrixXd y_hat, MatrixXd y){
            double loss = 0.0;
            for(int i = 0; i < y.cols(); i++) {
                for(int j = 0; j < y.rows(); j++){
                    if(y(j, i) == 1.0)
                        loss += -log(y_hat(j, i));
                    else if(y(j, i) != 0.0)
                        throw std::runtime_error("True probabilities should be either 0 or 1.");
                }
            }
            return loss;
        }

        auto init_model(std::vector<int> units_per_layer, float lr=.001f){
            this->units_per_layer = units_per_layer;
            weights.clear();
            bias.clear();
            this->lr = lr;
            for(size_t i = 0; i < units_per_layer.size() - 1; i++){
                int in_channels = units_per_layer[i];
                int out_channels = units_per_layer[i+1];

                auto w = MatrixXd::Random(out_channels, in_channels);
                weights.push_back(w);

                auto b = MatrixXd::Random(out_channels, 1);
                bias.push_back(b);

                activations.resize(units_per_layer.size());
            }
        }

        auto forward(MatrixXd &x){
            activations[0] = x;
            auto prev = x;
            for(int i = 0; i < units_per_layer.size() - 1; ++i){
                MatrixXd y = weights[i] * prev;
                for(int k = 0; k < y.cols(); k++)
                    y.col(k) += bias[i];

                y = sigmoid(y);
                activations[i+1] = y;
                prev = y;
            }
            return prev;
        }

        double backward(MatrixXd target){
            MatrixXd y_hat = activations.back();
            MatrixXd error = target - y_hat;
            double loss = crossEntropyLoss(y_hat, target);
            gradient.resize(weights.size());
            for (int i = weights.size() - 1; i >= 0; i--){
                auto Wt = weights[i].transpose();

                auto prev_error = Wt * error;
                MatrixXd d_outputs = d_sigmoid(activations[i + 1]);

                MatrixXd gradients = error.cwiseProduct(d_outputs);
                gradients = gradients * lr;
                MatrixXd a_trans = activations[i].transpose();
                MatrixXd weight_gradients = gradients * a_trans;
                gradient[i] = weight_gradients;

                for(int k = 0; k < gradients.cols(); k++)
                    bias[i] = bias[i] + gradients.col(k);
                weights[i] = weights[i] + weight_gradients;
                error = prev_error;
            }
            return loss;
        }

        void save_weights(const std::string& filename) {
            std::ofstream file(filename, std::ios::binary);
            if (!file.is_open()) {
                std::cerr << "Error opening file for writing: " << filename << std::endl;
                return;
            }
            for (size_t i = 0; i < weights.size(); i++) {
                file.write((char*)weights[i].data(), sizeof(double) * weights[i].size());
            }

            for (size_t i = 0; i < bias.size(); i++) {
                file.write((char*)bias[i].data(), sizeof(double) * bias[i].size());
            }

            file.close();
        }

        // Function to load the model weights from a file
        void load_weights(const std::string& filename) {
            std::ifstream file(filename, std::ios::binary);
            if (!file.is_open()) {
                std::cerr << "Error opening file for reading: " << filename << std::endl;
                return;
            }

            for (size_t i = 0; i < weights.size(); i++) {
                file.read((char *) weights[i].data(), sizeof(double) * weights[i].size());
            }

            for (size_t i = 0; i < bias.size(); i++) {
                file.read((char*)bias[i].data(), sizeof(double) * bias[i].size());
            }
            std::cout << "LOAD MODEL SUCCESSFULLY" << std::endl;
            file.close();
        }
    };
}

#endif //NEURALVISUALIZER_MLP_H
