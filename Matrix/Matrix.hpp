#ifndef _MATRIX_H_
#define _MATRIX_H_

#include<iostream>
#include<memory>
#include<cassert>
#include<cmath>

// #include"proto.h"
// #include"constructor.h"
// #include"assign.h"
// #include"operator.h"
// #include"compute.h"




template <class T>
class Matrix2
{
    public:
        // data
        int N;
        int D;
        long ele_num;
        std::shared_ptr<T> data;

        // functions
        Matrix2();
        Matrix2(int n, int d);
        Matrix2(Matrix2&);
        Matrix2(Matrix2&&);

        Matrix2& operator=(Matrix2&);
        Matrix2& operator=(Matrix2&&);
        Matrix2 operator+(Matrix2&);
        Matrix2 operator-(Matrix2&);
        Matrix2 operator*(Matrix2&);
        Matrix2 operator/(Matrix2&);
        template<class C>
        friend Matrix2<C> operator+(C n, Matrix2<C>& m);
        template<class C>
        friend Matrix2<C> operator-(C n, Matrix2<C>& m);
        template<class C>
        friend Matrix2<C> operator*(C n, Matrix2<C>& m);
        template<class C>
        friend Matrix2<C> operator/(C n, Matrix2<C>& m);

        static Matrix2 ones(int n, int d);
        static Matrix2 zeros(int n, int d);
        static Matrix2 arange(int n);
        static Matrix2 arange(int a, int b);

        Matrix2 reshape(int n ,int d);
        Matrix2 copy();

        Matrix2 dot(Matrix2&);

        Matrix2 exp();
        Matrix2 sum(int axis=0);
        
        void print();
};


/* constructors */

template<class T>
Matrix2<T>::Matrix2()
{
    N = 0;
    D = 0;
    ele_num =0;
    data = nullptr;
}



template<class T>
Matrix2<T>::Matrix2(int n, int d)
{
    if(n*d != 0)
    {
        N = n;
        D = d;
        ele_num = N * D;
        data.reset(new T[ele_num], [](T* p){delete[] p;});
    }
    else
    {
        N = 0;
        D = 0;
        ele_num = 0;
        data = nullptr;
    }
}



template<class T>
Matrix2<T>::Matrix2(Matrix2<T>&& m)
{
    N = m.N;
    D = m.D;
    ele_num = m.ele_num;
    data = m.data;
} 


template<class T>
Matrix2<T>::Matrix2(Matrix2<T>& m)
{
    N = m.N;
    D = m.D;
    ele_num = m.ele_num;
    data = m.data;
} 


/* operators */
template<class T>
Matrix2<T>& Matrix2<T>::operator=(Matrix2& m)
{
    if (this != &m)
    {
        N = m.N;
        D = m.D;
        ele_num = m.ele_num;
        data = m.data;
    }

    return *this;
}


template<class T>
Matrix2<T>& Matrix2<T>::operator=(Matrix2&& m)
{
    if (this != &m)
    {
        N = m.N;
        D = m.D;
        ele_num = m.ele_num;
        data = m.data;
    }

    return *this;
}




