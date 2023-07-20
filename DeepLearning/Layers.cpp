//
// Created by LENOVO on 7/9/2023.
//

#include "Layers.h"

Linear::Linear(int inputN, int outputN, Activations activation, double lr): weights(inputN, outputN) {
    this->inputN = inputN;
    this->outputN = outputN;
    this->lr = lr;
    switch (activation) {
        case Activations::relu:
            this->activation = new Relu();
            break;
        case Activations::tanh:
            this->activation = new Tanh();
            break;
        case Activations::sigmoid:
            this->activation =  new Sigmoid();
            break;
        case Activations::softplus:
            this->activation =  new SoftPlus();
            break;
        default:
            this->activation =  new Identity();
            break;
    }
}

Tensor Linear::forward(const Tensor &input) const {

    Tensor x = input.matmul(weights);
    Tensor x1 = this->activation->activation(x);
    return x1;
}

void Linear::zero_grad() {
    weights.zero_grad();
}

void Linear::step_SGD(){
    weights.data = weights.data - weights.grad->data * lr;
}

void Linear::del_ptrs() {
    delete activation;
    for(int i = 0; i < weights.depends_on.size(); i++){
        delete weights.depends_on[i];
    }
    delete weights.grad;
}