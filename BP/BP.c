#include"BP.h"

/* Tips: 
 * 1. 这里关于权值W b 是按照CS231n来做了，为了验证准确性，后面可以改成Xavier分布试试
 *  */

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
    res.hlayers[0].ini_method = para.Wb_init;
    res.hlayers[0].b = Matrix_create(1, hidenums[0]);
    for(int i = 1; i < hiden_num; i++)
    {
        res.hlayers[i].W = Matrix_create(hidenums[i-1],hidenums[i]);
        res.hlayers[i].act_fun = actfun[i];
        res.hlayers[i].ini_method = para.Wb_init;
        res.hlayers[i].b = Matrix_create(1,hidenums[i]);
    }

    // create and connect output layer
    res.out.W = Matrix_create(hidenums[hiden_num-1], outnum);
    res.out.out_fun = outfun;
    res.out.ini_method = para.Wb_init;
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
void BP_train(BPnet *bn, const train_data td)
{
    const int N = td.X.N;
    const int D = td.X.D;
    Matrix scores;

    // check if input shape fit the network well
    if(bn->innum != D)
    {
        fputs("ERROR: the train data shape does not fit the network well\n",stdout);
        fprintf(stdout, "\t in %s: %d\n", __FILE__, __LINE__);
        exit(0);
    }
    if(td.y.ele_num != N)
    {
        fprintf(stdout, "ERROR in %s: %d: the number of samples does not agree with the number of labels\n",__FILE__, __LINE__);
        exit(0);
    }

    // train data pre-processing


    // initalize the network W and b matrices
    for(int i = 0; i < bn->hiden_layer_num; i++)
    {
        BP_initWb(&(bn->hlayers[i].W), bn->hlayers[i].ini_method, N);
        BP_initWb(&(bn->hlayers[i].b), bn->hlayers[i].ini_method, N);
        fprintf(stdout, "Wb of hlayer %d is:\n");
        Matrix_print(bn->hlayers[i].W);
        Matrix_print(bn->hlayers[i].b);
    }
    BP_initWb(&(bn->out.W), bn->out.ini_method, N);
    BP_initWb(&(bn->out.b), bn->out.ini_method, N);

    fprintf(stdout, "Wb of out layer is:\n");
    Matrix_print(bn->out.W);
    Matrix_print(bn->out.b);
    

    // forward computation, and compute Loss function
    scores = BP_Loss(bn, td);


    Matrix_free(scores);

}




/* function:
 *
 * input:
 * return:
 *  */
inline void BP_hlayer_actfun(Matrix *m, const int func)
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
inline void BP_ReLu(Matrix *a)
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
void BP_initWb(Matrix *m, const int initMethod, const int sampleNum)
{
    double Gaussian_Num;

    // initialize the matrix with gaussian random number
    if(initMethod == WBinit_Gaussian) 
    {
        Gaussian_Num = 1/sqrt(sampleNum);
        for(long i = 0; i < m->ele_num; i++)
            m->data[i] = gaussian_rand(0,Gaussian_Num);
    }
}



/* function:
 * instruction: 
 * input: the scores matrix with shape (N,D), where N is the number of training samples, and D is the category numbers; y is the practical output array; Fun assigns which sort of Loss function is used
 * return: the score Matrix
 *  */
Matrix BP_Loss(BPnet *bn, const train_data td)
{
    Matrix X = td.X;
    Matrix y = td.y;
    double loss;
    Matrix hiden_output[bn->hiden_layer_num];
    Matrix scores;

    const int N = X.N;
    const int D = bn->out.W.D;
    Matrix sc;
    Matrix score_sum;
    Matrix score_correct;
    Matrix ind;
    Matrix score_sum_log;
    Matrix temp;
    Matrix max;

/* 
 * following is computing the scores Matrix along the forward path
 */
    scores = Matrix_copy(X);
    for(int i = 0; i < bn->hiden_layer_num; i++)
    {
        Matrix_dot_by(&scores, bn->hlayers[i].W);
        Matrix_add_by(&scores, bn->hlayers[i].b);
        hiden_output[i] = Matrix_copy(scores);
        BP_hlayer_actfun(&scores, bn->hlayers[i].act_fun);
    }

    Matrix_dot_by(&scores, bn->out.W);
    Matrix_add_by(&scores, bn->out.b); // here scores is the score matrix

    sc = Matrix_copy(scores);

    fputs("scores matrix is: \n",stdout);
    Matrix_print(scores);

/* 
 * When the Loss function is assigned to be softmax loss funtion
*/
    if(td.LossFun == LossFun_Softmax)
    {
    /* 
     * following is computing the loss scaler of the forward path
     */
        max = Matrix_max_axis(sc,1);
        Matrix_sign_reverse(&max);
        Matrix_add_by(&sc, max);
        Matrix_exp_ele_by(&sc);
        score_sum = Matrix_sum_axis(sc, 1);

        ind = Matrix_range(N);
        score_correct = Matrix_pick_eles(sc,ind,y);
        score_sum_log = Matrix_log_ele(score_sum);
        loss = Matrix_sum_all(score_sum_log) - Matrix_sum_all(score_correct);
        loss /= N;

        for(int i = 0; i < bn->hiden_layer_num; i++)
        {
            temp = Matrix_copy(bn->hlayers[i].W);
            Matrix_multi_by(&temp, temp);
            loss += td.reg * Matrix_sum_all(temp);
            Matrix_free(temp);
        }
        temp = Matrix_copy(bn->out.W);
        Matrix_multi_by(&temp, temp);
        loss += td.reg * Matrix_sum_all(temp);
        Matrix_free(temp);

        bn->loss = loss;
        fprintf(stdout, "the softmax loss function is: %lf \n", loss);

    /* 
     * following is computing the gradient of Ws and bs in the forward path
     */
        // Matrix dLdS =



    }

    // free temporary variables assigned from the heap
    for(int i = 0; i < bn->hiden_layer_num; i++)
        Matrix_free(hiden_output[i]);

    Matrix_free(score_sum);
    Matrix_free(score_correct);
    Matrix_free(scores);
    Matrix_free(ind);
    Matrix_free(max);
    Matrix_free(sc);

    return scores;
}
