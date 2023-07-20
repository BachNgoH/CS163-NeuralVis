//
// Created by LENOVO on 7/9/2023.
//

#ifndef NEURALVISUALIZER_ACTIVATIONS_H
#define NEURALVISUALIZER_ACTIVATIONS_H

#include "../Eigen/Dense"
#include "Tensor.h"
#include <algorithm>
#include <cmath>
#include <memory>
using namespace std;
using namespace Eigen;

enum class Activations {
    relu,
    sigmoid,
    tanh,
    softplus,
    identity
};


class IActivationFunction {
public:
    virtual Tensor activation(const Tensor &x) const { return Tensor(MatrixXd::Zero(1,1)); };
};

class Identity: public IActivationFunction {
public:
    Tensor activation(const Tensor &x) const override;
};


class Relu: public IActivationFunction {
public:
    Tensor activation(const Tensor &x) const override;
};

class Sigmoid: public IActivationFunction {
public:
    Tensor activation(const Tensor &x) const override;
};

class Tanh: public IActivationFunction {
public:
    Tensor activation(const Tensor &x) const override;
};

class SoftPlus: public IActivationFunction {
public:
    Tensor activation(const Tensor &x) const override;
};


#endif //NEURALVISUALIZER_ACTIVATIONS_H
