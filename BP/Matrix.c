#include"Matrix.h"



/* function:
 * instruction: 
 * input:
 * return:
 *  */
Matrix Matrix_dot(Matrix a, Matrix b)
{
    const int N = a.N;
    const int D = a.D;
    const int C = b.N;
    const int M = b.D;
    Matrix res;

    // check if two matrices not match in shape
    if(D != C)
    {
        fputs("Error: size of the two matrices not match\n", stdout);
        exit(0);
    }

    res = Matrix_create(N,M);

    // scenario where a and b are vectors, compute their outer product
    if(D == 1)
        cblas_dger(CblasRowMajor, N, M, 1, a.data, 1, b.data, 1, res.data, M);
    
    // scenario where a and b are vectors, and inner product computed
    else if(N == 1 && M == 1)
        res.data[0] = cblas_ddot(D, a.data, 1, b.data, 1);

    // scenario where a is vector and b is matrix
    else if(N == 1 && M != 1)
        cblas_dgemv(CblasRowMajor, CblasTrans, C, M, 1, b.data, M, a.data, 1, 0, res.data, 1);

    // scenario where a is matrix and b is vector
    else if(M == 1 && N != 1)
        cblas_dgemv(CblasRowMajor, CblasNoTrans, N, D, 1, a.data, D, b.data, 1, 0, res.data, 1);

    // scenario where a and b are matrices
    else
        cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, M, D, 1, a.data, D, b.data, M, 0, res.data, M);

    return res;
}



/* function:
 * instruction: 
 * input:
 * return:
 *  */
inline void Matrix_dot_by(Matrix *a, Matrix b)
{
    Matrix res;

    res = Matrix_dot(*a, b);
    Matrix_free(*a);
    *a = res;
}


/* function:
 * instruction: 
 * input:
 * return:
 *  */
inline void Matrix_free(Matrix m)
{
    free(m.data);
}



/* function:
 * instruction: create a Matrix with given size
 * input:
 * return:
 *  */
inline Matrix Matrix_create(const int N, const int D)
{
    Matrix res;

    res.N = N;
    res.D = D;
    res.ele_num = N*D;
    res.data = (double*)malloc(sizeof(double)*res.ele_num);
    memset(res.data, 0, sizeof(double)*res.ele_num);

    return res;
}




/* function:
 * instruction: 
 * input: a Matrix m, and the axis along which maximal is computed
 * return:
 *  */
Matrix Matrix_max(const Matrix m, const int axis)
{
    Matrix res;
    const int N = m.N;
    const int D = m.D;
    const double (*d)[D] = (double(*)[D])m.data;
    
    if(m.ele_num == 0)
    {
        perror("Matrix has combined size of 0!\n");
        exit(0);
    }

    // if calculate maximal through the director of axis = 0
    if(axis == 0)
    {
        if(N == 1)
            res = Matrix_copy(m);
        else
        {
            res = Matrix_create(1,D);
            for(int i = 0; i < D; i++)
            {
                res.data[i] = d[0][i];
                for(int j = 1; j < N; j++)
                    if(d[j][i] > res.data[i])
                        res.data[i] = d[j][i];
            }
        }
    }
    // if calculate maximal through the director of axis = 1
    if(axis == 1)
    {
        if(D == 1)
            res = Matrix_copy(m);
        else
        {
            res = Matrix_create(N,1);
            for(int i = 0; i < N; i++)
            {
                res.data[i] = d[i][0];
                for(int j = 1; j < D; j++)
                    if(d[i][j] > res.data[i])
                        res.data[i] = d[i][j];
            }
        }
    }

    return res;
}




/* function:
 * instruction: 
 * input: a Matrix m, and the axis along which maximal is computed
 * return:
 *  */
Matrix Matrix_min(const Matrix m, int axis)
{
    Matrix res;
    const int N = m.N;
    const int D = m.D;
    double (*d)[D] = (double(*)[D])m.data;
    
    if(m.ele_num == 0)
    {
        perror("Matrix has combined size of 0!\n");
        exit(0);
    }

    // if calculate maximal through the director of axis = 0
    if(axis == 0)
    {
        if(N == 1)
            res = Matrix_copy(m);
        else
        {
            res = Matrix_create(1,D);
            for(int i = 0; i < D; i++)
            {
                res.data[i] = d[0][i];
                for(int j = 1; j < N; j++)
                    if(d[j][i] < res.data[i])
                        res.data[i] = d[j][i];
            }
        }
    }

    // if calculate maximal through the director of axis = 1
    if(axis == 1)
    {
        if(D == 1)
            res = Matrix_copy(m);
        else
        {
            res = Matrix_create(N,1);
            for(int i = 0; i < N; i++)
            {
                res.data[i] = d[i][0];
                for(int j = 1; j < D; j++)
                    if(d[i][j] < res.data[i])
                        res.data[i] = d[i][j];
            }
        }
    }

    return res;
}


/* function:
 * instruction: return a deep copy of a given Matrix
 * input: 
 * return:
 *  */
