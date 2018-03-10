#ifndef _LAYER_H_
#define _LAYER_H_


#include<memory>
#include"Matrix.h"
#include"Optimizer.h"




// base class for other layers
class Layer
{
    public:
        virtual MATRIX forward(MATRIX)=0;
        virtual MATRIX backward(MATRIX, OPTIMIZER)=0;
        virtual void update()=0;
        virtual ~Layer(){};
};

typedef std::shared_ptr<Layer> LAYER;


#endif
