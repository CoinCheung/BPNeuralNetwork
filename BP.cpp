#include"BP.h"
#include"Matrix.hpp"
#include"FullyConnected.h"
#include"ReLU.h"
#include"Softmax.h"
#include<vector>
#include<iostream>
#include<string>


typedef Matrix2<double> MATRIX;


BPnet::BPnet(std::vector<int>& FC_nums, const char* act_type, const char* i_mthd)
{
    using namespace std;


    int layer_num = FC_nums.size();
    int hidden_nums;
    FullyConnected fc_layer;

    layers.reserve(3*layer_num);
    for(auto i{0}; i < layer_num-1; i++)
    {
        hidden_nums = FC_nums[i];
        fc_layer.reset(new FC_Layer(hidden_nums, act_type, i_mthd));
        layers.push_back(fc_layer);
    }
    hidden_nums = FC_nums[layer_num-1];
    layers.push_back(FullyConnected(new FC_Layer(hidden_nums, "", i_mthd)));

    init_method = std::string(i_mthd);
}





MATRIX BPnet::forward(MATRIX mat)
{

    for(auto& layer:layers)
    {
        mat = layer->forward(mat);
    }

    MATRIX softmax;
    softmax = SoftmaxLayer.forward(mat);

    return softmax;
}



MATRIX BPnet::backward(MATRIX loss)
{
    MATRIX grad;

    grad = SoftmaxLayer.backward(loss);

    auto len = layers.size();
    for(auto i{len-1}; i>=0; i--)
    {
        grad = layers[i]->backward(grad);
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
    MATRIX softmax;
    MATRIX Loss;
    MATRIX scores;

    scores = forward(in_mat);
    scores = forward(in_mat);
    Loss = ce_loss.forward(scores, label);
    std::cout << "loss:" << std::endl;
    Loss.print();
    backward(ce_loss.backward(Loss));
    update();
}




