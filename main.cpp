#include<iostream>
#include<string>
#include<vector>
#include<utility>

#include"Matrix.h"
#include"numeric.h"
#include"BP.h"
#include"Optimizer.h"
#include"SGD.h"
#include"dataloader.h"
#include<glog/logging.h>


BPnet trainBP();
void testBP(BPnet);



int main(void) {
    BPnet net;

    // training
    net = trainBP();

    std::cout << "training done !\n";
    CHECK(false) << "error !\n";

    // test
    testBP(net);

    return 0;
}



BPnet trainBP() {
    using namespace std;
    // hidden layer structures, change network stuctures here
    vector<int> hidden_nums;
    hidden_nums.reserve(3);
    hidden_nums.push_back(4);
    hidden_nums.push_back(5);
    hidden_nums.push_back(10);

    // optimizer
    SGD_OPT optimizer{std::make_shared<SGD>(1e-3, 0.9)};
    BPnet net(hidden_nums, "gaussian", optimizer);

    // dataloader
    Dataloader dl("../data/cifar_dbs/train.db");


    // training 
    int iter_num = 10;
    int batch_size = 32;
    MATRIX batch;
    MATRIX label;
    for (int i{0}; i < iter_num; i++) {
        auto batch = dl.get_one_batch(batch_size);
        auto img = batch.first;
        auto label = batch.second;

        // one training iteration
        net.train(img, label);
    }



    return net;
}



void testBP(BPnet net) {
    // test data
    MATRIX batch{MATRIX::arange(3,15).reshape(4,3)};
    MATRIX scores;
    MATRIX pred;

    scores = net.forward(batch);
    pred = scores.argmax(1).flatten();

    std::cout << "predicted labels: " << std::endl;
    pred.print();
}

