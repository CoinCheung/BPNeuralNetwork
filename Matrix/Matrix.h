#ifndef _MATRIX_H_
#define _MATRIX_H_

/* 
 * only basic data types supported: double
 * operators are overloaded so that it looks like numpy. However some difference are such as: 
 * 1. when the elements are to be accessed with indices, the normal bracelet () are used instead of regular bracelet []. 
 *
 * 2. slice goes in the c++ way like this, m(std::slice(2,3,4)), where 2 is the start position, 3 is the number of elements picked out, and 4 is the step size. Besides, the start position can be negative numbers, but the associated derived indice array must not be out of the range of the shape
 *
 * 3. submatrix can be obtained from m(ind), where ind is an array of indice, the members of ind must all be positive and confined within the range of Matrix shape
 *
 *  */



/* ********************************************************* 
 * header files
 ********************************************************* */
#include<iostream>
#include<cstring> // memcpy
#include<cmath>
#include<valarray>
#include"../numeric.h"

extern "C"
{
#include<cblas.h>
}


/* ********************************************************* 
 * usings
 ********************************************************* */
using std::cout;
using std::endl;
using std::exit;
using std::memcpy;
using std::memset;



/* ********************************************************* 
 * macros and types
 ********************************************************* */



/* ********************************************************* 
 * definitions
 ********************************************************* */



/* class:
 * instruction: 
 * derived from: 
 * successors: 
 *  */
class Ind
{
    public:
        long ele_num;
        int N;
        int D;
        int *data;

        Ind();
        Ind(const int num);
        Ind(Ind& ind);
        Ind(Ind&& ind);
        ~Ind();

        Ind& operator=(Ind&& ind);

        void print();
        void free();

        void init(const int num);
        static Ind randchoice(int batch_size, int N);
        static Ind arange(const int a);
        static Ind arange(const int a, const int b);
};




/* class:
 * instruction: 
 * derived from: 
 * successors: 
 *  */
template <class T>
class Matrix2
{
    public:
        // data
        int N;
        int D;
        long ele_num;
        T *data; 

        // functions
        explicit Matrix2();
        explicit Matrix2(int n, int d);
        explicit Matrix2(int n);
        explicit Matrix2(Matrix2& m); // copy construction
        explicit Matrix2(Matrix2&& m); // moving construction
        ~Matrix2();

        Matrix2& operator=(Matrix2& m); // copy assignment
        Matrix2& operator=(Matrix2&& m); // moving assignment

        static Matrix2 ones(const int N, const int D);
        static Matrix2 ones(const long N);
        static Matrix2 zeros(const int N, const int D);
        static Matrix2 zeros(const long N);
        static Matrix2 randn(const int N, const int D);
        static Matrix2 randn(const long N);
        static Matrix2 arange(const int N);
        static Matrix2 arange(const int a, const int b);
        static Matrix2 eye(const int d);

        void print();
        void free();
        void init(const int N, const int D);
        Ind toInd();
        Matrix2 copy();

        static Matrix2 dot(const Matrix2& a, const Matrix2& b);
        Matrix2 dot(const Matrix2& m);

        Matrix2 operator*(const Matrix2& m);
        Matrix2 operator*(const T m);
        Matrix2 operator/(const Matrix2& m);
        Matrix2 operator/(const T m);
        Matrix2 operator+(const Matrix2& m);
        Matrix2 operator+(const T m);
        Matrix2 operator-(const Matrix2& m);
        Matrix2 operator-(const T m);
        T& operator()(const int i, const int j);
        T& operator()(const int i);
        Matrix2 operator()(Ind& ind); // subMatrix derived by index array
        Matrix2 operator()(Ind&& ind); // 
        Matrix2 operator()(Ind&& indx, Ind&& indy); // 
        Matrix2 operator()(std::slice&& sl); // slice as in python
        Matrix2 operator()(std::slice&& slr, std::slice&& slc); // slice as in python

        template<class C>
        friend Matrix2<C> operator*(const C n, const Matrix2<C>& m);
        template<class C>
        friend Matrix2<C> operator/(const C n, const Matrix2<C>& m);
        template<class C>
        friend Matrix2<C> operator+(const C n, const Matrix2<C>& m);
        template<class C>
        friend Matrix2<C> operator-(const C n, const Matrix2<C>& m);

        void set(Ind&& indx, Ind&& y, T val);
        Matrix2 Trans();
        static void Trans(Matrix2& m);
        Matrix2 reshape(const int n, const int d);
        static void reshape(Matrix2& m, const int n, const int d);
        Matrix2 Snrev();
        static void Snrev(Matrix2& m);
        Matrix2 exp();
        static void exp(Matrix2& m);
        Matrix2 log();
        static void log(Matrix2& m);
        Matrix2 log10();
        static void log10(Matrix2& m);
        Matrix2 square();
        static void square(Matrix2& m);

        Matrix2 sum(const int axis);
        T sum();
        Matrix2 max(const int axis);
        T max();
        Ind argmax(const int axis);
        long argmax();
        Matrix2 min(const int axis);
        T min();
        Ind argmin(const int axis);
        long argmin();
};


/* ********************************************************* 
 * implementations
 ********************************************************* */


/////////////////////////////////////////////////////////
/* Implementation of class Matrix2 member functions */
/////////////////////////////////////////////////////////

