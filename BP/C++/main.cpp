
#include"Matrix.h"
#include"BP.h"
#include<iostream>


using std::cout;
using std::endl;



void testMatrix();




int main(void)
{
    double r = 8.8;
    int i = r;

    cout << i << " ," << r << 1e-3 << endl;

    // double *data;
    int *id = new int[10];
    delete[] id;
    // *data = static_cast<double>(id[0]);

    // BPnet bp(50,1,10);

    testMatrix();

    return 0;

}


void testMatrix()
{
    Matrix2<double> m;
    Matrix2<double> n;
    Matrix2<double> res;

    // m = Matrix2<double>::arange(1,25).reshape(8,3);
    // m.print();
    // m(Ind::slice(0,m.N-1)).print();

    // m = Matrix2<double>::arange(1,41).reshape(8,5);
    // m.print();
    // m(Ind::slice(1,-2,3), Ind::slice(1,-1,2)).print();
    // m.free();
    //
    // m = Matrix2<double>::arange(1,41).reshape(8,5);
    // m.print();
    // m.min(0).print();
    // m.free();
    //
    // m = Matrix2<double>::arange(1,41).reshape(8,5);
    // m.print();
    // m.min(1).print();
    // m.free();

    // m = Matrix2<double>::arange(1,41).reshape(8,5);
    // m.print();
    // cout << "min of m is :" << m.min() << endl;
    // m.free();
    //
    // m = Matrix2<double>::arange(1,41).reshape(8,5);
    // m.print();
    // m.argmin(0).print();
    // m.free();

    m = Matrix2<double>::arange(1,41).reshape(8,5);
    m(2,3) = 1;m(2,4) = 1;m(3,3) = 1;
    m.print();
    m.argmin().print();
    m.free();




}

