#ifndef _FULLYCONNECTED_H_
#define _FULLYCONNECTED_H_

#include"Matrix.hpp"
#include"Layer.h"
#include"Optimizer.h"
#include<iostream>



typedef Matrix2<double> MATRIX;


class FC_Layer: public Layer
{
    public:
        int hidden_num;
        std::string init_method;
        MATRIX in_mat;
        MATRIX weight;
        MATRIX bias;
        MATRIX gradW;
        MATRIX gradb;
        MATRIX deltaW;
        MATRIX deltab;

        explicit FC_Layer(int hidden_num, const char* init_mthd);

        FC_Layer& operator=(FC_Layer&);
        FC_Layer& operator=(FC_Layer&&);


        MATRIX initialize(int N, int D, const char* init_mthd);

        MATRIX forward(MATRIX);
        MATRIX backward(MATRIX, OPTIMIZER);
        void update();

        ~FC_Layer(){}

};


#endif
