#ifndef _MATRIX_H_
#define _MATRIX_H_

#include<iostream>
#include<memory>





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

        Matrix2 operator=(Matrix2&);
        Matrix2 operator=(Matrix2&&);

        static Matrix2 ones(int n, int d);

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
    N = n;
    D = d;
    ele_num = N * D;
    data.reset(new T[ele_num], [](T* p){delete[] p;});
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
Matrix2<T> Matrix2<T>::operator=(Matrix2& m)
{
    N = m.N;
    D = m.D;
    ele_num = m.ele_num;
    data = m.data;
}


template<class T>
Matrix2<T> Matrix2<T>::operator=(Matrix2&& m)
{
    N = m.N;
    D = m.D;
    ele_num = m.ele_num;
    data = m.data;
}



/* creating routines */
template<class T>
Matrix2<T> Matrix2<T>::ones(int n, int d)
{
    Matrix2<T> mat(n, d);

    T* pd;
    long num;

    num = mat.ele_num;
    pd = mat.data.get();

    for(long i{0}; i < num; i++)
        pd[i] = 1;

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

// // Operators
// template<class T>
// Matrix2<T> Matrix2<T>::operator*(const Matrix2<T>& m)
// {
//     using namespace std;
//
//     T temp;
//     long pos;
//
//     // scenario where two matrices have same shape
//     if(N == m.N && D == m.D)
//     {
//         Matrix2<T> res(N,D);
//         for(long i = 0; i < ele_num; i++)
//             res.data[i] = data[i] * m.data[i];
//         return std::move(res);
//     }
//
//     // scenario where a is one-element matrix
//     else if(N == 1 && D == 1)
//     {
//         Matrix2<T> res(m.N,m.D);
//         temp = data[0];
//         for(long i = 0; i < m.ele_num; i++)
//             res.data[i] = temp * m.data[i];
//         return std::move(res);
//     }
//
//     // scenario where b is a one-element matrix
//     else if(m.N == 1 && m.D == 1)
//     {
//         Matrix2<T> res(N,D);
//         temp = m.data[0];
//         for(long i = 0; i < ele_num; i++)
//             res.data[i] = data[i] * temp;
//         return std::move(res);
//     }
//
//     // scenario where a is a matrix and b is a horizontal vector
//     else if(m.N == 1 && D == m.D)
//     {
//         Matrix2 res(N,D);
//         for(int i = 0; i < m.D; i++)
//         {
//             temp = m.data[i];
//             pos = i;
//             for(int j = 0; j < N; j++, pos+=D)
//                 res.data[pos] = data[pos] * temp;
//         }
//         return std::move(res);
//     }
//
//     // scenario where a is a matrix and b is a vertical vector
//     else if(N == m.N && m.D == 1)
//     {
//         Matrix2 res(N,D);
//         pos = 0;
//         for(int i = 0; i < N; i++)
//         {
//             temp = m.data[i];
//             for(int j = 0; j < D; j++, pos++)
//                 res.data[pos] = data[pos] * temp;
//         }
//         return std::move(res);
//     }
//
//     // scenario where a is a horizontal vector and b is a Matrix
//     else if(N == 1 && D == m.D)
//     {
//         Matrix2<T> res(m.N,m.D);
//         for(int i = 0; i < m.D; i++)
//         {
//             pos = i;
//             temp = data[i];
//             for(int j = 0; j < m.N; j++, pos+=D)
//                 res.data[pos] = temp * m.data[pos];
//         }
//         return std::move(res);
//     }
//
//     // scenario where a is a vertical vector and b is a Matrix
//     else if(D == 1 && N == m.N)
//     {
//         Matrix2<T> res(m.N,m.D);
//         pos = 0;
//         for(int i = 0; i < m.N; i++)
//         {
//             temp = data[i];
//             for(int j = 0; j < m.D; j++, pos++)
//                 res.data[pos] = temp * m.data[pos];
//         }
//         return std::move(res);
//     }
//
//     else
//     {
//         cout << __FILE__ << ":" << __LINE__ <<" : ERROR: Matrix * requires input matrices have associated shapes" << endl;
//         exit(0);
//     }
// }
//
//
//
/* function:
 * instruction:
 * input:
 * return:
 *  */
// template<class T>
// Matrix2<T> Matrix2<T>::operator*(const T m)
// {
//     using namespace std;
//
//     Matrix2<T> res(N,D);
//     for(long i = 0; i < ele_num; i++)
//         res.data[i] = data[i] * m;
//
//     return std::move(res);
// }
//
//
//
/* function:
 * instruction:
 * input:
 * return:
 *  */
// template<class C>
// Matrix2<C> operator*(const C n, const Matrix2<C>& m)
// {
//     using namespace std;
//
//     Matrix2<C> res(m.N,m.D);
//     for(long i = 0; i < m.ele_num; i++)
//         res.data[i] = m.data[i] * n;
//
//     return std::move(res);
// }
//
//
/* function:
 * instruction:
 * input:
 * return:
 *  */
// template<class T>
// Matrix2<T> Matrix2<T>::operator/(const Matrix2<T>& m)
// {
//     using namespace std;
//
//     T temp;
//     long pos;
//
//     // scenario where two matrices have same shape
//     if(N == m.N && D == m.D)
//     {
//         Matrix2<T> res(N,D);
//         for(long i = 0; i < ele_num; i++)
//             res.data[i] = data[i] / m.data[i];
//         return std::move(res);
//     }
//
//     // scenario where a is one-element matrix
//     else if(N == 1 && D == 1)
//     {
//         Matrix2<T> res(m.N,m.D);
//         temp = data[0];
//         for(long i = 0; i < m.ele_num; i++)
//             res.data[i] = temp / m.data[i];
//         return std::move(res);
//     }
//
//     // scenario where b is a one-element matrix
//     else if(m.N == 1 && m.D == 1)
//     {
//         Matrix2<T> res(N,D);
//         temp = m.data[0];
//         for(long i = 0; i < ele_num; i++)
//             res.data[i] = data[i] / temp;
//         return std::move(res);
//     }
//
//     // scenario where a is a matrix and b is a horizontal vector
//     else if(m.N == 1 && D == m.D)
//     {
//         Matrix2 res(N,D);
//         for(int i = 0; i < m.D; i++)
//         {
//             temp = m.data[i];
//             pos = i;
//             for(int j = 0; j < N; j++, pos+=D)
//                 res.data[pos] = data[pos] / temp;
//         }
//         return std::move(res);
//     }
//
//     // scenario where a is a matrix and b is a vertical vector
//     else if(N == m.N && m.D == 1)
//     {
//         Matrix2 res(N,D);
//         pos = 0;
//         for(int i = 0; i < N; i++)
//         {
//             temp = m.data[i];
//             for(int j = 0; j < D; j++, pos++)
//                 res.data[pos] = data[pos] / temp;
//         }
//         return std::move(res);
//     }
//
//     // scenario where a is a horizontal vector and b is a Matrix
//     else if(N == 1 && D == m.D)
//     {
//         Matrix2<T> res(m.N,m.D);
//         for(int i = 0; i < m.D; i++)
//         {
//             pos = i;
//             temp = data[i];
//             for(int j = 0; j < m.N; j++, pos+=D)
//                 res.data[pos] = temp / m.data[pos];
//         }
//         return std::move(res);
//     }
//
//     // scenario where a is a vertical vector and b is a Matrix
//     else if(D == 1 && N == m.N)
//     {
//         Matrix2<T> res(m.N,m.D);
//         pos = 0;
//         for(int i = 0; i < m.N; i++)
//         {
//             temp = data[i];
//             for(int j = 0; j < m.D; j++, pos++)
//                 res.data[pos] = temp / m.data[pos];
//         }
//         return std::move(res);
//     }
//
//     else
//     {
//         cout << __FILE__ << ":" << __LINE__ <<" : ERROR: Matrix / requires input matrices have associated shapes" << endl;
//         exit(0);
//     }
// }
//
//
//
/* function:
 * instruction:
 * input:
 * return:
 *  */
// template<class T>
// Matrix2<T> Matrix2<T>::operator/(const T m)
// {
//     using namespace std;
//
//     Matrix2<T> res(N,D);
//     for(long i = 0; i < ele_num; i++)
//         res.data[i] = data[i] / m;
//
//     return std::move(res);
// }
//
//
//
/* function:
 * instruction:
 * input:
 * return:
 *  */
// template<class C>
// Matrix2<C> operator/(const C n, const Matrix2<C>& m)
// {
//     Matrix2<C> res(m.N,m.D);
//     for(long i = 0; i < m.ele_num; i++)
//         res.data[i] = n / m.data[i];
//
//     return std::move(res);
// }
//
//
//
//
/* function:
 * instruction:
 * input:
 * return:
 *  */
// template<class T>
// Matrix2<T> Matrix2<T>::operator+(const Matrix2<T>& m)
// {
//     using namespace std;
//
//     T temp;
//     long pos;
//
//     // scenario where two matrices have same shape
//     if(N == m.N && D == m.D)
//     {
//         Matrix2<T> res(N,D);
//         for(long i = 0; i < ele_num; i++)
//             res.data[i] = data[i] + m.data[i];
//         return std::move(res);
//     }
//
//     // scenario where a is one-element matrix
//     else if(N == 1 && D == 1)
//     {
//         Matrix2<T> res(m.N,m.D);
//         temp = data[0];
//         for(long i = 0; i < m.ele_num; i++)
//             res.data[i] = temp + m.data[i];
//         return std::move(res);
//     }
//
//     // scenario where b is a one-element matrix
//     else if(m.N == 1 && m.D == 1)
//     {
//         Matrix2<T> res(N,D);
//         temp = m.data[0];
//         for(long i = 0; i < ele_num; i++)
//             res.data[i] = data[i] + temp;
//         return std::move(res);
//     }
//
//     // scenario where a is a matrix and b is a horizontal vector
//     else if(m.N == 1 && D == m.D)
//     {
//         Matrix2 res(N,D);
//         for(int i = 0; i < m.D; i++)
//         {
//             temp = m.data[i];
//             pos = i;
//             for(int j = 0; j < N; j++, pos+=D)
//                 res.data[pos] = data[pos] + temp;
//         }
//         return std::move(res);
//     }
//
//     // scenario where a is a matrix and b is a vertical vector
//     else if(N == m.N && m.D == 1)
//     {
//         Matrix2 res(N,D);
//         pos = 0;
//         for(int i = 0; i < N; i++)
//         {
//             temp = m.data[i];
//             for(int j = 0; j < D; j++, pos++)
//                 res.data[pos] = data[pos] + temp;
//         }
//         return std::move(res);
//     }
//
//     // scenario where a is a horizontal vector and b is a Matrix
//     else if(N == 1 && D == m.D)
//     {
//         Matrix2<T> res(m.N,m.D);
//         for(int i = 0; i < m.D; i++)
//         {
//             pos = i;
//             temp = data[i];
//             for(int j = 0; j < m.N; j++, pos+=D)
//                 res.data[pos] = temp + m.data[pos];
//         }
//         return std::move(res);
//     }
//
//     // scenario where a is a vertical vector and b is a Matrix
//     else if(D == 1 && N == m.N)
//     {
//         Matrix2<T> res(m.N,m.D);
//         pos = 0;
//         for(int i = 0; i < m.N; i++)
//         {
//             temp = data[i];
//             for(int j = 0; j < m.D; j++, pos++)
//                 res.data[pos] = temp + m.data[pos];
//         }
//         return std::move(res);
//     }
//
//     else
//     {
//         cout << __FILE__ << ":" << __LINE__ <<" : ERROR: Matrix + requires input matrices have associated shapes" << endl;
//         exit(0);
//     }
// }
//
//
//
/* function:
 * instruction:
 * input:
 * return:
 *  */
// template<class T>
// Matrix2<T> Matrix2<T>::operator+(const T m)
// {
//     Matrix2<T> res(N,D);
//     for(long i = 0; i < ele_num; i++)
//         res.data[i] = data[i] + m;
//
//     return std::move(res);
// }
//
//
//
/* function:
 * instruction:
 * input:
 * return:
 *  */
// template<class C>
// Matrix2<C> operator+(const C n, const Matrix2<C>& m)
// {
//     Matrix2<C> res(m.N,m.D);
//     for(long i = 0; i < m.ele_num; i++)
//         res.data[i] = n + m.data[i];
//
//     return res;
// }
//
//
//
/* function:
 * instruction:
 * input:
 * return:
 *  */
// template<class C>
// Matrix2<C> operator-(const C n, const Matrix2<C>& m)
// {
//     Matrix2<C> res(m.N,m.D);
//     for(long i = 0; i < m.ele_num; i++)
//         res.data[i] = n - m.data[i];
//
//     return std::move(res);
// }
//
//
//
/* function:
 * instruction:
 * input:
 * return:
 *  */
// template<class T>
// Matrix2<T> Matrix2<T>::operator-(const Matrix2<T>& m)
// {
//
//     using namespace std;
//
//     T temp;
//     long pos;
//
//     // scenario where two matrices have same shape
//     if(N == m.N && D == m.D)
//     {
//         Matrix2<T> res(N,D);
//         for(long i = 0; i < ele_num; i++)
//             res.data[i] = data[i] - m.data[i];
//         return std::move(res);
//     }
//
//     // scenario where a is one-element matrix
//     else if(N == 1 && D == 1)
//     {
//         Matrix2<T> res(m.N,m.D);
//         temp = data[0];
//         for(long i = 0; i < m.ele_num; i++)
//             res.data[i] = temp - m.data[i];
//         return std::move(res);
//     }
//
//     // scenario where b is a one-element matrix
//     else if(m.N == 1 && m.D == 1)
//     {
//         Matrix2<T> res(N,D);
//         temp = m.data[0];
//         for(long i = 0; i < ele_num; i++)
//             res.data[i] = data[i] - temp;
//         return std::move(res);
//     }
//
//     // scenario where a is a matrix and b is a horizontal vector
//     else if(m.N == 1 && D == m.D)
//     {
//         Matrix2 res(N,D);
//         for(int i = 0; i < m.D; i++)
//         {
//             temp = m.data[i];
//             pos = i;
//             for(int j = 0; j < N; j++, pos+=D)
//                 res.data[pos] = data[pos] - temp;
//         }
//         return std::move(res);
//     }
//
//     // scenario where a is a matrix and b is a vertical vector
//     else if(N == m.N && m.D == 1)
//     {
//         Matrix2 res(N,D);
//         pos = 0;
//         for(int i = 0; i < N; i++)
//         {
//             temp = m.data[i];
//             for(int j = 0; j < D; j++, pos++)
//                 res.data[pos] = data[pos] - temp;
//         }
//         return std::move(res);
//     }
//
//     // scenario where a is a horizontal vector and b is a Matrix
//     else if(N == 1 && D == m.D)
//     {
//         Matrix2<T> res(m.N,m.D);
//         for(int i = 0; i < m.D; i++)
//         {
//             pos = i;
//             temp = data[i];
//             for(int j = 0; j < m.N; j++, pos+=D)
//                 res.data[pos] = temp - m.data[pos];
//         }
//         return std::move(res);
//     }
//
//     // scenario where a is a vertical vector and b is a Matrix
//     else if(D == 1 && N == m.N)
//     {
//         Matrix2<T> res(m.N,m.D);
//         pos = 0;
//         for(int i = 0; i < m.N; i++)
//         {
//             temp = data[i];
//             for(int j = 0; j < m.D; j++, pos++)
//                 res.data[pos] = temp - m.data[pos];
//         }
//         return std::move(res);
//     }
//
//     else
//     {
//         cout << __FILE__ << ":" << __LINE__ <<" : ERROR: Matrix + requires input matrices have associated shapes" << endl;
//         exit(0);
//     }
// }
//
//
/* function:
 * instruction:
 * input:
 * return:
 *  */
// template<class T>
// Matrix2<T> Matrix2<T>::operator-(const T m)
// {
//     Matrix2<T> res(N,D);
//     for(long i = 0; i < ele_num; i++)
//         res.data[i] = data[i] - m;
//
//     return std::move(res);
// }
//


#endif