template<class T>
Matrix2<T> Matrix2<T>::operator+(Matrix2& other)
{
    int dN{other.N};
    int dD{other.D};
    T *p{data.get()};
    T *dp{other.data.get()};

    assert((dN*dD*N*D) != 0);

    // scenario where two matrices have same shape
    if(N == dN && D == dD) 
    {
        Matrix2<T> mat(N,D);
        T* mp{mat.data.get()};

        for(long i{0}; i < ele_num; i++)
            mp[i] = p[i] + dp[i];
        return mat;
    }

    // scenario where divident is a one-element matrix
    else if(N == 1 && D == 1)
    {
        Matrix2<T> mat(dN, dD);
        T* mp{mat.data.get()};
        T temp{data.get()[0]};
        long num{other.ele_num};

        for(long i{0}; i < num; i++)
            mp[i] = temp + dp[i];
        return mat;
    }

    // scenario where other is a one-element matrix
    else if(dN == 1 && dD == 1)
    {
        Matrix2<T> mat(N, D);
        T* mp{mat.data.get()};
        T temp{dp[0]};

        for(long i{0}; i < ele_num; i++)
            mp[i] = p[i] + temp;
        return mat;
    }

    // scenario where a is a matrix and b is a horizontal vector
    else if(dN == 1 && D == dD)
    {
        Matrix2<T> mat(N, D);
        T* mp{mat.data.get()};
        T temp;
        long pos;

        for(int i{0}; i < dD; i++)
        {
            temp = dp[i];
            pos = i;
            for(int j{0}; j < N; j++, pos+=D)
                mp[pos] = p[pos] + temp;
        }
        return mat;
    }

    // scenario where a is a matrix and b is a vertical vector
    else if(N == dN && dD == 1) 
    {
        Matrix2<T> mat(N, D);
        T* mp{mat.data.get()};
        long pos{0};
        T temp;

        for(int i{0}; i < N; i++)
        {
            temp = dp[i];
            for(int j{0}; j < D; j++, pos++)
                mp[pos] = p[pos] + temp;
        }
        return mat;
    }

    // scenario where a is a horizontal vector and b is a Matrix
    else if(N == 1 && D == dD)
    {
        Matrix2<T> mat(dN, dD);
        T* mp{mat.data.get()};
        long pos;
        T temp;

        for(int i{0}; i < dD; i++)
        {
            pos = i;
            temp = p[i];
            for(int j{0}; j < dN; j++, pos+=D)
                mp[pos] = temp + dp[pos]; 
        }
        return mat;
    }

    // scenario where a is a vertical vector and b is a Matrix
    else if(D == 1 && N == dN)
    {
        Matrix2<T> mat(dN, dD);
        T* mp{mat.data.get()};
        long pos = 0;
        T temp;

        for(int i{0}; i < dN; i++)
        {
            temp = p[i];
            for(int j{0}; j < dD; j++, pos++)
                mp[pos] = temp + dp[pos]; 
        }
        return mat;
    }

    else
    {
        std::cout << "Two matrices do not match in shape" << std::endl;
        assert(false);
    }

}





template<class T>
Matrix2<T> Matrix2<T>::operator-(Matrix2& other)
{
    int dN{other.N};
    int dD{other.D};
    T *p{data.get()};
    T *dp{other.data.get()};

    assert((dN*dD*N*D) != 0);

    // scenario where two matrices have same shape
    if(N == dN && D == dD) 
    {
        Matrix2<T> mat(N,D);
        T* mp{mat.data.get()};

        for(long i{0}; i < ele_num; i++)
            mp[i] = p[i] - dp[i];
        return mat;
    }

    // scenario where divident is a one-element matrix
    else if(N == 1 && D == 1)
    {
        Matrix2<T> mat(dN, dD);
        T* mp{mat.data.get()};
        T temp{data.get()[0]};
        long num{other.ele_num};

        for(long i{0}; i < num; i++)
            mp[i] = temp - dp[i];
        return mat;
    }

    // scenario where other is a one-element matrix
    else if(dN == 1 && dD == 1)
    {
        Matrix2<T> mat(N, D);
        T* mp{mat.data.get()};
        T temp{dp[0]};

        for(long i{0}; i < ele_num; i++)
            mp[i] = p[i] - temp;
        return mat;
    }

    // scenario where a is a matrix and b is a horizontal vector
    else if(dN == 1 && D == dD)
    {
        Matrix2<T> mat(N, D);
        T* mp{mat.data.get()};
        T temp;
        long pos;

        for(int i{0}; i < dD; i++)
        {
            temp = dp[i];
            pos = i;
            for(int j{0}; j < N; j++, pos+=D)
                mp[pos] = p[pos] - temp;
        }
        return mat;
    }

    // scenario where a is a matrix and b is a vertical vector
    else if(N == dN && dD == 1) 
    {
        Matrix2<T> mat(N, D);
        T* mp{mat.data.get()};
        long pos{0};
        T temp;

        for(int i{0}; i < N; i++)
        {
            temp = dp[i];
            for(int j{0}; j < D; j++, pos++)
                mp[pos] = p[pos] - temp;
        }
        return mat;
    }

    // scenario where a is a horizontal vector and b is a Matrix
    else if(N == 1 && D == dD)
    {
        Matrix2<T> mat(dN, dD);
        T* mp{mat.data.get()};
        long pos;
        T temp;

        for(int i{0}; i < dD; i++)
        {
            pos = i;
            temp = p[i];
            for(int j{0}; j < dN; j++, pos+=D)
                mp[pos] = temp - dp[pos]; 
        }
        return mat;
    }

    // scenario where a is a vertical vector and b is a Matrix
    else if(D == 1 && N == dN)
    {
        Matrix2<T> mat(dN, dD);
        T* mp{mat.data.get()};
        long pos = 0;
        T temp;

        for(int i{0}; i < dN; i++)
        {
            temp = p[i];
            for(int j{0}; j < dD; j++, pos++)
                mp[pos] = temp - dp[pos]; 
        }
        return mat;
    }

    else
    {
        std::cout << "Two matrices do not match in shape" << std::endl;
        assert(false);
    }

}




