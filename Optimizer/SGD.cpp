#include"SGD.h"


SGD::SGD()
{

}



SGD::SGD(DataType lr, DataType momen)
{
    learning_rate = lr;
    momentum = momen;
}



MATRIX SGD::get_delta(MATRIX grad, MATRIX delta)
{
    MATRIX mat;

    mat = momentum * delta - learning_rate * grad;

    return mat;
}

