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
    // memset(res.data, 0, sizeof(double)*res.ele_num);

    return res;
}




/* function:
 * instruction: 
 * input: a Matrix m, and the axis along which maximal is computed
 * return:
 *  */
Matrix Matrix_max_axis(const Matrix m, const int axis)
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
Matrix Matrix_min_axis(const Matrix m, int axis)
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
        fprintf(stdout, "%s: %d: shape assigned to reshape() need to agree with number of matrix units\n", __FILE__, __LINE__);
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

    // if a bias added to a matrix
    else if(N1 == 1 && D1 == 1)
        for(long i = 0; i < b.ele_num; i++)
            res.data[i] = a.data[0] + b.data[i];

    // if a matrix added to a bias
    else if(N2 == 1 && D2 == 1)
        for(long i = 0; i < a.ele_num; i++)
            res.data[i] = b.data[0] + a.data[i];

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



/* function:
 * instruction: calculate hadmard product of two matrices if they have same shape. if the second input matrix is a vector whose shape fits the first matrix along some dimension, then the vector is augmented to a matrix with the same shape as the first one and hadmard product is computed.
 * No scaling operation is expected by this function
 * input: 
 * return:
 *  */
void Matrix_multi_by(Matrix* a, const Matrix b)
{
    double temp;
    long pos;

    // scenario where two matrices have same shape
    if(a->N == b.N && a->D == b.D) 
        for(long i = 0; i < a->ele_num; i++)
            a->data[i] *= b.data[i];

    // scenario where a is a vertical matrix and b is a Matrix
    else if(b.D == 1 && a->N == b.N)
    {
        pos = 0;
        for(int i = 0; i < b.N; i++)
        {
            temp = b.data[i];
            for(int j = 0; j < a->D; j++, pos++)
                a->data[pos] *= temp; 
        }
    }

    // scenario where a is a matrix and b is a horizontal vector
    else if(b.N == 1 && a->D == b.D)
    {
        for(int i = 0; i < b.D; i++)
        {
            temp = b.data[i];
            pos = i;
            for(int j = 0; j < a->N; j++, pos+=a->D)
                a->data[pos] *= temp;
        }
    }

    else
    {
        fputs("ERROR: Matrix_multi_by() requires input matrices have identical shapes\n", stdout);
        exit(0);
    }
}



/* function:
 * instruction: same operation as multi_by(), except that original matrix will not be changed and a new one returned.
 * input: 
 * return:
 *  */
Matrix Matrix_multi(const Matrix a, const Matrix b)
{
    Matrix res;

    // if a is a vector, then multiply it to matrix b
    if(a.N == 1 || a.D == 1)
    {
        res = Matrix_copy(b);
        Matrix_multi_by(&res, a);
    }

    // if a is not a vector, then call multi_by() to multiply b directly to it
    else
    {
        res = Matrix_copy(a);
        Matrix_multi_by(&res, b);
    }

    return res;
}



/* function:
 * instruction: calculate hadmard division of two matrices if they have same shape. if the second input matrix is a vector whose shape fits the first matrix along some dimension, then the vector is augmented to a matrix with the same shape as the first one and hadmard division is computed.
 * No scaling operation is expected by this function
 * input: 
 * return:
 *  */
void Matrix_divide_by(Matrix* a, const Matrix b)
{
    double temp;
    long pos;

    // scenario where two matrices have same shape
    if(a->N == b.N && a->D == b.D) 
        for(long i = 0; i < a->ele_num; i++)
            a->data[i] /= b.data[i];

    // scenario where a is a vertical matrix and b is a Matrix
    else if(b.D == 1 && a->N == b.N)
    {
        pos = 0;
        for(int i = 0; i < b.N; i++)
        {
            temp = b.data[i];
            for(int j = 0; j < a->D; j++, pos++)
                a->data[pos] /= temp; 
        }
    }

    // scenario where a is a matrix and b is a horizontal vector
    else if(b.N == 1 && a->D == b.D)
    {
        for(int i = 0; i < b.D; i++)
        {
            temp = b.data[i];
            pos = i;
            for(int j = 0; j < a->N; j++, pos+=a->D)
                a->data[pos] /= temp;
        }
    }

    else
    {
        fprintf(stdout,"%s: %d: Matrix_divide_by() requires input matrices have identical shapes\n", __FILE__, __LINE__);
        exit(0);
    }
}


/* function:
 * instruction: same operation as divide_by(), except that original matrix will not be changed and a new one returned.
 * input: 
 * return:
 *  */
