#ifndef _MATRIX_H_
#define _MATRIX_H_

/* 
 * only basic data types supported: double
 * operators are overloaded so that it looks like numpy. However some difference are such as: 
 * 1. when the elements are to be accessed with indices, the normal bracelet () are used instead of regular bracelet []. 
 * 2. slice should be used like this
 *  */

/* ********************************************************* 
 * header files
 ********************************************************* */
#include<iostream>
#include<cstring> // memcpy
#include<cmath>

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
 *  */
class Ind
{
    public:
        long ele_num;
        int *datax;
        int *datay;
        int slice_start;
        int slice_end;
        int slice_step;

        Ind();
        Ind(const int num);
        Ind(Ind& ind);
        Ind(Ind&& ind);
        ~Ind();

        Ind& operator=(Ind&& ind);

        void print();
        void free();


        void init(const int num);
        static Ind&& slice(int start = 0, int end = 0, int step = 1);
};




/* class:
 * instruction: 
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
        Matrix2();
        Matrix2(int n, int d);
        Matrix2(int n);
        Matrix2(Matrix2& m); // copy construction
        Matrix2(Matrix2&& m); // moving construction
        ~Matrix2();

        Matrix2& operator=(Matrix2& m); // copy assignment
        Matrix2& operator=(Matrix2&& m); // moving assignment

        static Matrix2 ones(const int N, const int D);
        static Matrix2 ones(const long N);
        static Matrix2 zeros(const int N, const int D);
        static Matrix2 zeros(const long N);
        static Matrix2 arange(const int N);
        static Matrix2 arange(const int a, const int b);
        static Matrix2 eye(const int d);

        void print();
        void free();
        void init(const int N, const int D);

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
        Matrix2 operator()(Ind& ind); // slice as in python
        Matrix2 operator()(Ind&& ind); // slice as in python

        template<class C>
        friend Matrix2<C> operator*(const C n, const Matrix2<C>& m);
        template<class C>
        friend Matrix2<C> operator/(const C n, const Matrix2<C>& m);
        template<class C>
        friend Matrix2<C> operator+(const C n, const Matrix2<C>& m);
        template<class C>
        friend Matrix2<C> operator-(const C n, const Matrix2<C>& m);

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
        Matrix2 sum(const int axis);
        T sum();
        Matrix2 max(const int axis);
        T max();
        Ind argmax(const int axis);
        Ind argmax();
};


/* ********************************************************* 
 * implementations
 ********************************************************* */

/////////////////////////////////////////////////////////
/* Implementation of class Ind member functions */
/////////////////////////////////////////////////////////

/* function:
 * instruction: 
 * input:
 * return:
 *  */
Ind::Ind():ele_num(0), datax(NULL), datay(NULL),slice_start(0), slice_end(0), slice_step(0)
{
}



/* function:
 * instruction: 
 * input:
 * return:
 *  */
Ind::Ind(const int num):ele_num(num), datax(new int[num]), datay(new int[num]), slice_start(0), slice_end(0), slice_step(0)
{
}



/* function:
 * instruction: copying construct
 * input:
 * return:
 *  */
Ind::Ind(Ind& ind)
{
    cout << "Ind: copying construct" << endl;

    ele_num = ind.ele_num;
    slice_start = ind.slice_start;
    slice_end = ind.slice_end;
    slice_step = ind.slice_step;

    datax = ind.datax;
    datay = ind.datay;
    
}



/* function:
 * instruction: moving construct
 * input:
 * return:
 *  */
Ind::Ind(Ind&& ind)
{
    cout << "Ind: moving construct" << endl;

    ele_num = ind.ele_num;
    slice_start = ind.slice_start;
    slice_end = ind.slice_end;
    slice_step = ind.slice_step;

    datax = ind.datax;
    datay = ind.datay;
    
    // ind.slice_start = 0;
    // ind.slice_end = 0;
    // ind.slice_step = 0;
    // ind.ele_num = 0;
    ind.datax = NULL;
    ind.datay = NULL;
}



/* function:
 * instruction: 
 * input:
 * return:
 *  */
Ind& Ind::operator=(Ind&& ind)
{
    cout << "Ind: moving assignment" << endl;

    this->ele_num = ind.ele_num;
    this->slice_start = ind.slice_start;
    this->slice_end = ind.slice_end;
    this->slice_step = ind.slice_step;
    this->datax = ind.datax;
    this->datay = ind.datay;

    ind.slice_start = 0;
    ind.slice_end = 0;
    ind.slice_end = 0;
    ind.ele_num = 0;
    ind.datax = NULL;
    ind.datay = NULL;

    return *this;
}




/* function:
 * instruction: 
 * input:
 * return:
 *  */
Ind::~Ind()
{
    delete[] datax;
    delete[] datay;

    slice_start = 0;
    slice_end = 0;
    slice_end = 0;
    ele_num = 0;
    datax = NULL;
    datay = NULL;
}




/* function:
 * instruction: 
 * input:
 * return:
 *  */
void Ind::print()
{

    if(ele_num != 0)
        for(long i = 0; i < ele_num; i++)
            cout << "(" << datax[i] << ", " << datay[i] << ")" << endl;

}



/* function:
 * instruction: 
 * input:
 * return:
 *  */
void Ind::free()
{
    delete[] datax;
    delete[] datay;
    slice_start = 0;
    slice_end = 0;
    slice_end = 0;
    ele_num = 0;
    datax = NULL;
    datay = NULL;
}




/* function:
 * instruction: 
 * input:
 * return:
 *  */
void Ind::init(const int num)
{
    ele_num = num;
    delete [] datax;
    delete [] datay;
    datax = new int[ele_num];
    datay = new int[ele_num];
}




