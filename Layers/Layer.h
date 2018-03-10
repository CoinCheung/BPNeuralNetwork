#ifndef _LAYER_H_
#define _LAYER_H_


#include<memory>
#include"Matrix.hpp"
#include"Optimizer.h"


typedef Matrix2<double> MATRIX;


// base class for other layers
class Layer
{
    public:
        virtual MATRIX forward(MATRIX)=0;
        virtual MATRIX backward(MATRIX, OPTIMIZER)=0;
        virtual void update()=0;
        virtual ~Layer(){};
};



#endif
