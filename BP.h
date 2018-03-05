#ifndef _BPNET_H_
#define _BPNET_H_

#include"Matrix/Matrix.h"
#include"Layers/Layer.h"
#include"Layers/ReLU.h"
#include"Layers/FullyConnected.h"
#include"Layers/Softmax.h"
#include<vector>
#include<memory>



typedef std::shared_ptr<Matrix2<double>> MATRIX;
typedef std::shared_ptr<Layer> LAYER;
typedef std::shared_ptr<FC_Layer> FullyConnected;
typedef std::shared_ptr<ReLU_Layer> RELU;


// class of BPnet
class BPnet
{
    public:
        int in_size;
        int out_size;
        int hlayer_num;
        int *hiden_size;
        std::vector<double> loss;
        Matrix2<double> *W;
        Matrix2<double> *b;
        Matrix2<double> *dW;
        Matrix2<double> *db;

//////////////
        BPnet(std::vector<int>& layer_nums);
        std::vector<LAYER> layers;
        Softmax softmax;
        MATRIX input;
//////////////

        void train();
        MATRIX forward(MATRIX&);
        MATRIX backward(MATRIX&);

        /* constructions */
        BPnet();
        BPnet(const int is, const int hn, int *hs, const int os, const double std=1e-4);
        ~BPnet();

        void train(Matrix2<double>& X, Matrix2<double>& y, Matrix2<double>& Xval, Matrix2<double>& yval, int batch_size = 200, const double reg = 5e-6, double learning_rate = 1e-3, const double lr_decay = 0.95, const int num_iter = 100);

        double loss_softmax(Matrix2<double>& Xbatch, Matrix2<double>& ybatch, const double reg);
        static Matrix2<double> activate_relu(Matrix2<double>& m);
        static void grad_relu(Matrix2<double> &da, Matrix2<double>& h);

        void printWb();
        double forward_loss(Matrix2<double>& Xbatch, Matrix2<double>& ybatch, const double reg);
};


#endif
