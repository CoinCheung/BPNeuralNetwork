#include"Matrix/Matrix.h"
#include"BP.h"
#include<iostream>


using std::cout;
using std::endl;



void testMatrix();
void testBP();




int main(void)
{
    double r = 8.8;
    int i = r;

    cout << i << " ," << r << 1e-3 << endl;

    // double *data;
    int *id = new int[10];
    delete[] id;
    // *data = static_cast<double>(id[0]);


    // testMatrix();

    testBP();

    return 0;

}



void testBP()
{
    int in_size = 4;
    int hiden_num = 1;
    int *hiden_size = new int(10);
    int out_size = 3;

    BPnet bp(in_size, hiden_num, hiden_size, out_size, 1e-1);
    // bp.printWb();
    // bp.train();

    // toy training setup
    int num_inputs;
    num_inputs = 5;
    Matrix2<double> X = 10.0 * Matrix2<double>::randn(num_inputs, in_size);
    Matrix2<double> y = Matrix2<double>::zeros(num_inputs,1);
    y(0) = 0;
    y(1) = 1;
    y(2) = 2;
    y(3) = 2;
    y(4) = 1;

    // X.print();y.print();

    // cout << "loss is: " << bp.loss_softmax(X,y,0) << endl;

    bp.train(X, y, X, y, 200, 5e-6, 1e-1, 0.95, 1);



    // Matrix2<double> m = Matrix2<double>::arange(36).reshape(6,6);
    // Matrix2<double> res;
    // m(1,1) = -1;
    // m(3,1) = -1;
    // m(2,1) = -1;
    // m(1,5) = -1;
    //
    // m.print();
    // res = BPnet::activate_relu(m);
    // m.print();
    // cout << "here" <<endl;
    // res.print();
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

    // m = Matrix2<double>::arange(1,41).reshape(8,5);
    // m(2,3) = 0;m(2,4) = 0;m(3,3) = 0;
    // m.print();
    // cout << "m.argmin() is: " << m.argmax() << endl;
    // m.free();

    // m = Matrix2<double>::arange(1,41).reshape(8,5);
    // m(2,3) = 0;m(2,4) = 0;m(3,3) = 0;
    // m.print();
    // m.argmax(1).print();
    // m.free();

    // m = Matrix2<double>::arange(1,41).reshape(8,5);
    // m(0,3) = 110;m(0,4) = 110;m(3,3) = 110;
    // m.print();
    // m.argmax(0).print();
    // m.free();

    // srand(time(NULL));
    // Ind::randchoice(50,41).print();

    // Ind ind(4);
    // ind.data[0] = 2;
    // ind.data[1] = 3;
    // ind.data[2] = 2;
    // ind.data[3] = 7;
    // m = Matrix2<double>::arange(1,41).reshape(8,5);
    // m(0,3) = 110;m(0,4) = 110;m(3,3) = 110;
    // m.print();
    // m(std::slice(-91,3,2)).print();
    // m.free();

    // Ind ind(4);
    // ind.data[0] = 2;
    // ind.data[1] = 3;
    // ind.data[2] = 2;
    // ind.data[3] = 7;
    // m = Matrix2<double>::arange(1,41).reshape(8,5);
    // m(0,3) = 110;m(0,4) = 110;m(3,3) = 110;
    // m.print();
    // m(std::move(ind)).print();
    // m.free();

    // Ind ind(4);
    // ind.data[0] = 2;
    // ind.data[1] = 3;
    // ind.data[2] = 2;
    // ind.data[3] = 7;
    // m = Matrix2<double>::arange(1,41).reshape(8,5);
    // m(0,3) = 110;m(0,4) = 110;m(3,3) = 110;
    // m.print();
    // m(std::slice(-1,2,-3), std::slice(-2,3,-1)).print();
    // m.free();
    
    // Ind ind(4);
    // ind.data[0] = 2;
    // ind.data[1] = 3;
    // ind.data[2] = 2;
    // ind.data[3] = 7;
    // m = Matrix2<double>::arange(1,41).reshape(8,5);
    // m(0,3) = 110;m(0,4) = 110;m(3,3) = 110;
    // m.print();
    // m(ind).print();
    // m.free();

    // Ind ind(4);
    // ind.data[0] = 2;
    // ind.data[1] = 3;
    // ind.data[2] = 2;
    // ind.data[3] = 7;
    // m = Matrix2<double>::arange(1,41).reshape(8,5);
    // m(0,3) = 110;m(0,4) = 110;m(3,3) = 110;
    // m.print();
    // m(ind).print();
    // m.free();

    // Ind inn;
    // inn = Ind::arange(10);
    // inn.print();inn.free();
    // inn = Ind::arange(4,15);
    // inn.print();inn.free();

    // Matrix2<double> mm;
    // mm = 0.5 + Matrix2<double>::arange(16).reshape(4,4);
    // mm.print();
    // mm.toInd().print();

    Matrix2<double> mm;
    Ind ind(4);
    ind.data[0] = 2;
    ind.data[1] = 0;
    ind.data[2] = 3;
    ind.data[3] = 1;
    mm = 0.5 + Matrix2<double>::arange(16).reshape(4,4);
    mm.print();
    mm.toInd().print();
    mm.set(Ind::arange(mm.N), std::move(ind), 1.0);
    mm.print();

    m = mm.copy();
    m.print();
    mm.print();
    m.data[3] = 1000;
    m.print();mm.print();

    
}

