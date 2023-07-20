//
// Created by LENOVO on 7/9/2023.
//

#ifndef NEURALVISUALIZER_LAYERS_H
#define NEURALVISUALIZER_LAYERS_H
#include "Tensor.h"
#include "Activations.h"
#include "Parameter.h"
#include <fstream>
#include <memory>

class Linear {
public:
    int inputN, outputN;
    Parameter weights;
    IActivationFunction *activation;
    double lr;

    Linear(int inputN, int outputN, Activations activation, double lr=0.01);

    Tensor forward(const Tensor &input) const;
    void zero_grad();
    void step_SGD();
    void del_ptrs();
};


#endif //NEURALVISUALIZER_LAYERS_H
