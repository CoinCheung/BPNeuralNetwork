#ifndef _LAYER_H_
#define _LAYER_H_


#include<memory>
#include"Matrix/Matrix.h"


typedef std::shared_ptr<Matrix2<double>> MATRIX;

// base class for other layers
class Layer
{
    public:
        virtual MATRIX forward(MATRIX);
        virtual MATRIX backward(MATRIX);
};



#endif
