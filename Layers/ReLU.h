#ifndef _RELU_H_
#define _RELU_H_


#include<memory>
#include"Matrix/Matrix.h"
#include"Layer.h"


typedef std::shared_ptr<Matrix2<double>> MATRIX;


class ReLU_Layer:public Layer
{
    public:
        explicit ReLU_Layer();

        MATRIX forward(MATRIX&);
        MATRIX backward(MATRIX&);

        
};



#endif
