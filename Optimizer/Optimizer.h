#ifndef _OPTIMIZER_H_
#define _OPTIMIZER_H_


#include"Matrix.h"
#include<memory>


class Optimizer
{
    public:
        virtual MATRIX get_delta(MATRIX, MATRIX)=0;
};

typedef std::shared_ptr<Optimizer> OPTIMIZER;


#endif
