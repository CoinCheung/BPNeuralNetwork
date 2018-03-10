#ifndef _RELU_H_
#define _RELU_H_


#include<memory>
#include"Matrix.h"
#include"Layer.h"
#include"Optimizer.h"



class ReLU_Layer:public Layer
{
    public:
        MATRIX in_mat;

        ReLU_Layer();

        MATRIX forward(MATRIX);
        MATRIX backward(MATRIX, OPTIMIZER);
        void update();

        
};


typedef std::shared_ptr<ReLU_Layer> RELU;

#endif
