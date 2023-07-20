//
// Created by LENOVO on 7/9/2023.
//

#include "Activations.h"
#include "Dependency.h"
#include <vector>
#include <functional>

Tensor Identity::activation(const Tensor &x) const {
    MatrixXd data = x.data;
    bool requires_grad = x.requires_grad;
    vector<Dependency*> depends_on;

    if (requires_grad) {
        function<MatrixXd(const MatrixXd &)> grad_fn = [&](const MatrixXd &grad) -> MatrixXd {
            MatrixXd grad_updated = grad;
            return grad_updated;
        };
        depends_on.push_back(new Dependency(x, grad_fn));
    }

    return Tensor(data, requires_grad, depends_on);
}

Tensor Relu::activation(const Tensor &x) const{
    MatrixXd data(x.data.rows(), x.data.cols());
    for (int i = 0; i < x.data.rows(); i++){
        for(int j = 0; j < x.data.cols(); j++){
            data(i, j) = max(0.0, x.data(i,j));
        }
    }

    bool requires_grad = x.requires_grad;
    vector<Dependency*> depends_on;

    if (requires_grad) {
        function<MatrixXd(const MatrixXd &)> grad_fn = [&](const MatrixXd &grad) -> MatrixXd {
            MatrixXd grad_updated(grad.rows(), grad.cols());
            for(int i = 0; i < grad.rows(); i++)
                for(int j = 0; j < grad.cols(); j++)
                    grad_updated(i, j) = max(0.0, grad(i, j));
            return grad_updated;
        };
        depends_on.push_back(new Dependency(x, grad_fn));
    }
    return Tensor(data, requires_grad, depends_on);
}

Tensor Sigmoid::activation(const Tensor &x) const{
    MatrixXd data(x.data.rows(), x.data.cols());
    for(int i = 0; i < x.data.rows(); i++){
        for(int j = 0; j < x.data.cols(); j++){
            data(i, j) = 1.0 / (1 + exp(-x.data(i, j)));
        }
    }
    bool requires_grad = x.requires_grad;
    vector<Dependency*> depends_on;

    if (requires_grad) {
        function<MatrixXd(const MatrixXd &)> grad_fn = [&](const MatrixXd& grad) -> MatrixXd {
            MatrixXd grad_updated(grad.rows(), grad.cols());
            for (int i = 0; i < grad.rows(); i++) {
                for(int j = 0; j < grad.cols(); j++){
                    grad_updated(i, j) = grad(i, j) * (1.0 - grad(i, j));
                }
            }
            return grad_updated;
        };
        depends_on.push_back(new Dependency(x, grad_fn));
    }
    return Tensor(data, requires_grad, depends_on);
}

Tensor Tanh::activation(const Tensor &x) const{
    MatrixXd data(x.data.rows(), x.data.cols());
    for(int i = 0; i < x.data.rows(); i++){
        for(int j = 0; j < x.data.cols(); j++){
            data(i, j) = (exp(x.data(i, j)) - exp(-x.data(i, j))) /
                    (exp(x.data(i, j)) + exp(-x.data(i, j)));
        }
    }
    bool requires_grad = x.requires_grad;
    vector<Dependency*> depends_on;

    if (requires_grad) {
        function<MatrixXd(const MatrixXd &)> grad_fn = [&](const MatrixXd &grad) -> MatrixXd {
            MatrixXd grad_updated(grad.rows(), grad.cols());

            for (int i = 0; i < grad.rows(); i++) {
                for(int j = 0; j < grad.cols(); j++){
                    grad_updated(i, j) = 1 - pow(data(i, j) = (exp(grad(i, j)) - exp(-grad(i, j))) /
                                                      (exp(grad(i, j)) + exp(-grad(i, j))), 2);
                }
            }
            return grad_updated;
        };
        depends_on.push_back(new Dependency(x, grad_fn));
    }
    return Tensor(data, requires_grad, depends_on);
}

Tensor SoftPlus::activation(const Tensor &x) const {
    MatrixXd data(x.data.rows(), x.data.cols());
    for(int i = 0; i < x.data.rows(); i++){
        for(int j = 0; j < x.data.cols(); j++){
            data(i, j) = log(1.0 + exp(x.data(i, j)));
        }
    }
    bool requires_grad = x.requires_grad;
    vector<Dependency*> depends_on;

    if (requires_grad){
        function<MatrixXd(const MatrixXd &)> grad_fn = [&](const MatrixXd &grad) -> MatrixXd {
           MatrixXd grad_updated(grad.rows(), grad.cols());
           for(int i = 0; i < grad.rows(); i++){
               for(int j = 0; j < grad.cols(); j++){
                   grad_updated(i, j) = 1.0 / (1.0 + exp(-grad(i, j)));
               }
           }
           return grad_updated;
       };
       depends_on.push_back(new Dependency(x, grad_fn));
    }
    return Tensor(data, requires_grad, depends_on);
}