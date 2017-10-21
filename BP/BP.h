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

#define ActFun_ReLu 0

#define OutFun_Softmax 100


/* structure of BPnet creation parameters
 * hidennodes, actfuns do not have to be stack memory, they can just be &a[0] or a which defined by int a[10]; */
typedef struct
{
    int *actfuns; // activation functions of each hiden layer
    int *hnode_num; // neuron numbers of each hiden layer
    int innodes; // input layer node numbers
    int outnodes; // output layer node numbers
    int hlayer_num; // number of hiden layers
    int outfun;

}BP_def_para;

/* structure of one single layer */
typedef struct
{
    int act_fun;
    Matrix W;
    Matrix b;
}hiden_layer;

/* structure of output layer */
typedef struct
{
    int out_fun;
    Matrix W;
    Matrix b;
}out_layer;


typedef struct
{
   double *y;
   double reg;
   Matrix X;
}train_data;

/* structure of a BP network */
typedef struct
{
    int innum;
    int hiden_layer_num;
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
void BP_train(BPnet *, train_data); 

// function to compute ReLu activation of a Matrix
void BP_ReLu(Matrix*);

// function to compute output of hiden layer activation node 
void BP_hlayer_actfun(Matrix*, int);

#endif
