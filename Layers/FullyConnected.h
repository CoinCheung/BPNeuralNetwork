#ifndef _FULLYCONNECTED_H_
#define _FULLYCONNECTED_H_

#include<memory>
#include"Matrix.h"
#include"Layer.h"
#include"Optimizer.h"




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


        MATRIX initialize(int N, int D, const char* init_mthd);

        MATRIX forward(MATRIX);
        MATRIX backward(MATRIX, OPTIMIZER);
        void update();

        ~FC_Layer(){}
};


typedef std::shared_ptr<FC_Layer> FULLY_CONNECTED;

#endif
