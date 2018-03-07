#include"Softmax.h"


Softmax::Softmax()
{

}

MATRIX Softmax::forward(MATRIX& scores)
{
    MATRIX scores_exp = scores.exp();
    MATRIX scores_exp_sum = scores_exp.sum(1);
    MATRIX softmax = scores_exp / scores_exp_sum;

    return softmax;
}


MATRIX Softmax::backward(MATRIX&)
{

}

