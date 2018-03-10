#ifndef _SOFTMAX_H_
#define _SOFTMAX_H_


#include<memory>
#include"Matrix.hpp"


typedef double DataType;
typedef Matrix2<DataType> MATRIX;


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
