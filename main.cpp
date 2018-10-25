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
void testBP(BPnet&);


int main(void) {
    // set up logger
    google::InitGoogleLogging("BP_Logger");
    google::SetStderrLogging(google::INFO);

    BPnet net;

    // training
    net = trainBP();

    LOG(INFO) << "training done !\n\n\n";

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
    int batch_size = 32;
    Dataloader dl("../data/cifar_dbs/train.db");

    // training 
    int iter_num = 10;
    double loss(0);
    MATRIX img;
    MATRIX label;
    for (int i{0}; i < iter_num; i++) {
        auto batch = dl.get_one_batch(batch_size);
        img = batch.first;
        label = batch.second;

        // one training iteration
        loss = net.train(img, label);
        LOG(INFO) << "iteration: " << iter_num 
            << ", loss: " << loss << std::endl;
    }

    return net;
}



void testBP(BPnet& net) {
    using namespace std;

    // test data
    int batch_size = 32;
    Dataloader dl("../data/cifar_dbs/test.db");
    dl.set_batch_size(32);
    LOG(INFO) << "dataloader initialized \n";

    MATRIX img;
    MATRIX scores;
    MATRIX pred;
    vector<MATRIX> vsc;
    int iter_num = dl.get_iter_num(batch_size);
    LOG(INFO) << "iter number by batch size " << batch_size 
        << ": " << iter_num << std::endl;

    vsc.reserve(iter_num);
    for (int i{0}; i < iter_num; ++i) {
        auto batch = dl.get_one_batch();
        img = batch.first;
        vsc.push_back(net.forward(img));
    }

    scores = MATRIX::tile(vsc);
    pred = scores.argmax(1);
    scores.shape().print();
    pred.shape().print();


}