/* function:
 * instruction: copy construction
 * input:
 * return:
 *  */
template<class T>
Matrix2<T>::Matrix2(Matrix2<T>& m): N(m.N), D(m.D), ele_num(m.ele_num), data(new T[ele_num])
{
    cout << "copying"<<endl;
    memcpy(data, m.data, ele_num*sizeof(T));
}



/* function:
 * instruction: moving construction
 * input:
 * return:
 *  */
template<class T>
Matrix2<T>::Matrix2(Matrix2<T>&& m): N(m.N), D(m.D), ele_num(m.ele_num), data(m.data) 
{
    cout << "moving construct" <<endl;
    m.data = NULL;
}


/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
Matrix2<T>::Matrix2(): N(0), D(0), data(NULL)
{
}



/* function:
 * instruction: construct with two dimensions
 * input:
 * return:
 *  */
template<class T>
Matrix2<T>::Matrix2(int n, int d): N(n), D(d), ele_num(n*d), data(new T[ele_num])
{
}



/* function:
 * instruction: construct with one dimension(a vector)
 * input:
 * return:
 *  */
template<class T>
Matrix2<T>::Matrix2(int n): N(1), D(n), ele_num(n), data(new T[ele_num])
{
}



/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
Matrix2<T>::~Matrix2()
{
    cout << "deconstructing..." <<endl;
    delete[] data;
    data = NULL;
}



/* function:
 * instruction: copy assignment
 * input:
 * return:
 *  */
template<class T>
Matrix2<T>& Matrix2<T>::operator=(Matrix2<T>& m) 
{
    if(this != &m)
        delete[] this->data;

    cout << "direct assign" <<endl;
    this->N = m.N;
    this->D = m.D;
    this->ele_num = m.ele_num;
    this->data = m.data;

    return *this;
}



/* function:
 * instruction: moving assignment 
 * input:
 * return:
 *  */
template<class T>
Matrix2<T>& Matrix2<T>::operator=(Matrix2<T>&& m)
{
    if(this != &m)
        delete[] this->data;

    cout << "moving assign"<<endl;
    this->N = m.N;
    this->D = m.D;
    this->ele_num = m.ele_num;
    this->data = m.data;
    m.data = NULL;

    return *this;
}

/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
Matrix2<T> Matrix2<T>::ones(const int N, const int D)
{
    Matrix2<T> ret(N,D);

    for(long i = 0; i < ret.ele_num; i++)
        ret.data[i] = 1;

    return std::move(ret); // return a right value so that moving construct called instead of memory copy
}



/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
Matrix2<T> Matrix2<T>::ones(const long N)
{
    Matrix2<T> ret(N);

    for(long i = 0; i < ret.ele_num; i++)
        ret.data[i] = 1;

    return std::move(ret);
}


/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
Matrix2<T> Matrix2<T>::zeros(const int N, const int D)
{
    Matrix2<T> ret(N,D);

    for(long i = 0; i < ret.ele_num; i++)
        ret.data[i] = 0;

    return std::move(ret);
}



/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
Matrix2<T> Matrix2<T>::zeros(const long N)
{
    Matrix2 ret(N);
    for(long i = 0; i < ret.ele_num; i++)
        ret.data[i] = 0;

    return std::move(ret);
}




/* function:
 * instruction: normalized gaussian random number
 * input:
 * return:
 *  */
template<class T>
Matrix2<T> Matrix2<T>::randn(const int N, const int D)
{
    Matrix2<T> ret(N,D);

    for(long i = 0; i < ret.ele_num; i++)
        ret.data[i] = gaussian_rand();

    return std::move(ret);
}





/* function:
 * instruction: normalized gaussian random number
 * input:
 * return:
 *  */
template<class T>
Matrix2<T> Matrix2<T>::randn(const long N)
{
    Matrix2 ret(N);
    for(long i = 0; i < ret.ele_num; i++)
        ret.data[i] = gaussian_rand();

    return std::move(ret);
}




/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
Matrix2<T> Matrix2<T>::arange(const int N)
{
    Matrix2<T> res(N);

    for(long i = 0; i < N; i++)
        res.data[i] = i;

    return std::move(res);
}



/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
Matrix2<T> Matrix2<T>::arange(const int a, const int b)
{
    if(b < a)
    {
        cout << __FILE__ << __LINE__ << " : ERROR: For function arange(a,b), input b should be greater than a" << endl;
        exit(0);
    }

    Matrix2<T> res(b-a);
    long ind;

    ind = 0;
    for(long i = a; i < b; i++)
        res.data[ind++] = i;

    return std::move(res);
}



/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
Matrix2<T> Matrix2<T>::eye(const int d)
{
    Matrix2<T> res(d,d);
    long pos;

    std::memset(res.data, 0, sizeof(T)*res.ele_num);
    pos = 0;
    for(int i = 0; i < d; i++,pos+=d)
        res.data[pos++] = 1;

    return std::move(res);
}



/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
void Matrix2<T>::print()
{
    long pos;
    pos = 0;

    cout << "[ " << endl;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < D; j++, pos++)
            cout << data[pos] << ", ";
        cout << endl;
    }
    cout << "] " <<endl;
}



/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
void Matrix2<T>::free()
{
    delete [] data;
    data = NULL;
}




