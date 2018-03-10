#include"BP.h"
#include"Matrix.h"
#include"Layer.h"
#include"FullyConnected.h"
#include"ReLU.h"
#include"SoftmaxCrossEntropy.h"
#include<vector>
#include<iostream>
#include<string>




BPnet::BPnet()
{

}




BPnet::BPnet(std::vector<int>& FC_nums, const char* i_mthd, OPTIMIZER opt)
{
    optimizer = opt;

    int layer_num = FC_nums.size();
    int hidden_nums;
    FULLY_CONNECTED fc_layer;
    RELU relu_layer;

    layers.reserve(3*layer_num);
    for(auto i{0}; i < layer_num-1; i++)
    {
        hidden_nums = FC_nums[i];
        fc_layer = std::make_shared<FC_Layer>(hidden_nums, i_mthd);
        layers.push_back(fc_layer);

        relu_layer = std::make_shared<ReLU_Layer>();
        layers.push_back(relu_layer);
    }
    hidden_nums = FC_nums[layer_num-1];
    layers.push_back(std::make_shared<FC_Layer>(hidden_nums, i_mthd));

    init_method = std::string(i_mthd);
}




BPnet::BPnet(BPnet& net)
{
    layers = net.layers;
    LossFunc = net.LossFunc;
    optimizer = net.optimizer;
    init_method = net.init_method;
}



BPnet::BPnet(BPnet&& net)
{
    layers.swap(net.layers);
    LossFunc = net.LossFunc;
    optimizer = net.optimizer;
    init_method = net.init_method;
}



BPnet& BPnet::operator=(BPnet net)
{
    layers = net.layers;
    LossFunc = net.LossFunc;
    optimizer = net.optimizer;
    init_method = net.init_method;
    
    return *this;
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
    static long iter_num = 0;

    // forward
    scores = forward(in_mat);
    Loss = LossFunc.forward(scores, label);
    std::cout << "iteration: " << iter_num << ",   loss:" << std::endl;
    Loss.print();

    // backward
    grad = LossFunc.backward();
    backward(grad, optimizer);

    // update network
    update();

    iter_num++;

}