inline Matrix Matrix_copy(const Matrix m)
{
    Matrix res;

    res = Matrix_create(m.N,m.D);
    memcpy(res.data, m.data, sizeof(double)*m.ele_num);

    return res;
}



/* function:
 * instruction: 
 * input: 
 * return:
 *  */
inline void Matrix_set(const Matrix m, const int row, const int col, const double val)
{
    double (*d)[m.D] = (double(*)[m.D])m.data;

    d[row][col] = val;
}



/* function:
 * instruction: 
 * input: 
 * return:
 *  */
void Matrix_print(const Matrix m)
{
    const int N = m.N;
    const int D = m.D;
    double (*d)[D] = (double(*)[D])m.data;

    fputs("[\n",stdout);
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < D; j++)
            fprintf(stdout, "%lf, ", d[i][j]);
        fputs("\n",stdout);
    }
    fputs("]\n",stdout);
    fputs("\n",stdout);
}



/* function:
 * instruction: 
 * input: 
 * return:
 *  */
inline void Matrix_reshape(Matrix * const m, const int N, const int D)
{
    if(N*D != m->ele_num)
    {
        fputs("ERROR: shape assigned to reshape() need to agree with number of matrix units\n",stdout);
        exit(0);
    }
    m->N = N;
    m->D = D;
    m->ele_num = N * D;
}




/* function:
 * instruction: 
 * input: 
 * return:
 *  */
Matrix Matrix_ones(const int N, const int D)
{
    Matrix res;

    res = Matrix_create(N,D);
    for(long i = 0; i < res.ele_num; i++)
        res.data[i] = 1;

    return res;
}



/* function:
 * instruction: 
 * input: 
 * return:
 *  */
Matrix Matrix_zeros(const int N, const int D)
{
    Matrix res;

    res = Matrix_create(N,D);
    memset(res.data, 0, sizeof(double)*res.ele_num);

    return res;
}



/* function:
 * instruction: 
 * input: 
 * return:
 *  */
Matrix Matrix_range(const int a)
{
    Matrix res;
    double val;

    val = 0;
    res = Matrix_create(1,a);
    for(int i = 0; i < a; i++, val++)
        res.data[i] = val;

    return res;
}




/* function:
 * instruction: 
 * input: 
 * return:
 *  */
Matrix Matrix_range2(const int a, const int b)
{
    Matrix res;
    double val;

    val = a;
    res = Matrix_create(1,b-a);
    for(int i = 0, val = a; i < b-a; i++, val++)
        res.data[i] = val;

    return res;
}



/* function:
 * instruction: 
 * input: 
 * return:
 *  */
Matrix Matrix_add(Matrix a, Matrix b) 
{
    const int N1 = a.N;
    const int D1 = a.D;
    const int N2 = b.N;
    const int D2 = b.D;
    const int Dr = (D1>D2?D1:D2);
    const int Nr = (N1>N2?N1:N2);
    Matrix res;
    double temp;
    double (*p1)[D1], (*p2)[D2], (*pr)[Dr];

    // check if empty matrix are given
    if(N1*N2*D1*D2 == 0)
    {
        fputs("Error: Matrix input of Matrix_add() cannot be Empty\n", stdout);
        exit(0);
    }

    // initial variables
    res = Matrix_create(Nr, Dr);

    p1 = (double(*)[D1])a.data;
    p2 = (double(*)[D2])b.data;
    pr = (double(*)[Dr])res.data;

    // two matrix have same shape
    if(N1 == N2 && D1 == D2)
        for(long i = 0; i < a.ele_num; i++)
            res.data[i] = a.data[i] + b.data[i];

    // a vertical vector plus a Matrix
    else if(N1 == N2 && D1 == 1)
        for(int i = 0; i < N1; i++)
        {
            temp = a.data[i];
            for(int j = 0; j < Dr; j++)
                pr[i][j] = temp + p2[i][j];
        }
            
    // a Matrix plus a vertical vector 
    else if(N1 == N2 && D2 == 1)
        for(int i = 0; i < N1; i++)
        {
            temp = b.data[i];
            for(int j = 0; j < Dr; j++)
                pr[i][j] = temp + p1[i][j];
        }

    // a horizontal vector plus a Matrix
    else if(D1 == D2 && N1 == 1)
        for(int i = 0; i < D1; i++)
        {
            temp = a.data[i];
            for(int j = 0; j < Nr; j++)
                pr[j][i] = temp + p2[j][i];
        }

    // a Matrix plus a horizontal vector 
    else if(D1 == D2 && N2 == 1)
        for(int i = 0; i < D1; i++)
        {
            temp = b.data[i];
            for(int j = 0; j < Nr; j++)
                pr[j][i] = temp + p1[j][i];
        }

    else
    {
        fputs("Error: the input matrices of Matrix_add() should have associated shape\n",stdout);
        exit(0);
    }

    return res;
}



/* function:
 * instruction: 
 * input: 
 * return:
 *  */
void Matrix_add_by(Matrix *a, Matrix b) 
{
    Matrix res;

    res = Matrix_add(*a, b);
    Matrix_free(*a);
    *a = res;
}