/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
void Matrix2<T>::init(const int N, const int D)
{
    this->N = N;
    this->D = D;
    this->ele_num = N*D;
    delete[] data;

    this->data = new T[this->ele_num];
}





/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
Ind Matrix2<T>::toInd()
{
    Ind res(ele_num);

    for(long i = 0; i < ele_num; i++)
        res.data[i] = (int)data[i];

    return std::move(res);
}




/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
Matrix2<T> Matrix2<T>::copy()
{
    Matrix2<T> res(N, D);

    memcpy(res.data, data, ele_num*sizeof(T));

    return std::move(res);
}




/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
Matrix2<T> Matrix2<T>::dot(const Matrix2<T>& m)
{
    const int N = this->N;
    const int D = this->D;
    const int C = m.N;
    const int M = m.D;

    Matrix2<T> res(N,M);

    // check if two matrices match in shape
    if(D != C)
    {
        cout<< __FILE__<<":"<<__LINE__<<"ERROR: shape of two matrices should match to each other"<<endl;
        exit(1);
    }

    // scenario where this and m are vectors
    if(D == 1)
        cblas_dger(CblasRowMajor, N, M, 1, this->data, 1, m.data, 1, res.data, M);
    //scenario where a and b are vectors, and, by shape, inner product is computed
    else if(N == 1 && M == 1)
        *res.data = cblas_ddot(D, this->data, 1, m.data, 1);
    // scenario where a is a h vector and b is a matrix
    else if(N == 1 && M != 1)
        cblas_dgemv(CblasRowMajor, CblasTrans, C, M, 1, m.data, M, this->data, 1, 0, res.data, 1);
    // scenario where a is matrix and b is vector
    else if(M == 1 && N != 1)
        cblas_dgemv(CblasRowMajor, CblasNoTrans, N, D, 1, this->data, D, m.data, 1, 0, res.data, 1);
    // scenario where a and b are matrices
    else
        cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, M, D, 1, this->data, D, m.data, M, 0, res.data, M);

    return std::move(res);
}



/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
Matrix2<T> Matrix2<T>::dot(const Matrix2<T> &a, const Matrix2<T> &b) 
{
    const int N = a.N;
    const int D = a.D;
    const int C = b.N;
    const int M = b.D;

    // check if two matrices not match in shape
    if(D != C)
    {
        cout <<"ERROR: "<<  __FILE__ << ": " << __LINE__ << ": "<< "the two input matrices should match each other in their shapes" << endl;
        exit(0);
    }

    Matrix2<T> res = Matrix2<T>::zeros(N,M);

    // scenario where a and b are vectors, compute their outer product
    if(D == 1)
        cblas_dger(CblasRowMajor, N, M, 1.0, a.data, 1, b.data, 1, res.data, M);
    
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

    return std::move(res);
}





/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
Matrix2<T> Matrix2<T>::operator*(const Matrix2<T>& m)
{

    T temp;
    long pos;

    // scenario where two matrices have same shape
    if(N == m.N && D == m.D) 
    {
        Matrix2<T> res(N,D);
        for(long i = 0; i < ele_num; i++)
            res.data[i] = data[i] * m.data[i];
        return std::move(res);
    }

    // scenario where a is one-element matrix
    else if(N == 1 && D == 1)
    {
        Matrix2<T> res(m.N,m.D);
        temp = data[0];
        for(long i = 0; i < m.ele_num; i++)
            res.data[i] = temp * m.data[i];
        return std::move(res);
    }

    // scenario where b is a one-element matrix
    else if(m.N == 1 && m.D == 1)
    {
        Matrix2<T> res(N,D);
        temp = m.data[0];
        for(long i = 0; i < ele_num; i++)
            res.data[i] = data[i] * temp;
        return std::move(res);
    }

    // scenario where a is a matrix and b is a horizontal vector
    else if(m.N == 1 && D == m.D)
    {
        Matrix2 res(N,D);
        for(int i = 0; i < m.D; i++)
        {
            temp = m.data[i];
            pos = i;
            for(int j = 0; j < N; j++, pos+=D)
                res.data[pos] = data[pos] * temp;
        }
        return std::move(res);
    }

    // scenario where a is a matrix and b is a vertical vector
    else if(N == m.N && m.D == 1) 
    {
        Matrix2 res(N,D);
        pos = 0;
        for(int i = 0; i < N; i++)
        {
            temp = m.data[i];
            for(int j = 0; j < D; j++, pos++)
                res.data[pos] = data[pos] * temp;
        }
        return std::move(res);
    }

    // scenario where a is a horizontal vector and b is a Matrix
    else if(N == 1 && D == m.D)
    {
        Matrix2<T> res(m.N,m.D);
        for(int i = 0; i < m.D; i++)
        {
            pos = i;
            temp = data[i];
            for(int j = 0; j < m.N; j++, pos+=D)
                res.data[pos] = temp * m.data[pos]; 
        }
        return std::move(res);
    }

    // scenario where a is a vertical vector and b is a Matrix
    else if(D == 1 && N == m.N)
    {
        Matrix2<T> res(m.N,m.D);
        pos = 0;
        for(int i = 0; i < m.N; i++)
        {
            temp = data[i];
            for(int j = 0; j < m.D; j++, pos++)
                res.data[pos] = temp * m.data[pos]; 
        }
        return std::move(res);
    }

    else
    {
        cout << __FILE__ << ":" << __LINE__ <<" : ERROR: Matrix * requires input matrices have associated shapes" << endl;
        exit(0);
    }
}



