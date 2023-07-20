//
// Created by LENOVO on 7/12/2023.
//

#ifndef NEURALVISUALIZER_LOSS_H
#define NEURALVISUALIZER_LOSS_H
#include "../Eigen/Dense"
#include "Tensor.h"
#include <cmath>
#include <vector>
#include "Dependency.h"

class CrossEntropyWithLogits {
public:

    Tensor get_loss(const Tensor &logits, MatrixXd labels) const {
        MatrixXd y_hat = MatrixXd(logits.data.rows(), logits.data.cols());
        for(int i = 0; i < logits.data.rows(); i++){
            double sum = 0;
            for(int j = 0; j < logits.data.cols(); j++){
                sum += exp(logits.data(i, j));
            }
            for(int j = 0; j < logits.data.cols(); j++){
                y_hat(i, j) = exp(logits.data(i, j)) / sum;
            }
        }

        MatrixXd loss_data = MatrixXd(logits.data.rows(), 1);
        for(int i = 0; i < logits.data.rows(); i++){
            int label = static_cast<int>(labels(i, 0));
            loss_data(i, 0) = log(y_hat(i, label));
        }
        bool requires_grad = logits.requires_grad;
        vector<Dependency*> depends_on;

        if(requires_grad){
            function<MatrixXd(const MatrixXd &)> grad_fn = [&](const MatrixXd& grad) -> MatrixXd {

                MatrixXd y_hat = MatrixXd(logits.data.rows(), logits.data.cols());
                for(int i = 0; i < logits.data.rows(); i++){
                    double sum = 0;
                    for(int j = 0; j < logits.data.cols(); j++){
                        sum += exp(logits.data(i, j));
                    }
                    for(int j = 0; j < logits.data.cols(); j++){
                        y_hat(i, j) = exp(logits.data(i, j)) / sum;
                    }
                }
                cout << "GRAD: (" << grad.rows() << ", " << grad.cols() << ")" << endl;
                cout << "Y_HAT: (" << y_hat.rows() << ", " << y_hat.cols() << ")" << endl;
                cout << "LABEL: (" << labels.rows() << ", " << labels.cols() << ")" << endl;

                MatrixXd grad_updated(y_hat.rows(), y_hat.cols());
                for(int i = 0; i < y_hat.cols(); i++){
                    if (labels(0,0) == i)
                        grad_updated(0, i) = grad(0,0) * (y_hat(0, i) - 1);
                    else
                        grad_updated(0, i) = grad(0,0) * (y_hat(0, i));
                }
                cout << "Grad update: (" << grad_updated.rows() << ", " << grad_updated.cols() << ")" << endl;
                return grad_updated;
            };
            depends_on.push_back(new Dependency(logits, grad_fn));
        }
        return Tensor(loss_data, requires_grad, depends_on);
    }
};

#endif //NEURALVISUALIZER_LOSS_H
