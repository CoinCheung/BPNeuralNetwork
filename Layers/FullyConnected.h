#ifndef _FULLYCONNECTED_H_
#define _FULLYCONNECTED_H_

#include<memory>
#include"Matrix/Matrix.h"
#include"Layer.h"

typedef std::shared_ptr<Matrix2<double>> MATRIX;


class FC_Layer: public Layer
{
    public:
        explicit FC_Layer(int hidden_num);

        MATRIX forward(MATRIX&);
        MATRIX backward(MATRIX&);

};


#endif