/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
Matrix2<T> Matrix2<T>::operator*(const T m)
{
    Matrix2<T> res(N,D);
    for(long i = 0; i < ele_num; i++)
        res.data[i] = data[i] * m;

    return std::move(res);
}



/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class C>
Matrix2<C> operator*(const C n, const Matrix2<C>& m)
{
    Matrix2<C> res(m.N,m.D);
    for(long i = 0; i < m.ele_num; i++)
        res.data[i] = m.data[i] * n;

    return std::move(res);
}


/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
Matrix2<T> Matrix2<T>::operator/(const Matrix2<T>& m)
{

    T temp;
    long pos;

    // scenario where two matrices have same shape
    if(N == m.N && D == m.D) 
    {
        Matrix2<T> res(N,D);
        for(long i = 0; i < ele_num; i++)
            res.data[i] = data[i] / m.data[i];
        return std::move(res);
    }

    // scenario where a is one-element matrix
    else if(N == 1 && D == 1)
    {
        Matrix2<T> res(m.N,m.D);
        temp = data[0];
        for(long i = 0; i < m.ele_num; i++)
            res.data[i] = temp / m.data[i];
        return std::move(res);
    }

    // scenario where b is a one-element matrix
    else if(m.N == 1 && m.D == 1)
    {
        Matrix2<T> res(N,D);
        temp = m.data[0];
        for(long i = 0; i < ele_num; i++)
            res.data[i] = data[i] / temp;
        return std::move(res);
    }

    // scenario where a is a matrix and b is a horizontal vector
    else if(m.N == 1 && D == m.D)
    {
        Matrix2 res(N,D);
        for(int i = 0; i < m.D; i++)
        {
            temp = m.data[i];
            pos = i;
            for(int j = 0; j < N; j++, pos+=D)
                res.data[pos] = data[pos] / temp;
        }
        return std::move(res);
    }

    // scenario where a is a matrix and b is a vertical vector
    else if(N == m.N && m.D == 1) 
    {
        Matrix2 res(N,D);
        pos = 0;
        for(int i = 0; i < N; i++)
        {
            temp = m.data[i];
            for(int j = 0; j < D; j++, pos++)
                res.data[pos] = data[pos] / temp;
        }
        return std::move(res);
    }

    // scenario where a is a horizontal vector and b is a Matrix
    else if(N == 1 && D == m.D)
    {
        Matrix2<T> res(m.N,m.D);
        for(int i = 0; i < m.D; i++)
        {
            pos = i;
            temp = data[i];
            for(int j = 0; j < m.N; j++, pos+=D)
                res.data[pos] = temp / m.data[pos]; 
        }
        return std::move(res);
    }

    // scenario where a is a vertical vector and b is a Matrix
    else if(D == 1 && N == m.N)
    {
        Matrix2<T> res(m.N,m.D);
        pos = 0;
        for(int i = 0; i < m.N; i++)
        {
            temp = data[i];
            for(int j = 0; j < m.D; j++, pos++)
                res.data[pos] = temp / m.data[pos]; 
        }
        return std::move(res);
    }

    else
    {
        cout << __FILE__ << ":" << __LINE__ <<" : ERROR: Matrix / requires input matrices have associated shapes" << endl;
        exit(0);
    }
}



/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
Matrix2<T> Matrix2<T>::operator/(const T m)
{
    Matrix2<T> res(N,D);
    for(long i = 0; i < ele_num; i++)
        res.data[i] = data[i] / m;

    return std::move(res);
}



/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class C>
Matrix2<C> operator/(const C n, const Matrix2<C>& m)
{
    Matrix2<C> res(m.N,m.D);
    for(long i = 0; i < m.ele_num; i++)
        res.data[i] = n / m.data[i];

    return std::move(res);
}




/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
Matrix2<T> Matrix2<T>::operator+(const Matrix2<T>& m)
{

    T temp;
    long pos;

    // scenario where two matrices have same shape
    if(N == m.N && D == m.D) 
    {
        Matrix2<T> res(N,D);
        for(long i = 0; i < ele_num; i++)
            res.data[i] = data[i] + m.data[i];
        return std::move(res);
    }

    // scenario where a is one-element matrix
    else if(N == 1 && D == 1)
    {
        Matrix2<T> res(m.N,m.D);
        temp = data[0];
        for(long i = 0; i < m.ele_num; i++)
            res.data[i] = temp + m.data[i];
        return std::move(res);
    }

    // scenario where b is a one-element matrix
    else if(m.N == 1 && m.D == 1)
    {
        Matrix2<T> res(N,D);
        temp = m.data[0];
        for(long i = 0; i < ele_num; i++)
            res.data[i] = data[i] + temp;
        return std::move(res);
    }

    // scenario where a is a matrix and b is a horizontal vector
    else if(m.N == 1 && D == m.D)
    {
        Matrix2 res(N,D);
        for(int i = 0; i < m.D; i++)
        {
            temp = m.data[i];
            pos = i;
            for(int j = 0; j < N; j++, pos+=D)
                res.data[pos] = data[pos] + temp;
        }
        return std::move(res);
    }

    // scenario where a is a matrix and b is a vertical vector
    else if(N == m.N && m.D == 1) 
    {
        Matrix2 res(N,D);
        pos = 0;
        for(int i = 0; i < N; i++)
        {
            temp = m.data[i];
            for(int j = 0; j < D; j++, pos++)
                res.data[pos] = data[pos] + temp;
        }
        return std::move(res);
    }

    // scenario where a is a horizontal vector and b is a Matrix
    else if(N == 1 && D == m.D)
    {
        Matrix2<T> res(m.N,m.D);
        for(int i = 0; i < m.D; i++)
        {
            pos = i;
            temp = data[i];
            for(int j = 0; j < m.N; j++, pos+=D)
                res.data[pos] = temp + m.data[pos]; 
        }
        return std::move(res);
    }

    // scenario where a is a vertical vector and b is a Matrix
    else if(D == 1 && N == m.N)
    {
        Matrix2<T> res(m.N,m.D);
        pos = 0;
        for(int i = 0; i < m.N; i++)
        {
            temp = data[i];
            for(int j = 0; j < m.D; j++, pos++)
                res.data[pos] = temp + m.data[pos]; 
        }
        return std::move(res);
    }

    else
    {
        cout << __FILE__ << ":" << __LINE__ <<" : ERROR: Matrix + requires input matrices have associated shapes" << endl;
        exit(0);
    }
}



