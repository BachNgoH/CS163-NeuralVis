//
// Created by LENOVO on 7/6/2023.
//

#include "Tensor.h"
// #include "Dependency.h"

Tensor Tensor::_add(const Tensor &t1, const Tensor &t2) {
    MatrixXd data = t1.data + t2.data;
    bool requires_grad = t1.requires_grad || t2.requires_grad;
    vector<Dependency*> depends_on;

    if (t1.requires_grad) {
        function<MatrixXd(const MatrixXd &)> grad_fn1 = ([](const MatrixXd& grad) -> MatrixXd {
            MatrixXd grad_updated= grad;
            return grad_updated;
        });
        depends_on.push_back(new Dependency(t1, grad_fn1));
    }
    if (t2.requires_grad) {
        function<MatrixXd(const MatrixXd &)> grad_fn2 = [](const MatrixXd& grad) -> MatrixXd {
            MatrixXd grad_updated = grad;
            return grad_updated;
        };
        depends_on.push_back(new Dependency(t2, grad_fn2));
    }

    return Tensor(data, requires_grad, depends_on);
}

Tensor Tensor::_mul(const Tensor &t1, const Tensor &t2) {
    MatrixXd data = t1.data.cwiseProduct(t2.data);
    bool requires_grad = t1.requires_grad || t2.requires_grad;
    vector<Dependency*> depends_on;
    if (t1.requires_grad){
        function<MatrixXd(MatrixXd const &)> grad_fn1 = [&](const MatrixXd& grad) -> MatrixXd {
            MatrixXd grad_update = grad.cwiseProduct(t2.data);
            return grad_update;
        };

        depends_on.push_back(new Dependency(t1, grad_fn1));
    }

    if (t2.requires_grad){
        function<MatrixXd(MatrixXd const &)> grad_fn2 = [&](const MatrixXd& grad) -> MatrixXd {
            MatrixXd grad_updated = grad.cwiseProduct(t1.data);
            return grad_updated;
        };
        depends_on.push_back(new Dependency(t2, grad_fn2));
    }

    return Tensor(data, requires_grad, depends_on);
}

Tensor Tensor::_matmul(const Tensor &t1, const Tensor &t2) {

    MatrixXd data = t1.data * t2.data;
    bool requires_grad = t1.requires_grad || t2.requires_grad;

    vector<Dependency*> depends_on;

    if (t1.requires_grad) {
        function<MatrixXd(MatrixXd const &)> grad_fn1 = [&](const MatrixXd& grad) -> MatrixXd {
            cout << "gradient shape: (" << grad.rows() << ", " << grad.cols() << ")" << endl;
            cout << "t2 shape: (" << t2.data.rows() << ", " << t2.data.cols() << ")" << endl;

            MatrixXd grad_updated = grad * t2.data.transpose();
            return grad_updated;
        };
        depends_on.push_back(new Dependency(t1, grad_fn1));
    }

    if (t2.requires_grad) {
        function<MatrixXd(MatrixXd const &)> grad_fn2 = [&](const MatrixXd& grad) -> MatrixXd {
            cout << "gradient shape: (" << grad.rows() << ", " << grad.cols() << ")" << endl;
            cout << "t1 shape: (" << t1.data.rows() << ", " << t1.data.cols() << ")" << endl;

            MatrixXd grad_updated = t1.data.transpose() * grad;
            return grad_updated;
        };
        depends_on.push_back(new Dependency(t2, grad_fn2));
    }

    return Tensor(data, requires_grad, depends_on);
}

Tensor Tensor::_neg(const Tensor &t) {
    MatrixXd data = -t.data;
    bool requires_grad = t.requires_grad;
    vector<Dependency*> depends_on;
    if (requires_grad){
        function<MatrixXd(MatrixXd const &)> grad_fn = [&](const MatrixXd& x) -> MatrixXd {
            return -x;
        };

        depends_on.push_back(new Dependency(t, grad_fn));
    }
    return Tensor(data, requires_grad, depends_on);
}

Tensor Tensor::_sub(const Tensor &t1, const Tensor &t2) {
    MatrixXd data = t1.data - t2.data;
    bool requires_grad = t1.requires_grad || t2.requires_grad;
    vector<Dependency*> depends_on;

    if (t1.requires_grad) {
        function<MatrixXd(MatrixXd const &)> grad_fn1 = [&](const MatrixXd& grad) -> MatrixXd {
            MatrixXd grad_updated= grad;
            return grad_updated;
        };
        depends_on.push_back(new Dependency(t1, grad_fn1));
    }
    if (t2.requires_grad) {
        function<MatrixXd(MatrixXd const &)> grad_fn2 = [&](const MatrixXd& grad) -> MatrixXd {
            MatrixXd grad_updated = -grad;
            return grad_updated;
        };
        depends_on.push_back(new Dependency(t2, grad_fn2));
    }

    return Tensor(data, requires_grad, depends_on);
}

Tensor Tensor::tensor_sum(const Tensor &t) {
    MatrixXd sum = MatrixXd::Constant(1,1, t.data.sum());
    bool requires_grad = t.requires_grad;
    vector<Dependency*> depends_on;
    if (requires_grad) {
        function<MatrixXd(MatrixXd const &)> grad_fn = [&](const MatrixXd& grad) -> MatrixXd {
            MatrixXd result = grad(0,0) * MatrixXd::Ones(t.data.rows(), t.data.cols()).transpose();
            return result.transpose();
        };
        depends_on.push_back(new Dependency(t, grad_fn));
    }
    return Tensor(sum, requires_grad, depends_on);
}

