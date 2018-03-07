#ifndef _SOFTMAX_H_
#define _SOFTMAX_H_


#include<memory>
#include"Matrix.hpp"

typedef Matrix2<double> MATRIX;


class Softmax
{
    public:
        Softmax();
        MATRIX forward(MATRIX&);
        MATRIX backward(MATRIX&);


};

#endif
