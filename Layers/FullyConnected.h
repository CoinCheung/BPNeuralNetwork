#ifndef _FULLYCONNECTED_H_
#define _FULLYCONNECTED_H_

#include"Matrix.hpp"
#include"Layer.h"
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

        explicit FC_Layer(int hidden_num, const char* act_type, const char* init_mthd);

        FC_Layer& operator=(FC_Layer&);
        FC_Layer& operator=(FC_Layer&&);


        MATRIX initialize(int N, int D, const char* init_mthd);
        MATRIX get_weight();
        MATRIX get_bias();
        MATRIX get_gradW();
        MATRIX get_gradb();

        MATRIX forward(MATRIX);
        MATRIX backward(MATRIX);
        void update();

        ~FC_Layer(){}

};


#endif
