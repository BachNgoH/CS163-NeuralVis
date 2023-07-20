//
// Created by BachNgo on 7/6/2023.
//

#ifndef NEURALVISUALIZER_TENSOR_H
#define NEURALVISUALIZER_TENSOR_H

#include "../Eigen/Dense"
// #include "Dependency.h"
#include <functional>
#include <vector>
#include <iostream>
#include <memory>
using namespace std;
using namespace Eigen;

class Tensor;

class Dependency {
public:
    const Tensor &tensor;
    function<MatrixXd(const MatrixXd &)> grad_fn;
//    MatrixXd (*func)(MatrixXd &);
//    Dependency(Tensor* tensor, std::function<MatrixXd(MatrixXd)> &grad_fn) : tensor(tensor), grad_fn(grad_fn) {}
    Dependency(const Tensor& tensor, function<MatrixXd(const MatrixXd &)> &grad_fn) : tensor(tensor), grad_fn(grad_fn) {}

};

class Tensor {
public:
    MatrixXd data;
    bool requires_grad;
    vector<Dependency*> depends_on;
    Tensor* grad;
    Tensor() {}

    Tensor(const MatrixXd& data, bool requires_grad = false, const std::vector<Dependency*> &depends_on = {})
            : data(data), requires_grad(requires_grad), depends_on(depends_on) {
        if (requires_grad)
            init_grad();
    }

    void zero_grad() {
        grad->data = MatrixXd::Zero(data.rows(), data.cols());
        grad->requires_grad = false;
    };

    void init_grad() {
        grad = new Tensor(MatrixXd::Zero(1,1), false);
    }

    Tensor operator+(const Tensor& other) const {
        return _add(*this, other);
    }

    Tensor operator+(double scalar) const {
        return _add(*this, Tensor(MatrixXd::Constant(data.rows(), data.cols(), scalar)));
    }

    Tensor operator+=(const Tensor& other) {
        data = data + other.data;
        return *this;
    }

    Tensor operator+=(double scalar) {
        data.array() += scalar;
        return *this;
    }

    Tensor operator-=(const Tensor& other) {
        data = data - other.data;
        return *this;
    }

    Tensor operator-=(double scalar) {
        data.array() -= scalar;
        return *this;
    }

    Tensor operator*=(const Tensor& other) {
        data = data * other.data;
        return *this;
    }

    Tensor operator*=(double scalar) {
        data = data * scalar;
        return *this;
    }

    Tensor operator*(const Tensor& other) const {
        return _mul(*this, other);
    }

    Tensor operator*(double scalar) const {
        return _mul(*this, Tensor(MatrixXd::Constant(data.rows(), data.cols(), scalar)));
    }

    Tensor operator-() const {
        return _neg(*this);
    }

    Tensor operator-(const Tensor& other) const {
        return _sub(*this, other);
    }

    Tensor operator-(double scalar) const {
        return _sub(*this, Tensor(MatrixXd::Constant(data.rows(), data.cols(), scalar)));
    }

    Tensor sum() const {
        return tensor_sum(*this);
    }

    Tensor matmul(const Tensor& other) const {
        return _matmul(*this, other);
    }

    friend std::ostream& operator<<(std::ostream& os, const Tensor& tensor) {
        os << "Tensor(" << tensor.data << ", requires_grad=" << tensor.requires_grad << ")";
        return os;
    }

    void backward(const Tensor &grad) const {
        assert(this->requires_grad);
        if(this->grad->data.rows() == 1 && this->grad->data.cols() == 1)
            this->grad->data = this->grad->data.array()(0,0) + grad.data.array();
        else
            this->grad->data = this->grad->data + grad.data;

        for(size_t i = 0; i < this->depends_on.size(); i++) {
            MatrixXd backward_grad = depends_on[i]->grad_fn(grad.data);
            Tensor back_grad(backward_grad);
            // cout << "Dependency: (" << depends_on[i]->tensor.data.rows() << "," << depends_on[i]->tensor.data.cols() << ")" << endl;

            cout << "Dependency: " << depends_on[i]->tensor << endl;
            depends_on[i]->tensor.backward(back_grad);
        }
    }

    void backward() {
        assert(this->requires_grad);
        this->grad->data = MatrixXd::Constant(1,1,1);

        for(int i = 0; i < this->depends_on.size(); i++){
            MatrixXd backward_grad = this->depends_on[i]->grad_fn(this->grad->data);
            cout << "Dependency: " << depends_on[i]->tensor << endl;
            this->depends_on[i]->tensor.backward(Tensor(backward_grad));
        }
    }

    static Tensor _add(const Tensor& t1, const Tensor& t2);

    static Tensor _mul(const Tensor& t1, const Tensor& t2);

    static Tensor _matmul(const Tensor& t1, const Tensor& t2);

    static Tensor _neg(const Tensor& t);

    static Tensor _sub(const Tensor& t1, const Tensor& t2);

    static Tensor tensor_sum(const Tensor& t);
};


#endif //NEURALVISUALIZER_TENSOR_H
