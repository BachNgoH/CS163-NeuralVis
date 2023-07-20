//
// Created by LENOVO on 7/9/2023.
//

#ifndef NEURALVISUALIZER_PARAMETER_H
#define NEURALVISUALIZER_PARAMETER_H

#include "Tensor.h"

class Parameter :public Tensor {
public:
    Parameter(int rows, int cols) : Tensor(MatrixXd::Random(rows, cols), true) {}
};

#endif //NEURALVISUALIZER_PARAMETER_H
