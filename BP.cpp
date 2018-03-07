#include"BP.h"
#include"Matrix.hpp"
#include"FullyConnected.h"
#include"ReLU.h"
#include"Softmax.h"
#include<vector>
#include<iostream>
#include<string>


typedef Matrix2<double> MATRIX;


BPnet::BPnet(std::vector<int>& FC_nums, const char* i_mthd)
{
    int layer_num = FC_nums.size();
    int hidden_nums;

    layers.reserve(3*layer_num);
    for(auto i{0}; i < layer_num-1; i++)
    {
        hidden_nums = FC_nums[i];
        layers.push_back(FullyConnected(new FC_Layer(hidden_nums)));
        layers.push_back(RELU(new ReLU_Layer));
    }
    hidden_nums = FC_nums[layer_num-1];
    layers.push_back(FullyConnected(new FC_Layer(hidden_nums)));

    init_method = std::string(i_mthd);
}





MATRIX BPnet::forward(MATRIX& in_mat)
{
    using namespace std;

    Matrix2<double> mat = in_mat;


    for(auto& layer:layers)
    {
        mat = layer->forward(mat);
    }

    MATRIX Loss;
    Loss = softmax.forward(mat);

    return Loss;
}


MATRIX BPnet::backward(MATRIX& loss)
{
    MATRIX grad;

    grad = softmax.backward(loss);

    auto len = layers.size();
    for(auto i{len-1}; i>=0; i--)
    {
        grad = layers[i]->backward(grad);
    }

    return grad;
}


void BPnet::train()
{
    MATRIX mat;
    MATRIX Loss;

    mat = input;
    Loss = BPnet::forward(mat);
    BPnet::backward(Loss);
}






// BPnet::BPnet(): in_size(0), out_size(0), hlayer_num(0), hiden_size(NULL), W(NULL), b(NULL), dW(NULL), db(NULL)
// {}