template<class T>
Matrix2<T> Matrix2<T>::operator*(Matrix2& other)
{
    int dN{other.N};
    int dD{other.D};
    T *p{data.get()};
    T *dp{other.data.get()};

    assert((dN*dD*N*D) != 0);

    // scenario where two matrices have same shape
    if(N == dN && D == dD) 
    {
        Matrix2<T> mat(N,D);
        T* mp{mat.data.get()};

        for(long i{0}; i < ele_num; i++)
            mp[i] = p[i] * dp[i];
        return mat;
    }

    // scenario where divident is a one-element matrix
    else if(N == 1 && D == 1)
    {
        Matrix2<T> mat(dN, dD);
        T* mp{mat.data.get()};
        T temp{data.get()[0]};
        long num{other.ele_num};

        for(long i{0}; i < num; i++)
            mp[i] = temp * dp[i];
        return mat;
    }

    // scenario where other is a one-element matrix
    else if(dN == 1 && dD == 1)
    {
        Matrix2<T> mat(N, D);
        T* mp{mat.data.get()};
        T temp{dp[0]};

        for(long i{0}; i < ele_num; i++)
            mp[i] = p[i] * temp;
        return mat;
    }

    // scenario where a is a matrix and b is a horizontal vector
    else if(dN == 1 && D == dD)
    {
        Matrix2<T> mat(N, D);
        T* mp{mat.data.get()};
        T temp;
        long pos;

        for(int i{0}; i < dD; i++)
        {
            temp = dp[i];
            pos = i;
            for(int j{0}; j < N; j++, pos+=D)
                mp[pos] = p[pos] * temp;
        }
        return mat;
    }

    // scenario where a is a matrix and b is a vertical vector
    else if(N == dN && dD == 1) 
    {
        Matrix2<T> mat(N, D);
        T* mp{mat.data.get()};
        long pos{0};
        T temp;

        for(int i{0}; i < N; i++)
        {
            temp = dp[i];
            for(int j{0}; j < D; j++, pos++)
                mp[pos] = p[pos] * temp;
        }
        return mat;
    }

    // scenario where a is a horizontal vector and b is a Matrix
    else if(N == 1 && D == dD)
    {
        Matrix2<T> mat(dN, dD);
        T* mp{mat.data.get()};
        long pos;
        T temp;

        for(int i{0}; i < dD; i++)
        {
            pos = i;
            temp = p[i];
            for(int j{0}; j < dN; j++, pos+=D)
                mp[pos] = temp * dp[pos]; 
        }
        return mat;
    }

    // scenario where a is a vertical vector and b is a Matrix
    else if(D == 1 && N == dN)
    {
        Matrix2<T> mat(dN, dD);
        T* mp{mat.data.get()};
        long pos = 0;
        T temp;

        for(int i{0}; i < dN; i++)
        {
            temp = p[i];
            for(int j{0}; j < dD; j++, pos++)
                mp[pos] = temp * dp[pos]; 
        }
        return mat;
    }

    else
    {
        std::cout << "Two matrices do not match in shape" << std::endl;
        assert(false);
    }

}



