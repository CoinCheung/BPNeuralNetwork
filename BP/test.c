#include<stdlib.h>
#include<stdio.h>
#include"BP.h"
#include"numeric.h"
#include"Matrix.h"
#include<cblas.h>

// a function used to try blas interface
void tryblas()
{
    const int N = 4;
    const int D = 5;
    const int C = 4;

    double a[4*5] = { 1, 2, 3, 4, 5, 6, 7, 8, 9,10, 11,12,13,14,15, 16,17,18,19,20 };
     double b[5*4] = { 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 };
    double c[4*4];

    const CBLAS_ORDER Order = CblasRowMajor;
    const CBLAS_TRANSPOSE Trans = CblasNoTrans;
    double alpha = 1;
    double beta = 0;
    int lda = D;
    int ldb = C;
    int ldc = C;


cblas_dgemm(Order, Trans, Trans, N, C, D, alpha, a, lda, b, ldb, beta, c, ldc);

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
            fprintf(stdout,"%lf, ", c[i*j]);
        fputs("\n",stdout);
    }
}




typedef struct
{
    int n;
    int *a;
} test_struct;

int main(void)
{
    test_struct ts;

    int m = 5;
    int *W = NULL;
    int (*a)[m] = NULL;
    int mm[10];

    a = (int(*)[m])W;

    ts.n = 4;
    ts.a = W;
    ts.a = mm;

    for(int i = 0; i < 1000; i++)
        W = (int*)malloc(sizeof(int)*10);

    fprintf(stdout, "RAND_MAX is: %d\n", RAND_MAX);

    /* ================================================ */
    // test Matrix
    Matrix mtx;
    Matrix res;

    mtx = Matrix_ones(3,3);
    Matrix_set(mtx,2,2,555);
    Matrix_print(mtx);

    res = Matrix_max(mtx,1);
    Matrix_print(res);
    Matrix_free(res);

    res = Matrix_min(mtx,0);
    Matrix_print(res);
    Matrix_free(res);

    Matrix_free(mtx);
///
    fputs("here\n",stdout);

    mtx = Matrix_range2(12, 24);
    Matrix_reshape(&mtx,3,4);
    Matrix_print(mtx);

    res = Matrix_max(mtx, 0);
    Matrix_print(res);
    Matrix_free(res);

    res = Matrix_max(mtx, 1);
    Matrix_print(res);
    Matrix_free(res);

    Matrix_free(mtx);

    fputs("try blas\n",stdout);
    tryblas();
///
    fputs("\n //////// \ntry matrix multiplication\n\n",stdout);
    Matrix mtx1, mtx2;

    mtx1 = Matrix_range(9);
    mtx2 = Matrix_range(9);
    Matrix_reshape(&mtx1,3,3);
    Matrix_reshape(&mtx2,3,3);
    fputs("mtx1 is: \n",stdout);
    Matrix_print(mtx1);
    fputs("mtx2 is: \n",stdout);
    Matrix_print(mtx2);
    fputs("dot is: \n",stdout);
    res = Matrix_dot(mtx1, mtx2);
    Matrix_print(res);
    Matrix_free(mtx1);
    Matrix_free(mtx2);
    Matrix_free(res);

    mtx1 = Matrix_range(9);
    mtx2 = Matrix_range2(3,6);
    Matrix_reshape(&mtx1,3,3);
    Matrix_reshape(&mtx2,3,1);
    fputs("mtx1 is: \n",stdout);
    Matrix_print(mtx1);
    fputs("mtx2 is: \n",stdout);
    Matrix_print(mtx2);
    fputs("dot is: \n",stdout);
    res = Matrix_dot(mtx1, mtx2);
    Matrix_print(res);
    Matrix_free(mtx1);
    Matrix_free(mtx2);
    Matrix_free(res);

    mtx1 = Matrix_range2(3,6);
    mtx2 = Matrix_range(9);
    Matrix_reshape(&mtx1,1,3);
    Matrix_reshape(&mtx2,3,3);
    fputs("mtx1 is: \n",stdout);
    Matrix_print(mtx1);
    fputs("mtx2 is: \n",stdout);
    Matrix_print(mtx2);
    fputs("dot is: \n",stdout);
    res = Matrix_dot(mtx1, mtx2);
    Matrix_print(res);
    Matrix_free(mtx1);
    Matrix_free(mtx2);
    Matrix_free(res);

    mtx1 = Matrix_range2(4,8);
    mtx2 = Matrix_range(4);
    Matrix_reshape(&mtx1,4,1);
    Matrix_reshape(&mtx2,1,4);
    fputs("mtx1 is: \n",stdout);
    Matrix_print(mtx1);
    fputs("mtx2 is: \n",stdout);
    Matrix_print(mtx2);
    fputs("dot is: \n",stdout);
    res = Matrix_dot(mtx1, mtx2);
    Matrix_print(res);
    Matrix_free(mtx1);
    Matrix_free(mtx2);
    Matrix_free(res);

    mtx1 = Matrix_range2(4,8);
    mtx2 = Matrix_range(4);
    Matrix_reshape(&mtx1,1,4);
    Matrix_reshape(&mtx2,4,1);
    fputs("mtx1 is: \n",stdout);
    Matrix_print(mtx1);
    fputs("mtx2 is: \n",stdout);
    Matrix_print(mtx2);
    fputs("dot is: \n",stdout);
    res = Matrix_dot(mtx1, mtx2);
    Matrix_print(res);
    Matrix_free(mtx1);
    Matrix_free(mtx2);
    Matrix_free(res);

///
    fputs("\n //////// \ntry matrix add\n\n",stdout);
    mtx1 = Matrix_range2(4,8);
    mtx2 = Matrix_range(16);
    Matrix_reshape(&mtx1,4,1);
    Matrix_reshape(&mtx2,4,4);
    fputs("mtx1 is: \n",stdout);
    Matrix_print(mtx1);
    fputs("mtx2 is: \n",stdout);
    Matrix_print(mtx2);
    fputs("addition result is: \n",stdout);
    res = Matrix_add(mtx1, mtx2);
    Matrix_print(res);
    Matrix_free(mtx1);
    Matrix_free(mtx2);
    Matrix_free(res);

    mtx1 = Matrix_range2(4,8);
    mtx2 = Matrix_range(16);
    Matrix_reshape(&mtx1,1,4);
    Matrix_reshape(&mtx2,4,4);
    fputs("mtx1 is: \n",stdout);
    Matrix_print(mtx1);
    fputs("mtx2 is: \n",stdout);
    Matrix_print(mtx2);
    fputs("addition result is: \n",stdout);
    res = Matrix_add(mtx1, mtx2);
    Matrix_print(res);
    Matrix_free(mtx1);
    Matrix_free(mtx2);
    Matrix_free(res);

    mtx1 = Matrix_range(16);
    mtx2 = Matrix_range2(4,8);
    Matrix_reshape(&mtx1,4,4);
    Matrix_reshape(&mtx2,1,4);
    fputs("mtx1 is: \n",stdout);
    Matrix_print(mtx1);
    fputs("mtx2 is: \n",stdout);
    Matrix_print(mtx2);
    fputs("addition result is: \n",stdout);
    res = Matrix_add(mtx1, mtx2);
    Matrix_print(res);
    Matrix_free(mtx1);
    Matrix_free(mtx2);
    Matrix_free(res);

    mtx1 = Matrix_range(16);
    mtx2 = Matrix_range2(4,8);
    Matrix_reshape(&mtx1,4,4);
    Matrix_reshape(&mtx2,4,1);
    fputs("mtx1 is: \n",stdout);
    Matrix_print(mtx1);
    fputs("mtx2 is: \n",stdout);
    Matrix_print(mtx2);
    fputs("addition result is: \n",stdout);
    res = Matrix_add(mtx1, mtx2);
    Matrix_print(res);
    Matrix_free(mtx1);
    Matrix_free(mtx2);
    Matrix_free(res);

    mtx1 = Matrix_range(9);
    mtx2 = Matrix_range2(3,12);
    Matrix_reshape(&mtx1,3,3);
    Matrix_reshape(&mtx2,3,3);
    fputs("mtx1 is: \n",stdout);
    Matrix_print(mtx1);
    fputs("mtx2 is: \n",stdout);
    Matrix_print(mtx2);
    fputs("addition result is: \n",stdout);
    res = Matrix_add(mtx1, mtx2);
    Matrix_print(res);
    Matrix_free(mtx1);
    Matrix_free(mtx2);
    Matrix_free(res);

    fputs("here is: \n",stdout);
    mtx1 = Matrix_range(9);
    mtx2 = Matrix_range2(3,12);
    Matrix_reshape(&mtx1,3,3);
    Matrix_reshape(&mtx2,3,3);
    fputs("mtx1 is: \n",stdout);
    Matrix_print(mtx1);
    fputs("mtx2 is: \n",stdout);
    Matrix_print(mtx2);
    fputs("addition result is: \n",stdout);
    Matrix_add_by(&mtx1, mtx2);
    Matrix_print(res);
    Matrix_free(mtx1);
    Matrix_free(mtx2);
    /* ================================================ */
    // nn test codes

    BPnet bn;
    BP_def_para para;
    int actfuns[1] = {ActFun_ReLu};
    int hidenodes[1] = {50};

    // BPnet setup parameters
    fputs("initialize network parameters\n",stdout);
    para.innodes = 3072;
    para.outnodes = 10;
    para.hlayer_num = 1;
    para.outfun = OutFun_Softmax;
    para.actfuns = &actfuns[0];
    para.hnode_num = &hidenodes[0];

    while(1)
    {
        fputs("creating BP network\n",stdout);
        bn = BP_create(para);

        fputs("free all the memories\n",stdout);
        BP_free(bn);

        break;
    }











    /* ================================================ */

    return 0;
}
