#ifndef _RELU_H_
#define _RELU_H_


#include<memory>
#include"Matrix.hpp"
#include"Layer.h"


typedef Matrix2<double> MATRIX;
typedef std::shared_ptr<Optimizer> OPTIMIZER;


class ReLU_Layer:public Layer
{
    public:
        MATRIX in_mat;

        ReLU_Layer();

        MATRIX forward(MATRIX);
        MATRIX backward(MATRIX, OPTIMIZER);
        void update();

        
};



#endif
