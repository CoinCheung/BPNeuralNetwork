#ifndef _SGD_H_
#define _SGD_H_

#include"Optimizer.h"
#include"Matrix.h"


class SGD: public Optimizer
{
    public:
        DataType learning_rate;
        DataType momentum;
        MATRIX grad_delta;

        SGD();
        SGD(DataType lr=1e-3, DataType momen=0);
        MATRIX get_delta(MATRIX, MATRIX);
};


typedef std::shared_ptr<SGD> SGD_OPT;


#endif
