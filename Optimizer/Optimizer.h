#ifndef _OPTIMIZER_H_
#define _OPTIMIZER_H_


#include"Matrix.hpp"
#include<memory>


typedef Matrix2<double> MATRIX;


class Optimizer
{
    public:
        virtual MATRIX get_delta(MATRIX, MATRIX)=0;
};

typedef std::shared_ptr<Optimizer> OPTIMIZER;


#endif
