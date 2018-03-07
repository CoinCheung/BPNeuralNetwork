#ifndef _FULLYCONNECTED_H_
#define _FULLYCONNECTED_H_

#include"Matrix.hpp"
#include"Layer.h"

typedef Matrix2<double> MATRIX;


class FC_Layer: public Layer
{
    public:
        int hidden_num;
        MATRIX weight;
        MATRIX grad;

        explicit FC_Layer(int hidden_num);

        MATRIX forward(MATRIX&);
        MATRIX backward(MATRIX&);

        ~FC_Layer(){}

};


#endif
