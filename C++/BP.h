#ifndef _BPNET_H_
#define _BPNET_H_

/* ===============================================================
 * includes
 * =============================================================== */
#include"Matrix.h"
#include<vector>




/* ===============================================================
 * usings
 * =============================================================== */



/* ===============================================================
 * definitions
 * =============================================================== */

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
