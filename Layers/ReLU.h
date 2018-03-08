#ifndef _RELU_H_
#define _RELU_H_


#include<memory>
#include"Matrix.hpp"
#include"Layer.h"


typedef Matrix2<double> MATRIX;


class ReLU_Layer:public Layer
{
    public:
        ReLU_Layer();

        MATRIX forward(MATRIX);
        MATRIX backward(MATRIX);
        void update();

        
};



#endif