template<class T>
Matrix2<T> Matrix2<T>::operator/(Matrix2& other)
{
    int dN{other.N};
    int dD{other.D};
    T *p{data.get()};
    T *dp{other.data.get()};

    assert((dN*dD*N*D) != 0);

    // scenario where two matrices have same shape
    if(N == dN && D == dD) 
    {
        Matrix2<T> mat(N,D);
        T* mp{mat.data.get()};

        for(long i{0}; i < ele_num; i++)
            mp[i] = p[i] / dp[i];
        return mat;
    }

    // scenario where divident is a one-element matrix
    else if(N == 1 && D == 1)
    {
        Matrix2<T> mat(dN, dD);
        T* mp{mat.data.get()};
        T temp{data.get()[0]};
        long num{other.ele_num};

        for(long i{0}; i < num; i++)
            mp[i] = temp / dp[i];
        return mat;
    }

    // scenario where other is a one-element matrix
    else if(dN == 1 && dD == 1)
    {
        Matrix2<T> mat(N, D);
        T* mp{mat.data.get()};
        T temp{dp[0]};

        for(long i{0}; i < ele_num; i++)
            mp[i] = p[i] / temp;
        return mat;
    }

    // scenario where a is a matrix and b is a horizontal vector
    else if(dN == 1 && D == dD)
    {
        Matrix2<T> mat(N, D);
        T* mp{mat.data.get()};
        T temp;
        long pos;

        for(int i{0}; i < dD; i++)
        {
            temp = dp[i];
            pos = i;
            for(int j{0}; j < N; j++, pos+=D)
                mp[pos] = p[pos] / temp;
        }
        return mat;
    }

    // scenario where a is a matrix and b is a vertical vector
    else if(N == dN && dD == 1) 
    {
        Matrix2<T> mat(N, D);
        T* mp{mat.data.get()};
        long pos{0};
        T temp;

        for(int i{0}; i < N; i++)
        {
            temp = dp[i];
            for(int j{0}; j < D; j++, pos++)
                mp[pos] = p[pos] / temp;
        }
        return mat;
    }

    // scenario where a is a horizontal vector and b is a Matrix
    else if(N == 1 && D == dD)
    {
        Matrix2<T> mat(dN, dD);
        T* mp{mat.data.get()};
        long pos;
        T temp;

        for(int i{0}; i < dD; i++)
        {
            pos = i;
            temp = p[i];
            for(int j{0}; j < dN; j++, pos+=D)
                mp[pos] = temp / dp[pos]; 
        }
        return mat;
    }

    // scenario where a is a vertical vector and b is a Matrix
    else if(D == 1 && N == dN)
    {
        Matrix2<T> mat(dN, dD);
        T* mp{mat.data.get()};
        long pos = 0;
        T temp;

        for(int i{0}; i < dN; i++)
        {
            temp = p[i];
            for(int j{0}; j < dD; j++, pos++)
                mp[pos] = temp / dp[pos]; 
        }
        return mat;
    }

    else
    {
        std::cout << "Two matrices do not match in shape" << std::endl;
        assert(false);
    }

}



template<class C>
Matrix2<C> operator+(C n, Matrix2<C>& m)
{
    Matrix2<C> mat(m.N, m.D);
    C *p{m.data.get()};
    C *mp{mat.data.get()};

    long num = m.ele_num;
    for(long i{0}; i<num; i++)
        mp[i] = p[i] + n;

    return mat;
}



template<class C>
Matrix2<C> operator-(C n, Matrix2<C>& m)
{
    Matrix2<C> mat(m.N, m.D);
    C *p{m.data.get()};
    C *mp{mat.data.get()};

    long num = m.ele_num;
    for(long i{0}; i<num; i++)
        mp[i] = p[i] - n;

    return mat;
}




template<class C>
Matrix2<C> operator*(C n, Matrix2<C>& m)
{
    Matrix2<C> mat(m.N, m.D);
    C *p{m.data.get()};
    C *mp{mat.data.get()};

    long num = m.ele_num;
    for(long i{0}; i<num; i++)
        mp[i] = p[i] * n;

    return mat;
}




template<class C>
Matrix2<C> operator/(C n, Matrix2<C>& m)
{
    Matrix2<C> mat(m.N, m.D);
    C *p{m.data.get()};
    C *mp{mat.data.get()};

    long num = m.ele_num;
    for(long i{0}; i<num; i++)
        mp[i] = p[i] / n;

    return mat;
}



/* creating routines */
template<class T>
Matrix2<T> Matrix2<T>::ones(int n, int d)
{
    Matrix2<T> mat(n, d);

    T* pd;
    long num;

    if(n*d != 0)
    {
        num = mat.ele_num;
        pd = mat.data.get();

        for(long i{0}; i < num; i++)
            pd[i] = 1;
    }

    return mat;
}


