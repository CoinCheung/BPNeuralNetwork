#ifndef _BP_H_
#define _BP_H_

/* A lib that provides basic Matrix computation written by Coin */

/* ===========================================================
 * includes
 * =========================================================== */

#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#include"numeric.h"
#include"Matrix.h"



/* ===========================================================
 * types and macros
 * =========================================================== */

/* macros */
#define ActFun_ReLu 0

#define OutFun_No 100
#define OutFun_Softmax 101

#define WBinit_Gaussian 200
#define WBinit_Xavier 201

#define LossFun_Softmax 300
#define LossFun_SVM 301

/* structure of BPnet creation parameters
 * hidennodes, actfuns do not have to be stack memory, they can just be &a[0] or a which defined by int a[10]; */
typedef struct
{
    int *actfuns; // activation functions of each hiden layer
    int *hnode_num; // neuron numbers of each hiden layer
    int innodes; // input layer node numbers
    int outnodes; // output layer node numbers
    int hlayer_num; // number of hiden layers
    int outfun; // assigned the type of out fun
    int Wb_init;

}BP_def_para;

/* structure of one single layer */
typedef struct
{
    int act_fun;
    int ini_method;
    Matrix W;
    Matrix b;
}hiden_layer;

/* structure of output layer */
typedef struct
{
    int out_fun;
    int ini_method;
    Matrix W;
    Matrix b;
}out_layer;

/* structure of train data */
typedef struct
{
   double reg;
   double Wbstd;
   int LossFun;
   Matrix X;
   Matrix y;
   
}train_data;

/* structure of a BP network */
typedef struct
{
    int innum;
    int hiden_layer_num;
    double loss; // loss of one forward computation
    int Wgnum; // number of W gradients
    Matrix *Wgrad; // array of W gradients
    int bgnum; // number of b gradients

    Matrix *bgrad; // array of b gradients
    hiden_layer *hlayers;
    out_layer out;
} BPnet;



/* ===========================================================
 * function definitions
 * =========================================================== */

 // create a BP network of given structure 
BPnet BP_create(const BP_def_para);

// free the memory the BP network takes
void BP_free(BPnet); 

// train the BP network with samples
void BP_train(BPnet *, const train_data); 

// function to compute ReLu activation of a Matrix
void BP_ReLu(Matrix*);

// function to compute output of hiden layer activation node 
void BP_hlayer_actfun(Matrix*, const int);

// initialize the Weight and bias Matrix with certain method
void BP_initWb(Matrix *m, const int, const int);

// calculating Loss function according to the scores matrix
Matrix BP_Loss(BPnet *, const train_data);

#endif
