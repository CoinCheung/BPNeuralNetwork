#ifndef _BPNET_H_
#define _BPNET_H_

/* ===============================================================
 * includes
 * =============================================================== */
#include"Matrix.h"




/* ===============================================================
 * usings
 * =============================================================== */



/* ===============================================================
 * definitions
 * =============================================================== */
class BPnet
{
    public:
        int in_num;
        int out_num;
        int hlayer_num;
        Matrix2<double> *W;
        Matrix2<double> *b;

        /* constructions */
        BPnet();
        BPnet(const int in, const int hn, const int on);

        void train(Matrix2<double> X, Matrix2<double> y, Matrix2<double> Xval, Matrix2<double> yval, double learning_rate = 1e-3);

};


#endif