/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
Matrix2<T> Matrix2<T>::operator+(const T m)
{
    Matrix2<T> res(N,D);
    for(long i = 0; i < ele_num; i++)
        res.data[i] = data[i] + m;

    return std::move(res);
}



/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class C>
Matrix2<C> operator+(const C n, const Matrix2<C>& m)
{
    Matrix2<C> res(m.N,m.D);
    for(long i = 0; i < m.ele_num; i++)
        res.data[i] = n + m.data[i];

    return std::move(res);
}



/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class C>
Matrix2<C> operator-(const C n, const Matrix2<C>& m)
{
    Matrix2<C> res(m.N,m.D);
    for(long i = 0; i < m.ele_num; i++)
        res.data[i] = n - m.data[i];

    return std::move(res);
}



/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
Matrix2<T> Matrix2<T>::operator-(const Matrix2<T>& m)
{

    T temp;
    long pos;

    // scenario where two matrices have same shape
    if(N == m.N && D == m.D) 
    {
        Matrix2<T> res(N,D);
        for(long i = 0; i < ele_num; i++)
            res.data[i] = data[i] - m.data[i];
        return std::move(res);
    }

    // scenario where a is one-element matrix
    else if(N == 1 && D == 1)
    {
        Matrix2<T> res(m.N,m.D);
        temp = data[0];
        for(long i = 0; i < m.ele_num; i++)
            res.data[i] = temp - m.data[i];
        return std::move(res);
    }

    // scenario where b is a one-element matrix
    else if(m.N == 1 && m.D == 1)
    {
        Matrix2<T> res(N,D);
        temp = m.data[0];
        for(long i = 0; i < ele_num; i++)
            res.data[i] = data[i] - temp;
        return std::move(res);
    }

    // scenario where a is a matrix and b is a horizontal vector
    else if(m.N == 1 && D == m.D)
    {
        Matrix2 res(N,D);
        for(int i = 0; i < m.D; i++)
        {
            temp = m.data[i];
            pos = i;
            for(int j = 0; j < N; j++, pos+=D)
                res.data[pos] = data[pos] - temp;
        }
        return std::move(res);
    }

    // scenario where a is a matrix and b is a vertical vector
    else if(N == m.N && m.D == 1) 
    {
        Matrix2 res(N,D);
        pos = 0;
        for(int i = 0; i < N; i++)
        {
            temp = m.data[i];
            for(int j = 0; j < D; j++, pos++)
                res.data[pos] = data[pos] - temp;
        }
        return std::move(res);
    }

    // scenario where a is a horizontal vector and b is a Matrix
    else if(N == 1 && D == m.D)
    {
        Matrix2<T> res(m.N,m.D);
        for(int i = 0; i < m.D; i++)
        {
            pos = i;
            temp = data[i];
            for(int j = 0; j < m.N; j++, pos+=D)
                res.data[pos] = temp - m.data[pos]; 
        }
        return std::move(res);
    }

    // scenario where a is a vertical vector and b is a Matrix
    else if(D == 1 && N == m.N)
    {
        Matrix2<T> res(m.N,m.D);
        pos = 0;
        for(int i = 0; i < m.N; i++)
        {
            temp = data[i];
            for(int j = 0; j < m.D; j++, pos++)
                res.data[pos] = temp - m.data[pos]; 
        }
        return std::move(res);
    }

    else
    {
        cout << __FILE__ << ":" << __LINE__ <<" : ERROR: Matrix + requires input matrices have associated shapes" << endl;
        exit(0);
    }
}


/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
Matrix2<T> Matrix2<T>::operator-(const T m)
{
    Matrix2<T> res(N,D);
    for(long i = 0; i < ele_num; i++)
        res.data[i] = data[i] - m;

    return std::move(res);
}



/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
T& Matrix2<T>::operator()(const int i, const int j)
{
    if(i >= N || j >= D)
        cout << __FILE__ << ": " << __LINE__ << ": " << "warning: function Matrix2::operator()(const int, const int) requires the index confined within the range of the shape of the matrix (N,D), but the given index is out of range" << endl;

    return data[i*D+j];
}




