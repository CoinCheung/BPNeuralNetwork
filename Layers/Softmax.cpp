#include"Softmax.h"


Softmax::Softmax()
{

}

MATRIX Softmax::forward(MATRIX scores)
{
    MATRIX scores_exp = scores.exp();
    // std::cout << "scores exp" << std::endl;
    // scores_exp.print();

    MATRIX scores_exp_sum = scores_exp.sum(1);
    // std::cout << "scores exp sum" << std::endl;
    // scores_exp_sum.print();

    MATRIX softmax = scores_exp / scores_exp_sum;
    // std::cout << "softmax" << std::endl;
    // softmax.print();

    return softmax;
}


MATRIX Softmax::backward(MATRIX)
{

}

