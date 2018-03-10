#ifndef _BPNET_H_
#define _BPNET_H_

#include"Matrix.hpp"
#include"Layer.h"
#include"ReLU.h"
#include"FullyConnected.h"
#include"SoftmaxCrossEntropy.h"
#include"Optimizer.h"
#include<vector>
#include<memory>


typedef Matrix2<double> MATRIX;

typedef std::shared_ptr<Layer> LAYER;


// class of BPnet
class BPnet
{
    public:

        std::vector<std::shared_ptr<Layer>> layers;
        SoftmaxCrossEntropy LossFunc;
        OPTIMIZER optimizer;
        std::string init_method;

        BPnet(std::vector<int>& layer_nums, const char* init_method, OPTIMIZER optimizer);

        void train(MATRIX, MATRIX);
        MATRIX forward(MATRIX);
        MATRIX backward(MATRIX, OPTIMIZER);
        void update();

};


#endif
