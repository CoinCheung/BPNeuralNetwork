#ifndef _SOFTMAX_H_
#define _SOFTMAX_H_


#include<memory>
#include"Matrix/Matrix.h"

typedef std::shared_ptr<Matrix2<double>> MATRIX;


class Softmax
{
    public:
        explicit Softmax();
        MATRIX forward(MATRIX);
        MATRIX backward(MATRIX);


};

#endif
