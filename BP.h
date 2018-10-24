#ifndef _BPNET_H_
#define _BPNET_H_

#include"Matrix.h"
#include"Layer.h"
#include"SoftmaxCrossEntropy.h"
#include"Optimizer.h"
#include<vector>
#include<string>



class BPnet
{
    public:
        // data members
        std::vector<LAYER> layers;
        SoftmaxCrossEntropy LossFunc;
        OPTIMIZER optimizer;
        std::string init_method;

        // constructors
        BPnet();
        BPnet(std::vector<int>& layer_nums, const char* init_method, OPTIMIZER optimizer);
        BPnet(BPnet &);
        BPnet(BPnet &&);

        // operators
        BPnet& operator=(BPnet);

        // memeber functions
        MATRIX forward(MATRIX);
        MATRIX backward(MATRIX, OPTIMIZER);
        void update();
        void train(MATRIX&, MATRIX&);
};


#endif