Matrix Matrix_divide(const Matrix a, const Matrix b)
{
    Matrix res;

    // if a is a vector, then multiply it to matrix b
    if(a.N == 1 || a.D == 1)
    {
        res = Matrix_copy(b);
        Matrix_divide_by(&res, a);
    }

    // if a is not a vector, then call multi_by() to multiply b directly to it
    else
    {
        res = Matrix_copy(a);
        Matrix_divide_by(&res, b);
    }

    return res;
}



/* function:
 * instruction: scale all the elements of a matrix with simply a scaler, the operation is directly implemented on the original matrix
 * input: 
 * return:
 *  */
inline void Matrix_scale_by(Matrix* m, const double scale)
{
    for(long i = 0; i < m->ele_num; i++)
        m->data[i] *= scale;
}



/* function:
 * instruction: Same operation as Matrix_scale_by(), except that original matrix will not be changed and a new matrix returned
 * input: 
 * return:
 *  */
Matrix Matrix_scale(const Matrix m, const double scale)
{
    Matrix res;

    res = Matrix_copy(m);
    Matrix_scale_by(&res, scale);

    return res;
}


/* function:
 * instruction: 
 * input: 
 * return:
 *  */
inline void Matrix_exp_ele_by(Matrix* m)
{
    for(long i = 0; i < m->ele_num; i++)
        m->data[i] = exp(m->data[i]);
}

/* function:
 * instruction: 
 * input: 
 * return:
 *  */
Matrix Matrix_exp_ele(const Matrix m)
{
    Matrix res;

    res = Matrix_create(m.N, m.D);
    for(long i = 0; i < res.ele_num; i++)
        res.data[i] = exp(m.data[i]);

    return res;
}


/* function:
 * instruction: 
 * input: 
 * return:
 *  */
void Matrix_log_ele_by(Matrix *m)
{
    for(long i = 0; i < m->ele_num; i++)
        m->data[i] = log(m->data[i]);
}


/* function:
 * instruction: 
 * input: 
 * return:
 *  */
Matrix Matrix_log_ele(const Matrix m)
{
    Matrix res;

    res = Matrix_create(m.N, m.D);
    for(long i = 0; i < m.ele_num; i++)
        res.data[i] = log(m.data[i]);

    return res;
}



/* function:
 * instruction: 
 * input: 
 * return:
 *  */
Matrix Matrix_sum_axis(const Matrix m, const int axis)
{
    Matrix res;

    if(axis == 0)
    {
        res = Matrix_create(1, m.D);
        for(int i = 0; i < m.D; i++)
        {
            res.data[i] = 0;
            int pos = i;
            for(int j = 0; j < m.N; j++, pos+=m.D)
                res.data[i] += m.data[pos];
        }
        return res;
    }

    else if(axis == 1)
    {
        res = Matrix_create(m.N, 1);
        int pos = 0;
        for(int i = 0; i < m.N; i++)
        {
            res.data[i] = 0;
            for(int j = 0; j < m.D; j++, pos++)
                res.data[i] += m.data[pos];
        }
        return res;
    }
    else
    {
        fputs("ERROR: does not support matrix of this shape\n", stdout);
        exit(0);
    }
}



/* function:
 * instruction: 
 * input: 
 * return:
 *  */
void Matrix_sum_axis_by(Matrix *m, const int axis)
{
    if(axis == 0)
    {
        for(int i = 0; i < m->D; i++)
        {
            int pos = i + m->D;
            for(int j = 1; j < m->N; j++, pos+=m->D)
                m->data[i] += m->data[pos];
        }
        m->data = (double*)realloc(m->data, sizeof(double)*m->D);
        m->N = 1;
    }
    else if(axis == 1)
    {
        int pos = 0;
        for(int i = 0; i < m->N; i++)
        {
            m->data[i] = m->data[pos++];
            for(int j = 1; j < m->D; j++, pos++)
                m->data[i] += m->data[pos]; 
        }
        m->data = (double*)realloc(m->data, sizeof(double)*m->N);
        m->D = 1;
    }
    else
    {
        fputs("ERROR: does not support matrix of this shape\n", stdout);
        exit(0);
    }
}



/* function:
 * instruction: 
 * input: 
 * return:
 *  */
double Matrix_sum_all(const Matrix m)
{
    double res = 0;
    
    for(long i = 0; i < m.ele_num; i++)
        res +=  m.data[i];

    return res;
}



/* function:
 * instruction: 
 * input: a is the matrix where the rows picked from, rows is a vector(vertical or horizontal) where the row indices stored
 * return: a new matrix independent to any of the input, it contains all the rows picked from the original matrix
 *  */