//
// function:
// instruction:
// input:
// return:
//
// BPnet::BPnet(const int is, const int hn, int *hs, const int os, const double std): in_size(is), out_size(os), hlayer_num(hn), hiden_size(hs), W(new Matrix2<double>[hlayer_num+1]), b(new Matrix2<double>[hlayer_num+1]), dW(new Matrix2<double>[hlayer_num+1]), db(new Matrix2<double>[hlayer_num+1])
// {
//     initialize the W and b matrix
//     W[0] = std * Matrix2<double>::randn(in_size, hiden_size[0]);
//     b[0] = Matrix2<double>::zeros(1, hiden_size[0]);
//     for(int i = 0; i < hlayer_num-1; i++)
//     {
//         W[i] = std * Matrix2<double>::randn(hiden_size[i],hiden_size[i+1]);
//         b[i] = Matrix2<double>::zeros(1, hiden_size[i+1]);
//     }
//     W[hlayer_num] = std * Matrix2<double>::randn(hiden_size[hlayer_num-1],out_size);
//     b[hlayer_num] = Matrix2<double>::zeros(1, out_size);
//
// }
//
//
//
//
// function:
// instruction:
// input:
// return:
//
// BPnet::~BPnet()
// {
//     delete hiden_size;
//     delete[] W;
//     delete[] b;
//     delete[] dW;
//     delete[] db;
//     loss.clear();
// }
//
//
//
//
// function:
// instruction:
// input:
// return:
//
// void BPnet::train(Matrix2<double>& X, Matrix2<double>& y, Matrix2<double>& Xval, Matrix2<double>& yval, int batch_size, const double reg, double learning_rate, const double lr_decay, const int num_iter)
// {
//     Matrix2<double> Xpick;
//     Matrix2<double> ypick;
//     Ind choice;
//     double loss_train;
//     long num_train;
//     int epoch;
//
//     num_train = X.N;
//     if(num_train < batch_size)
//         epoch = 1;
//     else
//         epoch = num_train / batch_size;
//     srand(0);
//     for(int i = 0; i < num_iter; i++)
//     {
//         pick out the random train sample batches
//         choice = Ind::randchoice(batch_size, num_train);
//         Xpick = X(choice);
//         ypick = y(choice);
//
//         compute the loss and the gradients
//         loss_train = BPnet::loss_softmax(Xpick, ypick, reg);
//         loss.push_back(loss_train);
//
//         update the Ws and bs
//         for(int i = 0; i < hlayer_num+1; i++)
//         {
//             W[i] = W[i] - learning_rate * dW[i];
//             b[i] = b[i] - learning_rate * db[i];
//         }
//
//         if(i % epoch == 0)
//             learning_rate = learning_rate * lr_decay;
//     }
//
//     cout << "losses in the train process are: " << endl;
//     for(unsigned int i = 0; i < loss.size(); i++)
//         cout << loss[i] << endl;
// }
//
//
//
//
// function:
// instruction: compute the softmax loss according to the given train samples, and compute the relevant gradient dW, db
// input:
// return:
//
// double BPnet::loss_softmax(Matrix2<double>& Xbatch, Matrix2<double>& ybatch, const double reg)
// {
//     double loss;
//     Matrix2<double> h[hlayer_num+1];
//     Matrix2<double> a[hlayer_num+1];
//     Matrix2<double> relu_a;
//
//     forward compute the loss function
//     h[0] = Xbatch.dot(W[0]) + b[0]; intput layer to the first hiden layer
//     a[0] = BPnet::activate_relu(h[0]);
//     for(int i = 1; i < hlayer_num; i++) the other hiden layers, all with relu
//     {
//         h[i] = a[i-1].dot(W[i]) + b[i];
//         a[i] = BPnet::activate_relu(h[i]);
//     }
//     h[hlayer_num] = a[hlayer_num-1].dot(W[hlayer_num]) + b[hlayer_num]; to the output layer
//
//     Matrix2<double> score_exp = (h[hlayer_num]).exp();
//     Matrix2<double> score_exp = (h[hlayer_num] - h[hlayer_num].max(1)).exp();
//     Matrix2<double> score_exp_prob = score_exp / score_exp.sum(1);
//     Matrix2<double> score_exp_correct = score_exp_prob(ybatch.toInd());
//     Matrix2<double> score_soft = score_exp_correct.log();
//     double loss_reg = 0;
//     for(int i = 0; i < hlayer_num+1; i++)
//         loss_reg += reg * (W[i].square().sum());
//
//     loss = loss_reg - (score_soft.sum() / Xbatch.N);
//
//
//
//     backward compute the gradients of Ws and bs
//     int aN, aD;
//     aN = h[hlayer_num].N;
//     aD = h[hlayer_num].D;
//     a[hlayer_num] = Matrix2<double>::zeros(aN, aD);
//     a[hlayer_num].set(Ind::arange(aN), ybatch.toInd(),1);
//     a[hlayer_num] = (score_exp_prob - a[hlayer_num]) / aN;
//
//     dW[hlayer_num] = a[hlayer_num-1].Trans().dot(a[hlayer_num]) + 2*reg*W[hlayer_num];
//     db[hlayer_num] = Matrix2<double>::ones(1,aN).dot(a[hlayer_num]);
//     int aN, aD;
//     aN = h[1].N;
//     aD = h[1].D;
//     a[1] = Matrix2<double>::zeros(aN, aD);
//     a[1].set(Ind::arange(aN), ybatch.toInd(),1);
//     a[1] = (score_exp_prob - a[1]) / aN;
//
//     dW[1] = a[0].Trans().dot(a[1]) + 2*reg*W[1];
//     db[1] = Matrix2<double>::ones(1,aN).dot(a[1]);
//
//     for(int i = hlayer_num-1; i > 0; i--)
//     {
//         relu_a = a[i+1].dot(W[i+1].Trans());
//         BPnet::grad_relu(relu_a, h[i]);
//         dW[i] = a[i-1].Trans().dot(relu_a) + 2*reg*W[i];
//         db[i] = Matrix2<double>::ones(1, relu_a.N).dot(relu_a);
//         a[i] = relu_a;
//         relu_a.data = NULL;
//     }
//     relu_a = a[1].dot(W[1].Trans());
//     BPnet::grad_relu(relu_a, a[0]);
//     dW[0] = Xbatch.Trans().dot(relu_a) + 2*reg*W[0];
//     db[0] = Matrix2<double>::ones(1, relu_a.N).dot(relu_a);
//
//
// #ifdef _DEBUG_
//     Matrix2<double> relu_a2;
//     relu_a = Matrix2<double>::randn(3,5);
//     relu_a.print();
//     relu_a2 = BPnet::activate_relu(relu_a);
//     relu_a2.print();
//     relu_a.print();
//     double fff;
//     std::cin >> fff;
// #endif
//
//
// compute numeric gradient
// #ifdef _DEBUG_
//     double orgval;
//     double interval;
//     double lossmh, lossph;
//     Matrix2<double> dWnum[hlayer_num+1];
//     Matrix2<double> dbnum[hlayer_num+1];
//
//     interval = 0.00001;
//
//     for(int i = 0; i < hlayer_num+1; i++)
//     {
//         dWnum[i].init(W[i].N, W[i].D);
//         for(int j = 0; j < W[i].ele_num; j++)
//         {
//             orgval = W[i].data[j];
//             W[i].data[j] = orgval + interval;
//             lossph = forward_loss(Xbatch, ybatch, reg);
//             W[i].data[j] = orgval - interval;
//             lossmh = forward_loss(Xbatch, ybatch, reg);
//             dWnum[i].data[j] = (lossph - lossmh) / (2 * interval);
//             W[i].data[j] = orgval;
//         }
//
//
//         dbnum[i].init(b[i].N, b[i].D);
//         for(int j = 0; j < b[i].ele_num; j++)
//         {
//             orgval = b[i].data[j];
//             b[i].data[j] = orgval + interval;
//             lossph = forward_loss(Xbatch, ybatch, reg);
//             b[i].data[j] = orgval - interval;
//             lossmh = forward_loss(Xbatch, ybatch, reg);
//             dbnum[i].data[j] = (lossph - lossmh) / (2 * interval);
//             b[i].data[j] = orgval;
//         }
//     }
//
//     double grad_errors_W[hlayer_num+1];
//     double grad_errors_b[hlayer_num+1];
//     for(int i = 0; i < hlayer_num+1; i++)
//     {
//         grad_errors_W[i] = (dWnum[i] - dW[i]).sum();
//         grad_errors_b[i] = (dbnum[i] - db[i]).sum();
//     }
//
//     cout << "numeric and calculus gradient errors are: " << endl;
//     for(int i = 0; i < hlayer_num+1; i++)
//     {
//         cout << grad_errors_W[i] << endl;
//         cout << grad_errors_b[i] << endl;
//     }
//
//
// #endif
//
//     return loss;
// }
//
//
//
//
// function:
// instruction:
// input:
// return:
//
// Matrix2<double> BPnet::activate_relu(Matrix2<double>& m)
// {
//     Matrix2<double> res;
//
//     res = m.copy();
//     for(int i = 0; i < m.ele_num; i++)
//         if(m.data[i] < 0)
//             res.data[i] = 0;
//
//     return std::move(res);
// }
//
//
//
//
// function:
// instruction:
// input:
// return:
//
// void BPnet::grad_relu(Matrix2<double>& da, Matrix2<double>& h)
// {
//     if(h.ele_num != da.ele_num || h.N != da.N || h.D != da.D)
//     {
//         cout << __FILE__ << ": " << __LINE__ << ":'da' and 'h' does not agree in shape so 'dh' cannot be computed" << endl;
//         exit(0);
//     }
//     for(int i = 0; i < h.ele_num; i++)
//         if(h.data[i] < 0)
//             da.data[i] = 0;
// }
//
//
//
//
// function:
// instruction:
// input:
// return:
//
// void BPnet::printWb()
// {
//     for(int i = 0; i < hlayer_num+1; i++)
//     {
//         cout << "W" << i << " and b" << i << " is: " << endl;
//         W[i].print();
//         b[i].print();
//     }
// }
//
//
//
//
// function:
// instruction:
// input:
// return:
//
// double BPnet::forward_loss(Matrix2<double>& Xbatch, Matrix2<double>& ybatch, const double reg)
// {
//     double forward_loss;
//     Matrix2<double> h[hlayer_num+1];
//     Matrix2<double> a[hlayer_num+1];
//
//     forward compute the loss function
//     h[0] = Xbatch.dot(W[0]) + b[0]; intput layer to the first hiden layer
//     a[0] = BPnet::activate_relu(h[0]);
//     for(int i = 1; i < hlayer_num; i++) the other hiden layers, all with relu
//     {
//         h[i] = a[i-1].dot(W[i]) + b[i];
//         a[i] = BPnet::activate_relu(h[i]);
//     }
//     h[hlayer_num] = a[hlayer_num-1].dot(W[hlayer_num]) + b[hlayer_num]; to the output layer
//
//     Matrix2<double> score_exp = (h[hlayer_num]).exp();
//     Matrix2<double> score_exp = (h[hlayer_num] - h[hlayer_num].max(1)).exp();
//     Matrix2<double> score_exp_prob = score_exp / score_exp.sum(1);
//     Matrix2<double> score_exp_correct = score_exp_prob(ybatch.toInd());
//     Matrix2<double> score_soft = score_exp_correct.log();
//     double loss_reg = 0;
//     for(int i = 0; i < hlayer_num+1; i++)
//         loss_reg += reg * (W[i].square().sum());
//
//     forward_loss = loss_reg - (score_soft.sum() / Xbatch.N);
//
//     return forward_loss;
// }
//