/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
T& Matrix2<T>::operator()(const int i)
{
    if(N != 1 && D != 1)
        cout << __FILE__ << ": " << __LINE__ << ": " << "warning: function Matrix2::operator()(const int) requires matrix have the shape of a vector, but this matrix is not a vector" << endl;

    return data[i];
}




/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
Matrix2<T> Matrix2<T>::operator()(Ind& ind)
{
    Matrix2<T> res;
    
    cout << "in operator (ind&&)" << endl;

    for(long i = 0; i < ind.ele_num; i++)
        if(ind.data[i] >= N || ind.data[i] < 0)
        {
            cout << __FILE__ << ": " << __LINE__ << ": indices array value out of range" << endl;
            exit(0);
        }

    T *data_ptr;
    long copy_len;
    res.init(ind.ele_num, D);

    data_ptr = res.data;
    copy_len = sizeof(T) * D;
    res.init(ind.ele_num, D);
    for(int i = 0; i < ind.ele_num; i++, data_ptr+=D)
        memcpy(data_ptr, data+ind.data[i]*D, copy_len);

    return std::move(res);
}



/* function:
 * instruction:   
 * input:
 * return:
 *  */
template<class T>
Matrix2<T> Matrix2<T>::operator()(Ind&& ind)
{
    Matrix2<T> res;
    
    cout << "in operator (ind&&)" << endl;

    for(long i = 0; i < ind.ele_num; i++)
        if(ind.data[i] >= N || ind.data[i] < 0)
        {
            cout << __FILE__ << ": " << __LINE__ << ": indices array value out of range" << endl;
            exit(0);
        }

    T *data_ptr;
    long copy_len;
    res.init(ind.ele_num, D);

    data_ptr = res.data;
    copy_len = sizeof(T) * D;
    res.init(ind.ele_num, D);
    for(int i = 0; i < ind.ele_num; i++, data_ptr+=D)
        memcpy(data_ptr, data+ind.data[i]*D, copy_len);

    return std::move(res);
}




/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
Matrix2<T> Matrix2<T>::operator()(Ind&& indx, Ind&& indy)
{
    Matrix2<T> res;

    // check bondary
    if(indx.ele_num != indy.ele_num)
    {
        cout << __FILE__ << ": " << __LINE__ << ": indices array indx and indy do not agree in their shapes" << endl;
        exit(0);
    }
    for(long i = 0; i < indx.ele_num; i++)
        if(indx.data[i] >= N || indx.data[i] < 0)
        {
            cout << __FILE__ << ": " << __LINE__ << ": indices array indx value out of range" << endl;
            exit(0);
        }

    for(long i = 0; i < indy.ele_num; i++)
        if(indy.data[i] >= N || indy.data[i] < 0)
        {
            cout << __FILE__ << ": " << __LINE__ << ": indices array indy value out of range" << endl;
            exit(0);
        }

    // pick out numbers
    long pos;

    pos = 0;
    res.init(indx.ele_num, 1);
    for(long i = 0; i < indx.ele_num; i++)
    {
        pos = indx.data[i] * D + indy.data[i];
        res.data[i] = data[pos];
    }

    return std::move(res);
}





/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
Matrix2<T> Matrix2<T>::operator()(std::slice&& sl)
{
    Matrix2<T> res;
    int start, length, step, end;
    
    start = sl.start();
    if(start < 0)
        start += N;
    length = sl.size();
    step = sl.stride();
    end = start + step * (length - 1);
    if(start<0 || start>=N || end<0 || end>=N)
    {
        cout << __FILE__ << ": " << __LINE__ << ": slice indices out of range" << endl;
        exit(0);
    }

    // pick the numbers out
    long pos;
    long des;
    int stride;
    long size;
    res.init(length, D);
    pos = start * D;
    des = 0;
    stride = step * D;
    size = sizeof(T) * D;
    for(int i = 0; i < length; i++, des+=D, pos+=stride)
        memcpy((res.data+des), data+pos, sizeof(T)*D);

    return std::move(res);
}




/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
Matrix2<T> Matrix2<T>::operator()(std::slice&& slr, std::slice&& slc)
{
    Matrix2<T> res;
    int startx, lengthx, stepx, endx;
    int starty, lengthy, stepy, endy;

    startx = slr.start();
    starty = slc.start();
    if(startx < 0)
        startx += N;
    if(starty < 0)
        starty += D;
    lengthx = slr.size();
    lengthy = slc.size();
    stepx = slr.stride();
    stepy = slc.stride();
    endx = startx + stepx * (lengthx - 1);
    endy = starty + stepy * (lengthy - 1);
    if(startx<0 || startx>=N || endx<0 || endx>=N || starty<0 || starty>=D || endy<0 || endy>=D)
    {
        cout << __FILE__ << ": " << __LINE__ << ": slice indices out of range" << endl;
        exit(0);
    }

    // pick the numbers out
    res.init(lengthx,lengthy);
    
    long posx;
    long posy;
    long count;
    int stridex;

    count = 0;
    stridex = stepx * D;
    posx = startx*D;
    for(int i = 0; i < lengthx; i++, posx+=stridex)
    {
        posy = posx + starty;
        for(int j = 0; j < lengthy; j++, posy+=stepy)
            res.data[count++] = data[posy];
    }

    return std::move(res);
}




