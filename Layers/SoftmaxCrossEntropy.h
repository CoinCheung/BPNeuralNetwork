#ifndef _SOFTMAX_H_
#define _SOFTMAX_H_


#include<memory>
#include"Matrix.h"



class SoftmaxCrossEntropy
{
    public:
        MATRIX softmax;
        MATRIX label;

        SoftmaxCrossEntropy();
        MATRIX forward(MATRIX, MATRIX);
        MATRIX backward();
};

#endif
