#include"BP.h"
#include"Matrix.hpp"
#include"Layer.h"
#include"FullyConnected.h"
#include"ReLU.h"
#include"SoftmaxCrossEntropy.h"
#include<vector>
#include<iostream>
#include<string>
#include<memory>



typedef std::shared_ptr<FC_Layer> FullyConnected;
typedef std::shared_ptr<ReLU_Layer> RELU;



BPnet::BPnet(std::vector<int>& FC_nums, const char* i_mthd, OPTIMIZER opt)
{
    optimizer = opt;

    int layer_num = FC_nums.size();
    int hidden_nums;
    FullyConnected fc_layer;
    RELU relu_layer;

    layers.reserve(3*layer_num);
    for(auto i{0}; i < layer_num-1; i++)
    {
        hidden_nums = FC_nums[i];
        fc_layer.reset(new FC_Layer(hidden_nums, i_mthd));
        layers.push_back(fc_layer);

        relu_layer.reset(new ReLU_Layer);
        layers.push_back(relu_layer);
    }
    hidden_nums = FC_nums[layer_num-1];
    layers.push_back(FullyConnected(new FC_Layer(hidden_nums, i_mthd)));

    init_method = std::string(i_mthd);
}





MATRIX BPnet::forward(MATRIX mat)
{

    for (auto& layer:layers)
    {
        mat = layer->forward(mat);
    }

    return mat;
}



MATRIX BPnet::backward(MATRIX grad_pre, OPTIMIZER optimizer)
{
    MATRIX grad{grad_pre};

    auto len = layers.size();
    for(auto i{0}; i<len; i++)
    {
        grad = layers[len-i-1]->backward(grad, optimizer);
    }

    return grad;
}



void BPnet::update()
{
    int layer_num = layers.size();

    for(auto el:layers)
    {
        el->update();
    }
}


void BPnet::train(MATRIX in_mat, MATRIX label)
{
    MATRIX Loss;
    MATRIX scores;
    MATRIX grad;

    FullyConnected l1 = std::static_pointer_cast<FC_Layer>(layers[0]);

    // forward
    scores = forward(in_mat);
    Loss = LossFunc.forward(scores, label);
    std::cout << "loss:" << std::endl;
    Loss.print();

    // backward
    grad = LossFunc.backward();
    backward(grad, optimizer);

    // update network
    update();

}




