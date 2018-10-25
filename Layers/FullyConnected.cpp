#include"FullyConnected.h"
#include"Optimizer.h"
#include"numeric.h"
#include<iostream>
#include<string>



FC_Layer::FC_Layer(int hnum, const char* init_mthd)
{
    hidden_num = hnum;
    init_method = std::string(init_mthd);
}





MATRIX FC_Layer::initialize(int N, int D, const char* init_mthd) {
    using namespace std;

    CHECK_EQ(init_method, "gaussian") << "unknown initializer\n";

    MATRIX mat(N, D);
    string init_method(init_mthd);
    DataType* pd;
    long size;

    pd = mat.data.get();
    size = mat.ele_num;
    for(long i{0}; i < size; i++) {
        pd[i] = static_cast<DataType>(gaussian_rand(0, 0.02));
    }

    return mat;
}



MATRIX FC_Layer::forward(MATRIX input) {

    if(weight.data == nullptr) {
        weight = initialize(input.D, hidden_num, "gaussian");
        bias = MATRIX::zeros(1, hidden_num);
    }

    in_mat = input;
    MATRIX mat = input.dot(weight) + bias;

    return mat;
}



MATRIX FC_Layer::backward(MATRIX grad_pre, OPTIMIZER optimizer) {
    MATRIX mat;

    gradW = in_mat.transpose().dot(grad_pre);
    gradb = MATRIX::ones(1, in_mat.N).dot(grad_pre);
    mat = grad_pre.dot(weight.transpose());

    if (deltaW.data==nullptr) {
        deltaW = MATRIX::zeros_like(weight);
        deltab = MATRIX::zeros_like(bias);
    }

    deltaW = optimizer->get_delta(gradW, deltaW);
    deltab = optimizer->get_delta(gradb, deltab);

    return mat;
}



void FC_Layer::update() {
    weight = weight + deltaW;
    bias = bias + deltab;
}


