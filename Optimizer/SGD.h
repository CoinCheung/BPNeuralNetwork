#ifndef _SGD_H_
#define _SGD_H_

#include"Optimizer.h"
#include"Matrix.hpp"


typedef Matrix2<double> MATRIX;


class SGD: public Optimizer
{
    public:
        double learning_rate;
        double momentum;
        MATRIX grad_delta;

        SGD();
        SGD(double lr=1e-3, double momen=0);
        MATRIX get_delta(MATRIX, MATRIX);
};


typedef std::shared_ptr<SGD> SGD_OPT;


#endif
