#include"BP.h"


/* function:
 *
 * input:
 * return:
 *  */
BPnet BP_create(const BP_def_para para) 
{
    int innum = para.innodes;
    int outnum = para.outnodes;
    int hiden_num = para.hlayer_num;
    int *hidenums = para.hnode_num;
    int *actfun = para.actfuns;
    int outfun = para.outfun;

    BPnet res;

    res.innum = innum;
    res.hiden_layer_num = hiden_num;

    // create and connect hiden layers
    res.hlayers = (hiden_layer*)malloc(sizeof(hiden_layer)*hiden_num);

    res.hlayers[0].W = Matrix_create(innum, hidenums[0]);
    res.hlayers[0].act_fun = actfun[0];
    res.hlayers[0].b = Matrix_create(1, hidenums[0]);
    for(int i = 1; i < hiden_num; i++)
    {
        res.hlayers[i].W = Matrix_create(hidenums[i-1],hidenums[i]);
        res.hlayers[i].act_fun = actfun[i];
        res.hlayers[i].b = Matrix_create(1,hidenums[i]);
    }

    // create and connect output layer
    res.out.W = Matrix_create(hidenums[hiden_num-1], outnum);
    res.out.out_fun = outfun;
    res.out.b = Matrix_create(1, outnum);

    return res;
}


/* function:
 *
 * input:
 * return:
 *  */
void BP_free(BPnet bn)
{
    for(int i = 0; i < bn.hiden_layer_num; i++)
    {
        Matrix_free(bn.hlayers[i].W);
        Matrix_free(bn.hlayers[i].b);
        free(bn.hlayers);
    }
    free(bn.hlayers);

    Matrix_free(bn.out.W);
    Matrix_free(bn.out.b);
}


/* function:
 *
 * input:
 * return:
 *  */
void BP_train(BPnet *bn, train_data td)
{
    Matrix X = Matrix_copy(td.X);
    double *y = td.y;
    const int N = X.N;
    const int D = X.D;
    const int M = bn->out.W.D;
    double scores[M];
    Matrix hiden_output[bn->hiden_layer_num];
    Matrix temp, outmtx;

    // check if input shape fit the network well
    if(bn->innum != D)
    {
        fputs("ERROR: the train data shape does not fit the network well",stdout);
        exit(0);
    }

    // train data pre-processing

    // forward computation
    temp = Matrix_copy(X);
    /* for(int i = 0; i < bn->hiden_layer_num; i++) */
    /* { */
    /*     Matrix_dot_by(&temp,bn->hlayers[i].W); */
    /*     Matrix_add_by(&temp,bn->hlayers[i].b); */
    /*     hiden_output[i] = Matrix_copy(temp); */
    /*     BP_hlayer_actfun(&temp, bn->hlayers[i].act_fun); */
    /* } */
    /*  */
    /* Matrix_dot_by(&temp, bn->out.W); */




    Matrix_free(X);
    Matrix_free(temp);
    for(int i = 0; i < bn->hiden_layer_num; i++)
        Matrix_free(hiden_output[i]);
}




/* function:
 *
 * input:
 * return:
 *  */
inline void BP_hlayer_actfun(Matrix *m, int func)
{
    if(func == ActFun_ReLu)
        BP_ReLu(m);
         

    else
    {
        fprintf(stdout, "Error: no such activation function %d as assigned\n", func);
        exit(0);
    }
}


/* function:
 *
 * input:
 * return:
 *  */
void BP_ReLu(Matrix *a)
{
    for(long i = 0; i < a->ele_num; i++)
        if(a->data[i] < 0)
            a->data[i] = 0;
}


/* function:
 *
 * input:
 * return:
 *  */
BP_cal_outscores(Matrix outmtx, double * res, int scorefun);

