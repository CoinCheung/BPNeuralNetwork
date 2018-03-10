#include<Matrix.h>
#include<numeric.h>
#include"BP.h"
#include"Optimizer.h"
#include"SGD.h"
#include<iostream>
#include<string>
#include<vector>




BPnet trainBP();
void testBP(BPnet);



int main(void)
{
    BPnet net;

    // training
    net = trainBP();

    // test
    testBP(net);

    return 0;
}



BPnet trainBP()
{
    // hidden layer structures, change network stuctures here
    std::vector<int> hidden_nums;
    hidden_nums.reserve(2);
    hidden_nums.push_back(4);
    hidden_nums.push_back(5);
    hidden_nums.push_back(6);

    // optimizer
    SGD_OPT optimizer(new SGD(1e-3, 0.9));
    BPnet net(hidden_nums, "gaussian", optimizer);


    // training 
    MATRIX batch;
    MATRIX label;
    for (int i{0}; i < 10; i++)
    {
        // prepare training data
        batch = MATRIX::arange(12).reshape(4,3);
        label = 2.0*MATRIX::ones(1,4);

        // one training iteration
        net.train(batch, label);
    }

    std::vector<int>().swap(hidden_nums);

    return net;
}



void testBP(BPnet net)
{
    // test data
    MATRIX batch{MATRIX::arange(3,15).reshape(4,3)};
    MATRIX scores;
    MATRIX pred;

    scores = net.forward(batch);
    pred = scores.argmax(1).flatten();

    std::cout << "predicted labels: " << std::endl;
    pred.print();
}

