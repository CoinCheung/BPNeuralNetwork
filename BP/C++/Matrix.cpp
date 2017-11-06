// #include"Matrix.h"


// template<class T>
// Matrix2<T>::Matrix2(int n, int d)
// {
//     N = n;
//     D = d;
//     ele_num = n * d;
//     data = (T(*)[D])malloc(sizeof(T)*ele_num);
// }
//
//
//
// template<class T>
// Matrix2<T>::~Matrix2()
// {
//     free(data);
// }
//
//
// template<class T>
// Matrix2<T> Matrix2<T>::ones(int N, int D)
// {
//     Matrix2 ret(N,D);
//     for(long i = 0; i < ret.ele_num; i++)
//         ret.data[i] = 1;
//
//     return ret;
// }
//
//
// template<class T>
// void Matrix2<T>::print()
// {
//     for(int i = 0; i < N; i++)
//     {
//         for(int j = 0; j < D; j++)
//             cout<<data[i][j] << " ,";
//         cout<<endl;
//     }
//
// }
//
//
//
// int trry::fun()
// {
//     return 1;
// }
//