/* function:
 * instruction: get the slice index with one number, works like a[ar:] in numpy
 * input:
 * return:
 *  */
Ind&& Ind::slice(int start, int end, int step)
{
    Ind res;

    res.slice_start = start; 
    res.slice_end = end;
    res.slice_step = step;

    return std::move(res);
}


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

    if(ind.ele_num != 0) // if indices are given separately
    {
        res.init(1, ind.ele_num);
        for(long i = 0; i < ind.ele_num; i++)
        {
            if(ind.datax[i] > N || ind.datay[i] > D)
            {
                cout << __FILE__ << ": " << __LINE__ << ": value of index must be constrained within the shape of Matrix (N, D)" << endl;
                exit(0);
            }
            res.data[i] = data[ind.datax[i]*D+ind.datay[i]];
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
Matrix2<T> Matrix2<T>::operator()(Ind&& in)
{
    Ind ind = in;
    Matrix2<T> res;
    int st, ed;
    int pos;
    int n;

    if(ind.slice_start < 0)
        st = N + ind.slice_start;
    else
        st = ind.slice_start;
    if(ind.slice_end <= 0)
        ed = N + ind.slice_end;
    else
        ed = ind.slice_end;
    if(st < 0 || ed > N)
    {
        cout << __FILE__ << ": " << __LINE__ << ": slice indices out of range" << endl;
        exit(0);
    }

    n = (ed - st) / ind.slice_step;
    pos = st*D;
    res.init(n,D);
    for(int i = 0; i < n; i++)
    {
        memcpy((res.data+i*D), data+pos*D, sizeof(T)*D);
        pos += ind.slice_step;
    }

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
            res.datay[i] = i;
            res.datax[i] = 0;
            for(int j = 0; j < N-1; j++)
            {
                pos += D;
                if(data[pos] > temp)
                {
                    temp = data[pos];
                    res.datax[i] = j+1;
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
            res.datax[i] = i;
            res.datay[i] = 0;
            for(int j = 0; j < D-1; j++, pos++)
            {
                if(temp < data[pos])
                {
                    temp = data[pos];
                    res.datay[i] = j+1;
                }
            }
        }
    }

    return std::move(res);

}



/* function:
 * instruction: 
 * input:
 * return: Index Matrix of relevant element
 *  */
template<class T>
Ind Matrix2<T>::argmax()
{
    Ind res;
    T temp;
    long pos;
    long count; // number of max elements

    temp = data[0];
    count = 1;
    for(long i = 0; i < ele_num; i++)
        if(temp > data[i])
            continue;
        else if(temp < data[i])
        {
            temp = data[i];
            count = 1; // recount
        }
        else
            count++;

    res.init(count);

    pos = 0;
    count = 0;
    for(int i = 0; i < N; i++)
        for(int j = 0; j < D; j++, pos++)
            if(temp == data[pos])
            {
                res.datax[count] = i;
                res.datay[count] = j;
                count++;
            }

    return std::move(res);

}

//////////////////////////







//
// class A
// {
//     public:
//         double *data;
//         int N;
//         int D;
//
//         A();
//         A(const A& a);
//         A(A&& a);
//         ~A();
//         void print();
//         A& operator=(A &a);
//         A& operator=(A&& a);
//         A* copy();
// };
//
//
// A& A::operator=(A& a)
// {
//     cout << "operator = called" <<endl;
//     this->N = a.N;
//     this->D = a.D;
//     free(this->data);
//     this->data = (double*)malloc(sizeof(double)*D*N);
//     memcpy(this->data, a.data, a.N*a.D*sizeof(double));
//     return *this;
// }
//
//
// A& A::operator=(A&& a)
// {
//     cout << "moving operator = called" <<endl;
//     this->N = a.N;
//     this->D = a.D;
//     free(this->data);
//     this->data = a.data;
//     a.data = NULL;
//     return *this;
// }
//
//
// // A& A::operator=(A& a)
// // {
// //     cout << "moving operator = called" <<endl;
// //     this->N = a.N;
// //     this->D = a.D;
// //     this->data = a.data;
// //     a.data = NULL;
// //     return *this;
// // }
//
//
// A::A()
// {
//     N = 5;
//     D = 4;
//     data = (double*)malloc(sizeof(double)*N*D);
//     cout << "A() called" <<endl;
// }
//
// A::A(const A& a)
// {
//     N = a.N;
//     D = a.D;
//     cout << "A(A& ) called" <<endl;
//     this->data = (double*)malloc(D*N*sizeof(double));
//     memcpy(this->data, a.data, D*N);
// }
//
//
// A::A(A&& a)
// {
//     N = a.N;
//     D = a.D;
//     data = a.data;
//     a.data = NULL;
//     cout << "A(A&& ) called" <<endl;
// }
//
// A::~A()
// {
//     cout << "destroying A" <<endl;
//     free(data);
// }
//
// // A* A::copy()
// // {
// //     A res;
// //     cout << "copying object " << endl;
// //     return &res;
// // }
//
//
// void A::print()
// {
//     const int DD = 5;
//     // double *dd;
//     //
//     // dd = data;
//
//     // double *a = new double[D];
//
//     // d = dynamic_cast<double(*)[D]>(a);
//
//     double (*d)[DD];
//     // d = new double[2][5];(double(*)[D])
//     // d = static_cast<double (*)[5]>(malloc(sizeof(double)*10));
//     d = reinterpret_cast<double (*)[DD]>(data);
//     // d = (double(*)[DD])data;
//     // int aa[D];
//
//
//     // d = (double(*)[DD])this->data;
//     for(int i = 0; i < N; i++)
//         cout << d[i] <<endl;
// }


#endif