Matrix Matrix_pick_rows(const Matrix a, const Matrix rows)
{
    Matrix res;
    int pos;
    int srcpos;

    // check if the shapes of the two matrices agree to each other 
    if(rows.N != 1 && rows.D != 1)
    {
        fputs("ERROR: rows indices matrix has too many dimensions\n", stdout);
        exit(0);
    }
    if(rows.ele_num > a.N)
    {
        fputs("ERROR: too many rows to pick for the matrix\n", stdout);
        exit(0);
    }

    res = Matrix_create(rows.ele_num, a.D);
    pos = 0;
    for(int i = 0; i < rows.ele_num; i++, pos+=a.D)
    {
        srcpos = (a.D*rows.data[i]);
        memcpy(res.data+pos, a.data+srcpos, a.D*sizeof(double));
    }

    return res;
}



/* function:
 * instruction: pick the elements by coordination assigned from the R C matrices or vectors, and return a new vector containing the picked elements
 * input: 
 * return:
 *  */
Matrix Matrix_pick_eles(const Matrix a, const Matrix R, const Matrix C)
{
    Matrix res;
    int maxN, maxD;
    int minN, minD;
    const int D = a.D;
    double (*d)[D];

    if(R.ele_num != C.ele_num)
    {
        fputs("ERROR: the coordinations assigned by R and C have conflicting shapes\n", stdout);
        exit(0);
    }
    maxN = Matrix_max_all(R);
    maxD = Matrix_max_all(C);
    minN = Matrix_min_all(R);
    minD = Matrix_min_all(C);

    if(maxN > a.N || maxD > a.D || minN < 0 || minD < 0)
    {
        fputs("ERROR: one or several coordinations assigned by R and C tries to access elements outbounds\n", stdout);
        exit(0);
    }

    res = Matrix_create(1,R.ele_num);
    d = (double (*)[D])a.data;
    for(int i = 0; i < R.ele_num; i++)
        res.data[i] = d[(int)R.data[i]][(int)C.data[i]];

    return res;
}




/* function:
 * instruction: 
 * input: 
 * return:
 *  */
double Matrix_max_all(const Matrix m)
{
    double res;

    if(m.ele_num < 0)
    {
        fputs("ERROR: element number of a matrix must be a positive number\n", stdout);
        exit(0);
    }
    res = m.data[0];
    for(long i = 1; i < m.ele_num; i++)
        if(res < m.data[i])
            res = m.data[i];

    return res;
}



/* function:
 * instruction: 
 * input: 
 * return:
 *  */
double Matrix_min_all(const Matrix m)
{
    double res;

    if(m.ele_num < 0)
    {
        fputs("ERROR: element number of a matrix must be a positive number\n", stdout);
        exit(0);
    }
    res = m.data[0];
    for(long i = 1; i < m.ele_num; i++)
        if(res > m.data[i])
            res = m.data[i];

    return res;
}



/* function:
 * instruction: 
 * input: 
 * return:
 *  */
inline void Matrix_sign_reverse(Matrix *m)
{
    for(long i = 0; i < m->ele_num; i++)
        m->data[i] = 0 - m->data[i];
}



/* function:
 * instruction: 
 * input: 
 * return:
 *  */
void Matrix_transpose(Matrix *m)
{
    Matrix res;
    Matrix eye;

    res = Matrix_create(m->D, m->N);
    eye = Matrix_eye(m->D);

    // C.T = (AB).T = B.T.dot(A.T)
    cblas_dgemm(CblasRowMajor, CblasTrans, CblasTrans, m->D, m->N, m->D, 1, eye.data, eye.D, m->data, m->D, 0, res.data, m->N);

    Matrix_free(*m);
    Matrix_free(eye);
    *m = res;
}


/* function:
 * instruction: 
 * input: 
 * return:
 *  */
Matrix Matrix_eye(const int d)
{
    Matrix res;
    long pos;

    pos = 0;
    res = Matrix_create(d,d);
    memset(res.data, 0, res.ele_num*sizeof(double));
    for(int i = 0; i < d; i++, pos+=d)
        res.data[pos++] = 1;

    return res;
}


/* function:
 * instruction: 
 * input: 
 * return:
 *  */
Matrix Matrix_gaussian(const int N, const int D)
{
    Matrix res;

    res = Matrix_create(N,D);
    for(long i = 0; i < res.ele_num; i++)
        res.data[i] = gaussian_rand(0,1);

    return res;
}