template<class T>
Matrix2<T> Matrix2<T>::zeros(int n, int d)
{
    Matrix2<T> mat(n,d);

    if(n*d != 0)
    {
        T* pd = mat.data.get();
        long num = mat.ele_num;

        for(long i{0}; i<num; i++)
            pd[i] = 0;
    }

    return mat;
}



template<class T>
Matrix2<T> Matrix2<T>::arange(int N)
{
    Matrix2<T> mat(1, N);

    if(N != 0)
    {
        T* dp = mat.data.get();
        long num = mat.ele_num;

        for(long i{0}; i<num; i++)
            dp[i] = i;
    }

    return mat;
}



template<class T>
Matrix2<T> Matrix2<T>::arange(int a, int b)
{
    Matrix2<T> mat;

    if (a < b)
    {
        mat = Matrix2<T>(1, b-a);
        T* dp = mat.data.get();
        long num = mat.ele_num;

        for(long i{0}; i<num; i++)
            dp[i] = a + i;
    }

    return mat;
}




template<class T>
Matrix2<T> Matrix2<T>::reshape(int n, int d)
{
    assert(n*d == N*D);

    Matrix2<T> mat(n,d);
    T* dp1{data.get()};
    T* dp2{mat.data.get()};
    long num{ele_num};

    for(int i{0}; i<num; i++)
        dp2[i] = dp1[i];

    return mat;
}




template<class T>
Matrix2<T> Matrix2<T>::copy()
{
    Matrix2<T> mat(N, D);
    T* fp{data.get()};
    T* tp{mat.data.get()};
    
    for(long i{0}; i<ele_num; i++)
        tp[i] = fp[i];

    return mat;
}




template<class T>
Matrix2<T> Matrix2<T>::dot(Matrix2& mr)
{
    T* dl{data.get()}; 
    T* dr{mr.data.get()}; 
    int N1{N}; 
    int D1{D}; 
    int N2{mr.N}; 
    int D2{mr.D};

    Matrix2<T> mat = Matrix2<T>::zeros(N1,D2); 
    T* dm = mat.data.get();

    // TODO: add boundary check here
    assert(D1==N2);
    assert(data != nullptr);
    assert(mr.data != nullptr);

    long pos_mat{0};
    long pos1{0}, pos2{0};
    long row1{0};
    for(int i{0}; i<N1; i++)
    {
        for(int j{0}; j<D2; j++)
        {
            pos1 = row1;
            pos2 = j;
            for(int k{0}; k<N2; k++)
            {
                dm[pos_mat] += dl[pos1] * dr[pos2];
                pos1 ++;
                pos2 += D2;
            }
            pos_mat ++;;
        }
        row1 += D1;
    }

    return mat;
}



template<class T>
Matrix2<T> Matrix2<T>::exp()
{
    Matrix2<T> mat(N, D);
    T* fp{data.get()};
    T* tp{mat.data.get()};

    for(long i{0}; i<ele_num; i++)
        tp[i] = std::exp(fp[i]);

    return mat;
}



template<class T>
Matrix2<T> Matrix2<T>::sum(int axis)
{

    Matrix2<T> mat;
    if (axis == 0)
    {
        mat = Matrix2<T>::zeros(1,D);
        T* mp{mat.data.get()};
        T* p{data.get()};
        long pos{0};

        for (long i{0}; i<ele_num; i++, pos++)
        {
            if (pos % D == 0)
                pos = 0;

            mp[pos] += p[i];
        }

    }

    else if (axis == 1)
    {
        mat = Matrix2<T>::zeros(N,1);
        T* mp{mat.data.get()};
        T* p{data.get()};
        long pos{0};

        for (long i{0}; i<ele_num; i++)
        {
            if (i % D == 0)
                pos ++;
            mp[pos-1] += p[i];
        }
            
    }

    else
    {
        std::cout << "does not support dimensions over 3" << std::endl;
        assert(false);
    }

    return mat;
}



template<class T>
void Matrix2<T>::print()
{
    using namespace std;

    T *pd{data.get()};

    cout << "[ " << endl;;
    for(int i{0}; i < N; i++)
    {
        for(int j{0}; j < D; j++)
            cout << pd[i*D+j] << ", ";
        cout << endl;
    }
    cout << "] " << endl;
}




#endif




