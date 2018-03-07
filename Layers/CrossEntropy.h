#ifndef _CROSS_ENTROPY_H_
#define _CROSS_ENTROPY_H_


#include"Matrix.hpp"



typedef Matrix2<double> MATRIX;

class CrossEntropy 
{
    public:
        CrossEntropy();
        MATRIX forward(MATRIX&, MATRIX&);
        MATRIX backward(MATRIX&);
};

#endif

