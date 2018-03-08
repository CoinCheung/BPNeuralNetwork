#include"FullyConnected.h"
#include"numeric.h"
#include<vector>
#include<iostream>
#include<cassert>



FC_Layer::FC_Layer(int hnum, const char* act_type, const char* init_mthd)
{
    hidden_num = hnum;
    init_method = std::string(init_mthd);
}



FC_Layer& FC_Layer::operator=(FC_Layer& fl)
{
    hidden_num = fl.hidden_num;
    init_method = fl.init_method;
    weight = fl.weight;
    bias = fl.bias;
    gradW = fl.gradW;
    gradb = fl.gradb;

    return *this;
}



FC_Layer& FC_Layer::operator=(FC_Layer&& fl)
{
    hidden_num = fl.hidden_num;
    init_method = fl.init_method;
    weight = fl.weight;
    bias = fl.bias;
    gradW = fl.gradW;
    gradb = fl.gradb;

    return *this;
}



MATRIX FC_Layer::initialize(int N, int D, const char* init_mthd)
{
    using namespace std;

    MATRIX mat(N, D);

    if (init_mthd == "gaussian")
    {
        double* pd;
        long size;
        pd = mat.data.get();
        size = mat.ele_num;
        for(long i{0}; i < size; i++)
            // pd[i] = gaussian_rand(0, 0.02);
            pd[i] = i/10.0;
    }
    else
    {
        cout << "FC_Layer: unknown initializer" << endl;
        assert(false);
    }

    return mat;
}



MATRIX FC_Layer::get_weight()
{
    return weight;
}



MATRIX FC_Layer::get_bias()
{
    return bias;
}



MATRIX FC_Layer::get_gradW()
{
    return gradW;
}



MATRIX FC_Layer::get_gradb()
{
    return gradb;
}



MATRIX FC_Layer::forward(MATRIX input)
{

    if(weight.data == nullptr)
    {
        weight = initialize(input.D, hidden_num, "gaussian");
        bias = MATRIX::zeros(1, hidden_num);
    }

    in_mat = input;
    MATRIX mat = input.dot(weight) + bias;

    return mat;
}



MATRIX FC_Layer::backward(MATRIX grad_pre)
{
    MATRIX mat;

    gradW = in_mat.transpose().dot(grad_pre);
    gradb = MATRIX::ones(1, in_mat.N).dot(grad_pre);
    mat = grad_pre.dot(weight.transpose());

    return mat;
}



void FC_Layer::update()
{

}


