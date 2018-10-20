#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include<opencv2/opencv.hpp>
#include<utility>
#include<iostream>

#include"utils.h"

// TODO: use args to assign cifar bin directories
// 1. clear() before seekg
// istreambuf_iter<char>


void convert_cifar();
void concat_file(FileIn&, FileOut&);



int main() {
    convert_cifar();
    return 0;
}


void convert_cifar() {
    using namespace std;

    string train_img_dir = "/home/coin/myprojects/BPNeuralNetwork/data/cifar_images/train/";
    string test_img_dir = "/home/coin/myprojects/BPNeuralNetwork/data/cifar_images/test/";
    string data_bins_dir = "/home/coin/myprojects/BPNeuralNetwork/data/cifar-10-batches-bin/";
    string db_dir = "/home/coin/myprojects/BPNeuralNetwork/data/cifar_dbs/";
    string img_dir;
    stringstream ss;

    FileIn fin;
    FileOut fout;
    vector<int> lb_nums(10, 0);
    
    // prepare for fout
    ss.str("");
    ss.clear();
    ss << db_dir << "/train.db";
    fout.set_file(ss.str());

    for (int i{0}; i < 6; ++i) {
        ss.clear();
        ss.str("");
        if (i != 5) {
            ss << data_bins_dir << "data_batch_" << i + 1 << ".bin";
            fin.set_file(ss.str());
            img_dir = train_img_dir;
        } else {
            ss << db_dir << "/test.db";
            fout.set_file(ss.str());
            ss.str("");
            ss.clear();
            ss << data_bins_dir << "test_batch.bin";
            fin.set_file(ss.str());
            img_dir = test_img_dir;
        }

        // decompress each images
        cout << "Processing: " << fin.fn << endl;
        while (fin.peek() != EOF) {
            auto one_pair = fin.get_one_img();
            auto img = one_pair.first;
            auto lb = one_pair.second;
            ss.clear();
            ss.str("");
            ss << img_dir << "/" << lb << "_" << lb_nums[lb] << ".jpg";
            lb_nums[lb] += 1;
            cv::imwrite(ss.str(), img);
        }
        
        // concat each bin to a whole one
        concat_file(fin, fout);
    }
    cout << "finished" << endl;
}


void concat_file(FileIn& fin, FileOut& fout) {
    int fin_pos = fin.tellg();
    int len = fin.get_length();
    int buf_size{4096};
    std::vector<char> buf(buf_size);
    // char buf[4096];

    fin.restart();
    while (fin.peek() != EOF) {
        if (len >= buf_size) {
            len -= buf_size;
            fin.read(buf, buf_size);
            fout.write(buf, buf_size);
        } else {
            fin.read(buf, len);
            fout.write(buf, len);
        }
    }

    fin.seekg(fin_pos);
}
