#include"Matrix.h"



void tryMatrix2();
A test_construct();



int main(void)
{
    cout<< "long time no see c++" <<endl;

    //
    // Matrix2<double> m(3,3);

    // Matrix2<double> mm = Matrix2<double>::ones(3,3);
    // mm.print();

    // A a;
    // a.print();

    // printlines();

    // tryMatrix2();

    // A b;

    // cout << "before function called " <<endl;
    //
    // A&& b = test_construct();
    //
    // for(int i = 0; i < 20; i++)
    //     cout << "b.data[i] is: "<< b.data[i] <<endl;

    tryMatrix2();


    return 0;
}


A test_construct()
{
    A a;
    A b;

    a.N = 100;
    for(int i = 0; i < 20; i++)
        a.data[i] = 5555;

    cout << "before assign a to b"<<endl;
    b = a;
    cout << "after assign a to b"<<endl;

    // return a;
    return std::move(a);
}


void tryMatrix2()
{
    Matrix2<double> res;
    Matrix2<double> m;
    Matrix2<double> n;

    // cout << "zeros(4)"<<endl;
    // m = Matrix2<double>::zeros(4);
    // cout << "Matrix m is: " <<endl;
    // m.print();

    // cout << "ones(4,5)"<<endl;
    // m = Matrix2<double>::zeros(4,5);
    // cout << "Matrix m is: " <<endl;m.print();
    // n = Matrix2<double>::zeros(1,4);
    // cout << "Matrix n is: " <<endl;n.print();
    // m.free();n.free();
    //
    // m = Matrix2<double>::ones(5,4);
    // cout << "Matrix m is: " <<endl;m.print();
    // n = Matrix2<double>::ones(4,1);
    // cout << "Matrix n is: " <<endl;n.print();
    // res = Matrix2<double>::dot(m,n);
    // cout << "static dot result is: " <<endl;res.print();
    // m.free(); n.free(); res.free();
    //
    // m = Matrix2<double>::ones(4,1);
    // cout << "Matrix m is: " <<endl;m.print();
    // n = Matrix2<double>::ones(1,5);
    // cout << "Matrix n is: " <<endl;n.print();
    // res = Matrix2<double>::dot(m,n);
    // cout << "static dot result is: " <<endl;res.print();
    // m.free(); n.free(); res.free();
    //
    // m = Matrix2<double>::ones(1,5);
    // cout << "Matrix m is: " <<endl;m.print();
    // n = Matrix2<double>::ones(5,1);
    // cout << "Matrix n is: " <<endl;n.print();
    // res = Matrix2<double>::dot(m,n);
    // cout << "static dot result is: " <<endl;res.print();
    // m.free(); n.free(); res.free();
    //
    // m = Matrix2<double>::ones(1,5);
    // cout << "Matrix m is: " <<endl;m.print();
    // n = Matrix2<double>::ones(5,5);
    // cout << "Matrix n is: " <<endl;n.print();
    // res = Matrix2<double>::dot(m,n);
    // cout << "static dot result is: " <<endl;res.print();
    // m.free(); n.free(); res.free();
    //
    // m = Matrix2<double>::ones(5,5);
    // cout << "Matrix m is: " <<endl;m.print();
    // n = Matrix2<double>::ones(5,1);
    // cout << "Matrix n is: " <<endl;n.print();
    // res = Matrix2<double>::dot(m,n);
    // cout << "static dot result is: " <<endl;res.print();
    // m.free(); n.free(); res.free();
    //
    // m = Matrix2<double>::ones(5,5);
    // cout << "Matrix m is: " <<endl;m.print();
    // n = Matrix2<double>::ones(5,6);
    // cout << "Matrix n is: " <<endl;n.print();
    // res = Matrix2<double>::dot(m,n);
    // cout << "static dot result is: " <<endl;res.print();
    // m.free(); n.free(); res.free();
    //
    // m = Matrix2<double>::ones(5,1);
    // cout << "Matrix m is: " <<endl;m.print();
    // n = Matrix2<double>::ones(1,6);
    // cout << "Matrix n is: " <<endl;n.print();
    // m.dot(n);
    // cout << "m.dot(n) result is: " <<endl;m.print();
    // m.free(); n.free(); res.free();
    //
    // m = Matrix2<double>::ones(1,5);
    // cout << "Matrix m is: " <<endl;m.print();
    // n = Matrix2<double>::ones(5,3);
    // cout << "Matrix n is: " <<endl;n.print();
    // m.dot(n);
    // cout << "m.dot(n) result is: " <<endl;m.print();
    // m.free(); n.free(); res.free();
    //
    // m = Matrix2<double>::ones(5,5);
    // cout << "Matrix m is: " <<endl;m.print();
    // n = Matrix2<double>::ones(5,1);
    // cout << "Matrix n is: " <<endl;n.print();
    // m.dot(n);
    // cout << "m.dot(n) result is: " <<endl;m.print();
    // m.free(); n.free(); res.free();
    //
    // m = Matrix2<double>::ones(5,5);
    // cout << "Matrix m is: " <<endl;m.print();
    // n = Matrix2<double>::ones(5,6);
    // cout << "Matrix n is: " <<endl;n.print();
    // m.dot(n);
    // cout << "m.dot(n) result is: " <<endl;m.print();
    // m.free(); n.free(); res.free();
    //
    // m = Matrix2<double>::ones(5,5);
    // cout << "Matrix m is: " <<endl;m.print();
    // n = Matrix2<double>::ones(5,6);
    // cout << "Matrix n is: " <<endl;n.print();
    // res = ((m*2.0).dot(n));
    // // res = (2.0*m);
    // m = m * 2.0;
    // cout << "Matrix m*2.dot(n) is: " <<endl;res.print();
    // // cout << "m*2.0 result is: " <<endl;m.print();
    // m.free(); n.free(); res.free();
    //
    // m = Matrix2<double>::ones(5,5);
    // cout << "Matrix m is: " <<endl;m.print();
    // n = Matrix2<double>::ones(5,6);
    // cout << "Matrix n is: " <<endl;n.print();
    // res =  Matrix2<double>::dot(m,n);
    // cout << "dot(m,n) result is: " <<endl;res.print();
    // m.free(); n.free(); res.free();
    //
    // m = Matrix2<double>::ones(5,5);
    // cout << "Matrix m is: " <<endl;m.print();
    // n = Matrix2<double>::ones(5,6)*2;
    // cout << "Matrix n is: " <<endl;n.print();
    // res =  Matrix2<double>::dot(m,n)*2.0;
    // cout << "dot(m,n) result is: " <<endl;res.print();
    // m.free(); n.free(); res.free();
    //
    // m = Matrix2<double>::ones(5,5);
    // cout << "Matrix m is: " <<endl;m.print();
    // n = Matrix2<double>::ones(5,5)*2;
    // cout << "Matrix n is: " <<endl;n.print();
    // res =  m*n;
    // cout << "m*n result is: " <<endl;res.print();
    // m.free(); n.free(); res.free();
    //
    // m = Matrix2<double>::ones(1,5);
    // cout << "Matrix m is: " <<endl;m.print();
    // n = Matrix2<double>::ones(5,5)*2;
    // cout << "Matrix n is: " <<endl;n.print();
    // res =  m*n;
    // cout << "m*n result is: " <<endl;res.print();
    // m.free(); n.free(); res.free();
    //
    // m = Matrix2<double>::ones(5,1);
    // cout << "Matrix m is: " <<endl;m.print();
    // n = Matrix2<double>::ones(5,5)*2;
    // cout << "Matrix n is: " <<endl;n.print();
    // res =  m*n;
    // cout << "m*n result is: " <<endl;res.print();
    // m.free(); n.free(); res.free();
    //
    // m = Matrix2<double>::ones(5,5);
    // cout << "Matrix m is: " <<endl;m.print();
    // n = Matrix2<double>::ones(1,5)*2;
    // cout << "Matrix n is: " <<endl;n.print();
    // res =  m*n;
    // cout << "m*n result is: " <<endl;res.print();
    // m.free(); n.free(); res.free();
    //
    // m = Matrix2<double>::ones(5,5);
    // cout << "Matrix m is: " <<endl;m.print();
    // n = Matrix2<double>::ones(5,5)+2;
    // cout << "Matrix n is: " <<endl;n.print();
    // res =  m+n;
    // cout << "m*n result is: " <<endl;res.print();
    // m.free(); n.free(); res.free();
    //
    // m = Matrix2<double>::ones(1,6);
    // cout << "Matrix m is: " <<endl;m.print();
    // n = Matrix2<double>::ones(4,6)/2;
    // cout << "Matrix n is: " <<endl;n.print();
    // res =  m/n;
    // cout << "m/n result is: " <<endl;res.print();
    // m.free(); n.free(); res.free();
    //
    // m = Matrix2<double>::ones(4,6);
    // cout << "Matrix m is: " <<endl;m.print();
    // n = Matrix2<double>::ones(1,1)*2;
    // cout << "Matrix n is: " <<endl;n.print();
    // res =  m*n;
    // cout << "m*n result is: " <<endl;res.print();
    // m.free(); n.free(); res.free();
    //
    // m = Matrix2<double>::ones(1,1)+3;
    // cout << "Matrix m is: " <<endl;m.print();
    // n = Matrix2<double>::ones(1,1)+2;
    // cout << "Matrix n is: " <<endl;n.print();
    // res =  m+n;
    // cout << "m+n result is: " <<endl;res.print();
    // m.free(); n.free(); res.free();
    //
    // m = Matrix2<double>::ones(4,6)-3;
    // cout << "Matrix m is: " <<endl;m.print();
    // n = Matrix2<double>::ones(4,6)-2;
    // cout << "Matrix n is: " <<endl;n.print();
    // res =  m-n;
    // cout << "m+n result is: " <<endl;res.print();
    // m.free(); n.free(); res.free();
    //
    // m = Matrix2<double>::ones(4,6)-3;
    // cout << "Matrix m is: " <<endl;m.print();
    // n = Matrix2<double>::ones(4,6)-2;
    // cout << "Matrix n is: " <<endl;n.print();
    // res =  2.0*m;
    // cout << "2*m result is: " <<endl;res.print();
    // m.free(); n.free(); res.free();
    //
    // m = Matrix2<double>::ones(4,6)+3;
    // cout << "Matrix m is: " <<endl;m.print();
    // n = Matrix2<double>::ones(4,6)+2;
    // cout << "Matrix n is: " <<endl;n.print();
    // res =  2.0/m;
    // cout << "2/m result is: " <<endl;res.print();
    // m.free(); n.free(); res.free();
    //
    // m = Matrix2<double>::ones(4,6)+3;
    // cout << "Matrix m is: " <<endl;m.print();
    // n = Matrix2<double>::ones(4,6)+2;
    // cout << "Matrix n is: " <<endl;n.print();
    // res =  2.0+m;
    // cout << "2+m result is: " <<endl;res.print();
    // m.free(); n.free(); res.free();
    //
    // m = Matrix2<double>::ones(4,6)+3;
    // cout << "Matrix m is: " <<endl;m.print();
    // n = Matrix2<double>::ones(4,6)+2;
    // cout << "Matrix n is: " <<endl;n.print();
    // res =  2.0-m;
    // cout << "2-m result is: " <<endl;res.print();
    // m.free(); n.free(); res.free();
    //
    // m = Matrix2<double>::ones(4,6)+3;
    // cout << "Matrix m is: " <<endl;m.print();
    // res = m.Trans();
    // cout << "m.Trans() result is: " <<endl;res.print();
    // m.free(); n.free(); res.free();
    //
    // m = Matrix2<double>::ones(4,6)+3;
    // cout << "Matrix m is: " <<endl;m.print();
    // Matrix2<double>::Trans(m);
    // cout << "Matrix2<T>.Trans(m) result is: " <<endl;m.print();
    // m.free(); n.free(); res.free();
    //
    // m = Matrix2<double>::arange(9)+3;
    // cout << "Matrix m is: " <<endl;m.print();
    // Matrix2<double>::Trans(m);
    // cout << "Matrix2<T>.Trans(m) result is: " <<endl;m.print();
    // m.free(); n.free(); res.free();
    //
    // m = Matrix2<double>::arange(9,19);
    // cout << "Matrix m is: " <<endl;m.print();
    // Matrix2<double>::Trans(m);
    // cout << "Matrix2<T>.Trans(m) result is: " <<endl;m.print();
    // m.free(); n.free(); res.free();
    //
    // m = Matrix2<double>::arange(9,19);
    // cout << "Matrix m is: " <<endl;m.print();
    // Matrix2<double>::reshape(m, 2, 5);
    // cout << "Matrix2<T>.reshape(m, n, d) result is: " <<endl;m.print();
    // m.free(); n.free(); res.free();
    //
    // m = Matrix2<double>::arange(9,19);
    // cout << "Matrix m is: " <<endl;m.print();
    // res = m.reshape(2, 5);
    // cout << "m.reshape(n, d) result is: " <<endl;res.print();
    // Matrix2<double>::Trans(res);
    // cout << "Matrix2<T>.Trans(res) result is: " <<endl;res.print();
    // m.free(); n.free(); res.free();
    //
    // m = Matrix2<double>::arange(9);
    // cout << "Matrix m is: " <<endl;m.print();
    // res = m.reshape(3, 3);
    // cout << "m.reshape(n, d) result is: " <<endl;res.print();
    // res = res.Trans();
    // cout << "res.Trans(res) result is: " <<endl;res.print();
    // m.free(); n.free(); res.free();
    //
    // m = Matrix2<double>::arange(9);
    // res = m.reshape(3, 3);
    // cout << "m.reshape(n, d) result is: " <<endl;res.print();
    // res = res.Snrev();
    // cout << "res.Snrev() result is: " <<endl;res.print();
    // m.free(); n.free(); res.free();

    m = Matrix2<double>::arange(9);
    res = m.reshape(3, 3);
    cout << "m.reshape(n, d) result is: " <<endl;res.print();
    Matrix2<double>::Snrev(res);
    cout << "Matrix2::Snrev(res) result is: " <<endl;res.print();
    m.free(); n.free(); res.free();

    m = Matrix2<double>::arange(9);
    res = m.reshape(3, 3);
    cout << "m.reshape(n, d) result is: " <<endl;res.print();
    res = res.exp();
    cout << "res.exp() result is: " <<endl;res.print();
    m.free(); n.free(); res.free();

    float ffff = 3;
    cout<< "exp(fff) is: "<< exp(ffff) << endl;

    m = Matrix2<double>::arange(9);
    res = m.reshape(3, 3);
    cout << "m.reshape(n, d) result is: " <<endl;res.print();
    Matrix2<double>::exp(res);
    cout << "Matrix2::exp(res) result is: " <<endl;res.print();
    m.free(); n.free(); res.free();

    m = Matrix2<double>::arange(9);
    res = m.reshape(3, 3);
    cout << "m.reshape(n, d) result is: " <<endl;res.print();
    res = res.exp();
    cout << "res.exp() result is: " <<endl;res.print();
    m.free(); n.free(); res.free();

    m = Matrix2<double>::arange(9);
    res = m.reshape(3, 3);
    cout << "m.reshape(n, d) result is: " <<endl;res.print();
    Matrix2<double>::log(res);
    cout << "Matrix2::log(res) result is: " <<endl;res.print();
    m.free(); n.free(); res.free();

    m = Matrix2<double>::arange(9);
    res = m.reshape(3, 3);
    cout << "m.reshape(n, d) result is: " <<endl;res.print();
    res = res.log();
    cout << "res.log() result is: " <<endl;res.print();
    m.free(); n.free(); res.free();

    m = Matrix2<double>::arange(9);
    res = m.reshape(3, 3);
    cout << "m.reshape(n, d) result is: " <<endl;res.print();
    Matrix2<double>::log10(res);
    cout << "Matrix2::log10(res) result is: " <<endl;res.print();
    m.free(); n.free(); res.free();

    m = Matrix2<double>::arange(9);
    res = m.reshape(3, 3);
    cout << "m.reshape(n, d) result is: " <<endl;res.print();
    res = res.log10();
    cout << "res.log10() result is: " <<endl;res.print();
    m.free(); n.free(); res.free();

    m = Matrix2<double>::eye(9);
    cout << "Matrix::eye(9) is: " <<endl;m.print();
    m.free(); n.free(); res.free();

    m = Matrix2<double>::arange(9).reshape(3,3);
    cout << "Matrix::arange(9) is: " <<endl;m.print();
    res = m.sum(0);
    cout << "m.sum(0) is: " <<endl;res.print();
    m.free(); n.free(); res.free();

    m = Matrix2<double>::arange(9).reshape(3,3);
    cout << "Matrix::arange(9) is: " <<endl;m.print();
    res = m.sum(1);
    cout << "m.sum(1) is: " <<endl;res.print();
    m.free(); n.free(); res.free();

    m = Matrix2<double>::arange(9).reshape(3,3);
    cout << "Matrix::arange(9) is: " <<endl;m.print();
    double sum_num;
    sum_num = m.sum();
    cout << "m.sum(0) is: " <<sum_num<<endl;
    m.free(); n.free(); res.free();

    m = Matrix2<double>::arange(12).reshape(4,3);
    cout << "Matrix::arange(9) is: " <<endl;m.print();
    res = m.max(0);
    cout << "m.max(0) is: " <<endl;res.print();
    m.free(); n.free(); res.free();
    
    m = Matrix2<double>::arange(12).reshape(4,3);
    cout << "Matrix::arange(12) is: " <<endl;m.print();
    res = m.max(1);
    cout << "m.max(1) is: " <<endl;res.print();
    m.free(); n.free(); res.free();

    m = Matrix2<double>::arange(12).reshape(4,3);
    cout << "Matrix::arange(12) is: " <<endl;m.print();
    double num;
    num = m.max();
    cout << "m.max(1) is: " << num <<endl;
    m.free(); n.free(); res.free();

    double d[4] = {1,2,3,4};
    cout << d[(int)2.0] << endl;

    m = Matrix2<double>::arange(12).reshape(1,12);
    cout << "Matrix::arange(12) is: " <<endl;m.print();
    Ind inds;
    inds = m.argmax(0);
    cout << "m.argmax(0) is: " << endl; inds.print();
    m.free(); n.free(); res.free(); inds.free();

    m = Matrix2<double>::arange(12).reshape(12,1);
    cout << "Matrix::arange(12) is: " <<endl;m.print();
    inds = m.argmax(1);
    cout << "m.argmax(1) is: " << endl; inds.print();
    m.free(); n.free(); res.free(); inds.free();

    m = Matrix2<double>::arange(12).reshape(3,4);
    m(1,1) = 11;
    cout << "Matrix::arange(12) is: " <<endl;m.print();
    inds = m.argmax();
    cout << "m.argmax() is: " << endl; inds.print();
    cout << "m(2,3) is: " << m(2,3) << endl;
    m.free(); n.free(); res.free(); inds.free();

    m = Matrix2<double>::arange(12).reshape(12,1);
    m(1) = 11;
    m(2) = 11;
    cout << "Matrix::arange(12) is: " <<endl;m.print();
    inds = m.argmax();
    cout << "m.argmax() is: " << endl; inds.print();
    cout << "m(2,3) is: " << m(2,3) << endl;
    m.free(); n.free(); res.free(); inds.free();

    m = Matrix2<double>::arange(12).reshape(12,1);
    m(1) = 11;
    m(2) = 11;
    cout << "Matrix::arange(12) is: " <<endl;m.print();
    inds = m.argmax();
    cout << "m.argmax() is: " << endl; inds.print();
    res = m(inds);
    cout << "m(inds) is: " << endl; res.print();
    m.free(); n.free(); res.free(); inds.free();

    m = Matrix2<double>::arange(12).reshape(3,4);
    // m(1) = 11;m(2) = 11;
    cout << "Matrix::arange(12) is: " <<endl;m.print();
    res = m(Ind::slice());
    cout << "m(Ind::slice) is: " << endl; res.print();
    m.free(); n.free(); res.free(); inds.free();
}