/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
void Matrix2<T>::set(Ind&& indx, Ind&& indy, T val)
{
    // check bondary
    if(indx.ele_num != indy.ele_num)
    {
        cout << __FILE__ << ": " << __LINE__ << ": indices array indx and indy do not agree in their shapes" << endl;
        exit(0);
    }
    for(long i = 0; i < indx.ele_num; i++)
        if(indx.data[i] >= N || indx.data[i] < 0)
        {
            cout << __FILE__ << ": " << __LINE__ << ": indices array indx value out of range" << endl;
            exit(0);
        }

    for(long i = 0; i < indy.ele_num; i++)
        if(indy.data[i] >= N || indy.data[i] < 0)
        {
            cout << __FILE__ << ": " << __LINE__ << ": indices array indy value out of range" << endl;
            exit(0);
        }

    // set values
    long pos;

    pos = 0;
    for(long i = 0; i < indx.ele_num; i++)
    {
        pos = indx.data[i] * D + indy.data[i];
        data[pos] = val; 
    }
}




/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
Matrix2<T> Matrix2<T>::Trans()
{
    Matrix2<T> res(D,N);
    long pos_before;
    long pos_after;

    pos_before = 0;
    for(int i = 0; i < N; i++)
    {
        pos_after = i;
        for(int j = 0; j < D; j++, pos_before++, pos_after+=N)
            res.data[pos_after] = data[pos_before] ;
    }

    return std::move(res);
}



/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
void Matrix2<T>::Trans(Matrix2<T>& m)
{
    T *res = new T[m.N*m.D];
    long pos_before;
    long pos_after;

    pos_before = 0;
    for(int i = 0; i < m.N; i++)
    {
        pos_after = i;
        for(int j = 0; j < m.D; j++, pos_before++, pos_after+=m.N)
            res[pos_after] = m.data[pos_before] ;
    }

    delete[] m.data;
    m.data = res;
    m.N = m.D^m.N;
    m.D = m.D^m.N;
    m.N = m.D^m.N;
}



/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
Matrix2<T> Matrix2<T>::reshape(const int n, const int d)
{
    if(n*d != N*D)
    {
        cout << __FILE__ << __LINE__ << " : function reshape() requires input shape n*d equaling to N*D" << endl;
        exit(0);
    }

    Matrix2<T> res(n,d);
    memcpy(res.data, data, sizeof(T)*ele_num);

    return std::move(res);
}



/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
void Matrix2<T>::reshape(Matrix2<T>& m, const int n, const int d)
{
    if(n*d != m.N*m.D)
    {
        cout << __FILE__ << __LINE__ << " : function reshape() requires input shape n*d equaling to N*D" << endl;
        exit(0);
    }

    m.N = n;
    m.D = d;
}




/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
Matrix2<T> Matrix2<T>::Snrev()
{
    Matrix2<T> res(N, D);

    for(long i = 0; i < ele_num; i++)
        res.data[i] = -data[i];

    return std::move(res);
}



/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
void Matrix2<T>::Snrev(Matrix2<T>& m)
{
    for(long i = 0; i < m.ele_num; i++)
        m.data[i] = -m.data[i];
}



/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
Matrix2<T> Matrix2<T>::exp()
{
    Matrix2<T> res(N,D);

    for(long i = 0; i < ele_num; i++)
        res.data[i] = std::exp(data[i]);

    return std::move(res);
}




/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
void Matrix2<T>::exp(Matrix2<T>& m)
{
    for(long i = 0; i < m.ele_num; i++)
        m.data[i] = std::exp(m.data[i]);
}




/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
Matrix2<T> Matrix2<T>::log()
{
    Matrix2<T> res(N,D);

    for(long i = 0; i < ele_num; i++)
        res.data[i] = std::log(data[i]);

    return std::move(res);
}




/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
void Matrix2<T>::log(Matrix2& m)
{
    for(long i = 0; i < m.ele_num; i++)
        m.data[i] = std::log(m.data[i]);
}




/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
Matrix2<T> Matrix2<T>::log10()
{
    Matrix2<T> res(N,D);

    for(long i = 0; i < ele_num; i++)
        res.data[i] = std::log10(data[i]);

    return std::move(res);
}



/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
void Matrix2<T>::log10(Matrix2& m)
{
    for(long i = 0; i < m.ele_num; i++)
        m.data[i] = std::log10(m.data[i]);
}




/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
Matrix2<T> Matrix2<T>::square()
{
    Matrix2<T> res(N,D);
    
    for(long i = 0; i < res.ele_num; i++)
        res.data[i] = data[i] * data[i];

    return std::move(res);
}




/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
void Matrix2<T>::square(Matrix2<T>& m)
{
    for(long i = 0; i < m.ele_num; i++)
        m.data[i] = m.data[i] * m.data[i];
}



/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
Matrix2<T> Matrix2<T>::sum(const int axis)
{
    Matrix2<T> res;
    if(axis == 0)
    {
        res.init(1, D);
        int pos;

        pos = 0;
        std::memset(res.data, 0, sizeof(T)*res.ele_num);
        for(int i = 0; i < N; i++)
            for(int j = 0; j < D; j++)
                res.data[j] += data[pos++];
    }

    else if(axis == 1)
    {
        res.init(N, 1);
        long pos;

        std::memset(res.data, 0, sizeof(T)*res.ele_num);
        pos = 0;

        for(int i = 0; i < N; i++)
            for(int j = 0; j < D; j++)
                res.data[i] += data[pos++];
    }

        return std::move(res);
}




