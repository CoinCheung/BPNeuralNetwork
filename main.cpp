#include<Matrix.hpp>
#include<numeric.h>
#include"BP.h"
#include<iostream>
#include<string>
#include<vector>





void testMatrix();
void testBP();




int main(void)
{
    using namespace std;

    double r = 8.8;
    int i = r;

    cout << i << " ," << r << 1e-3 << endl;

    // double *data;
    int *id = new int[10];
    delete[] id;
    // *data = static_cast<double>(id[0]);


    cout << "here" << endl;
    cout << gaussian_rand() << endl;
    cout << log(exp(1)) << endl;

    testMatrix();

    // testBP();

    return 0;

}



void testBP()
{
    using namespace std;

    vector<int> hidden_nums;

    hidden_nums.reserve(2);
    hidden_nums.push_back(4);
    hidden_nums.push_back(5);

    BPnet net(hidden_nums, "relu", "gaussian");

    // MATRIX in(MATRIX::ones(3,3));
    MATRIX in = MATRIX::arange(12).reshape(4,3);
    MATRIX label = MATRIX::ones(1,4);
    net.train(in, label);

    // auto fl = FullyConnected(new FC_Layer(10, "relu", "gaussian"));
    // FC_Layer fl(10, "relu", "gaussian");
    // cout << "hidden numbers: " << fl.get()->hidden_num << endl;
    // cout << "init_method: " << fl.get()->init_method << endl;

    // MATRIX scores = net.forward(in);
    // scores.print();
    // auto layers = net.layers;
    // net.layers[0]->get_weight().print();


    
    // net.train();
}



// void testBP()
// {
//     int in_size = 4;
//     int hiden_num = 1;
//     int *hiden_size = new int(10);
//     int out_size = 3;
//
//     BPnet bp(in_size, hiden_num, hiden_size, out_size, 1e-1);
//     // bp.printWb();
//     // bp.train();
//
//     // toy training setup
//     int num_inputs;
//     num_inputs = 5;
//     Matrix2<double> X = 10.0 * Matrix2<double>::randn(num_inputs, in_size);
//     Matrix2<double> y = Matrix2<double>::zeros(num_inputs,1);
//     y(0) = 0;
//     y(1) = 1;
//     y(2) = 2;
//     y(3) = 2;
//     y(4) = 1;
//
//     // X.print();y.print();
//
//     // cout << "loss is: " << bp.loss_softmax(X,y,0) << endl;
//
//     // bp.train(X, y, X, y, 200, 5e-6, 1e-1, 0.95, 1);
//     testMatrix();
//
//
//
//     // Matrix2<double> m = Matrix2<double>::arange(36).reshape(6,6);
//     // Matrix2<double> res;
//     // m(1,1) = -1;
//     // m(3,1) = -1;
//     // m(2,1) = -1;
//     // m(1,5) = -1;
//     //
//     // m.print();
//     // res = BPnet::activate_relu(m);
//     // m.print();
//     // cout << "here" <<endl;
//     // res.print();
// }



void testMatrix()
{
    using namespace std;

    // Matrix2<double> m;
    // Matrix2<double> n;
    // Matrix2<double> res;
    //
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

    // Matrix2<double> mm;
    // Ind ind(4);
    // ind.data[0] = 2;
    // ind.data[1] = 0;
    // ind.data[2] = 3;
    // ind.data[3] = 1;
    // mm = 0.5 + Matrix2<double>::arange(16).reshape(4,4);
    // mm.print();
    // mm.toInd().print();
    // mm.set(Ind::arange(mm.N), std::move(ind), 1.0);
    // mm.print();
    //
    // m = mm.copy();
    // m.print();
    // mm.print();
    // m.data[3] = 1000;
    // m.print();mm.print();
    //
    // MATRIX mm1 = MATRIX::arange(20).reshape(4,5);
    // mm1.print();
    // MATRIX mm2 = MATRIX::arange(30).reshape(5,6);
    // mm2.print();
    // MATRIX md = MATRIX::arange(0);
    // md.print();
    // cout << md.data.get() << endl;
    // cout << "dot multiplication" << endl;
    // MATRIX mm = mm1.dot(mm2);
    // mm.print();

    // MATRIX mm1 = MATRIX::arange(1,21).reshape(4,5);
    // mm1.print();
    // MATRIX mm2 = MATRIX::arange(2,22).reshape(4,5);
    // mm2.print();
    // MATRIX mm = mm1/mm2;
    // mm.print();

    // MATRIX mm1 = MATRIX::arange(1,21).reshape(4,5);
    // mm1.print();
    // MATRIX mm2 = MATRIX::arange(2,7);
    // mm2.print();
    // MATRIX mm = mm2/mm1;
    // mm.print();


    // unsigned int f;
    // f = -1;
    // cout << f << endl;
    //
    // MATRIX mm1 = MATRIX::arange(1,25).reshape(4,6);
    // cout << mm1.data.get() << endl;
    // mm1.print();
    // MATRIX mm2 = mm1.copy();
    // mm2.print();
    // mm2 = mm1.exp();
    // mm2.print();
    // mm1.print();
    //
    // mm2 = mm1.sum(1);
    // mm2.print();

    // cout << 1e-10*2 << endl;
    //
    // MATRIX mm1 = MATRIX::arange(1,25).reshape(4,6);
    // mm1.print();
    // MATRIX mm2 = mm1 + 1.0;
    // mm2.print();
    //
    // MATRIX mm3 = 1.0 - mm1;
    // mm3.print();

    // MATRIX mm1 = MATRIX::arange(1,25).reshape(1,24);
    // MATRIX mm2 = MATRIX::arange(2,26).reshape(24,1);
    //
    // MATRIX mm3 = mm1 * mm2.flatten();
    // // MATRIX mm3 = mm1 * mm2;
    // mm3.print();
    //
    // MATRIX mm1 = MATRIX::arange(1,25).reshape(4,6);
    // mm1.print();
    // mm1.argmax(1).print();
    //
    // MATRIX mm2(0,3);
    // mm2.print();
    //
    // mm1 = MATRIX::arange(1,5);
    // mm1.print();
    // mm2 = (2.0*mm1.flatten()).one_hot(1,5);
    // mm2.print();

    MATRIX mm1 = MATRIX::arange(1,25).reshape(4,6);
    mm1.print();
    mm1.transpose().print();
}




