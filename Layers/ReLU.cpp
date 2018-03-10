#include"ReLU.h"
#include"Optimizer.h"


typedef double DataType;


ReLU_Layer::ReLU_Layer()
{

}




MATRIX ReLU_Layer::forward(MATRIX input)
{
    MATRIX mat(input.N, input.D);
    DataType* ip{input.data.get()};
    DataType* mp{mat.data.get()};
    long num{input.ele_num};

    in_mat = input;

    for (long i{0}; i<num; i++)
        if (ip[i] > 0)
            mp[i] = ip[i];
        else
            mp[i] = 0;

    return mat;
}



MATRIX ReLU_Layer::backward(MATRIX grad_prev, OPTIMIZER optimizer)
{
    assert((grad_prev.N==in_mat.N) && (grad_prev.D==in_mat.D));

    MATRIX mat(grad_prev.N, grad_prev.D);
    DataType* ip{in_mat.data.get()};
    DataType* gp{grad_prev.data.get()};
    DataType* mp{mat.data.get()};
    long num{grad_prev.ele_num};

    for (long i{0}; i<num; i++)
        if (ip[i] > 0)
            mp[i] = gp[i];
        else
            mp[i] = 0;

    return mat;
}



void ReLU_Layer::update()
{
    // do nothing
}