/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
T Matrix2<T>::sum()
{
    T res;
    
    res = 0;
    for(long i = 0; i < ele_num; i++)
        res += data[i];

    return res;
}



/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
Matrix2<T> Matrix2<T>::max(const int axis)
{
    Matrix2<T> res;
    long pos;

    if(axis == 0)
    {
        res.init(1,D);
        for(int i = 0; i < D; i++)
        {
            pos = i;
            res.data[i] = data[pos];
            for(int j = 0; j < N-1; j++)
            {
                pos += D;
                if(data[pos] > res.data[i])
                    res.data[i] = data[pos];
            }
        }
    }

    else if(axis == 1)
    {
        res.init(N,1);
        pos = 0;
        for(int i = 0; i < N; i++)
        {
            res.data[i] = data[pos++];
            for(int j = 0; j < D-1; j++, pos++)
            {
                if(res.data[i] < data[pos])
                    res.data[i] = data[pos];
            }
        }
    }

    return std::move(res);
}




/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
T Matrix2<T>::max()
{
    T temp;

    temp = data[0];
    for(long i = 1; i < ele_num; i++)
        if(temp < data[i])
            temp = data[i];

    return temp;
}




/* function:
 * instruction: 
 * input:
 * return: Index Matrix of relevant element
 *  */
template<class T>
Ind Matrix2<T>::argmax(const int axis)
{
    Ind res;
    T temp;
    long pos;

    if(axis == 0)
    {
        res.init(D);
        for(int i = 0; i < D; i++)
        {
            pos = i;
            temp = data[pos];
            res.data[i] = 0;
            for(int j = 1; j < N; j++)
            {
                pos += D;
                if(data[pos] > temp)
                {
                    temp = data[pos];
                    res.data[i] = j;
                }
            }
        }
    }

    else if(axis == 1)
    {
        res.init(N);
        pos = 0;
        for(int i = 0; i < N; i++)
        {
            temp = data[pos++];
            res.data[i] = 0;
            for(int j = 1; j < D; j++, pos++)
            {
                if(temp < data[pos])
                {
                    res.data[i] = j;
                    temp = data[pos];
                }
            }
        }
    }

    return std::move(res);

}



/* function:
 * instruction: 
 * input:
 * return: Index of relevant element in the array which is strentched to line from the Matrix
 *  */
template<class T>
long Matrix2<T>::argmax()
{
    T temp;
    long pos;

    pos = 0;
    temp = data[0];

    for(long i = 0; i < ele_num; i++)
        if(temp < data[i])
        {
            temp = data[i];
            pos = i;
        }

    return pos;
}



/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
Matrix2<T> Matrix2<T>::min(const int axis)
{
    Matrix2<T> res;
    long pos;

    if(axis == 0)
    {
        res.init(1,D);
        for(int i = 0; i < D; i++)
        {
            pos = i;
            res.data[i] = data[pos];
            for(int j = 0; j < N-1; j++)
            {
                pos += D;
                if(res.data[i] > data[pos])
                    res.data[i] = data[pos];
            }
        }
    }

    else if(axis == 1)
    {
        res.init(N,1);
        pos = 0;
        for(int i = 0; i < N; i++)
        {
            res.data[i] = data[pos++];
            for(int j = 0; j < D-1; j++, pos++)
            {
                if(res.data[i] > data[pos])
                    res.data[i] = data[pos];
            }
        }
    }

    return std::move(res);
}




/* function:
 * instruction: 
 * input:
 * return: Index of relevant element in the array which is strentched to line from the Matrix
 *  */
template<class T>
long Matrix2<T>::argmin()
{
    T temp;
    long pos;

    pos = 0;
    temp = data[0];

    for(long i = 0; i < ele_num; i++)
        if(temp > data[i])
        {
            temp = data[i];
            pos = i;
        }

    return pos;
}




/* function:
 * instruction: 
 * input:
 * return: Index Matrix of relevant element
 *  */
template<class T>
Ind Matrix2<T>::argmin(const int axis)
{
    Ind res;
    T temp;
    long pos;

    if(axis == 0)
    {
        res.init(D);
        for(int i = 0; i < D; i++)
        {
            pos = i;
            temp = data[pos];
            res.data[i] = 0;
            for(int j = 1; j < N; j++)
            {
                pos += D;
                if(data[pos] < temp)
                {
                    temp = data[pos];
                    res.data[i] = j;
                }
            }
        }
    }

    else if(axis == 1)
    {
        res.init(N);
        pos = 0;
        for(int i = 0; i < N; i++)
        {
            temp = data[pos++];
            res.data[i] = 0;
            for(int j = 1; j < D; j++, pos++)
            {
                if(temp > data[pos])
                {
                    res.data[i] = j;
                    temp = data[pos];
                }
            }
        }
    }

    return std::move(res);


}








//////////////////////////








class A
{
    public:
        double *data;
        int N;
        int D;

        A();
        A(const A& a);
        A(A&& a);
        ~A();
        void print();
        A& operator=(A &a);
        A& operator=(A&& a);
        A* copy();
};



#endif
