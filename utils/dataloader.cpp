#include<string>
#include<iostream>
#include<vector>
#include<fstream>
#include<algorithm>
#include<utility>
#include<glog/logging.h>

#include"dataloader.h"
#include"Matrix.h"



Dataloader::Dataloader() {

}


Dataloader::Dataloader(const Dataloader& dl) {
    fpth = dl.fpth;
    len = dl.len;
    curr = dl.curr;
    batch_size = dl.batch_size;
    indices = dl.indices;
    fin.open(fpth, std::ios_base::in | std::ios_base::binary);
    CHECK(fin.is_open()) << "File " << fpth << "open failed !!\n";
}


Dataloader::Dataloader(Dataloader&& dl) {
    fin.swap(dl.fin);
    len = dl.len;
    curr = dl.curr;
    batch_size = dl.batch_size;
    std::swap(indices, dl.indices);
    std::swap(dl.fin, fin);
}


Dataloader::Dataloader(std::string db_path) {
    fpth = db_path;
    fin.open(fpth, std::ios_base::in | std::ios_base::binary);
    CHECK(fin.is_open()) << "File " << fpth << "open failed !!\n";

    fin.seekg(0, fin.end);
    len = fin.tellg() / (3073);
    curr = 0;
    batch_size = 0;
    LOG(INFO) << "length of dataset is: " << len << std::endl;
    indices.reserve(len);
    for (long i{0}; i < len ; ++i) indices.push_back(i);
    shuffle();
}


Dataloader::~Dataloader() {
    if (fin.is_open()) fin.close();
}


Dataloader Dataloader::shuffle() {
    std::random_shuffle(indices.begin(), indices.end());
    return *this;
}


Dataloader Dataloader::set_batch_size(int bs) {
    batch_size = bs;
    return *this;
}


Dataloader Dataloader::reset() {
    CHECK(fin.is_open()) << "File " << fpth << "is not opened !!\n";
    fin.seekg(0, fin.end);
    curr = 0;
    return *this;
}


// infinite iterator
std::pair<MATRIX, MATRIX> Dataloader::get_one_batch(int batchsize) {
    using namespace std;

    long offset; 
    vector<char> buf(3073);
    MATRIX mat(batchsize, 3072);
    MATRIX label(batchsize, 1);
    double *lb_ptr{label.data.get()};

    if (curr + batchsize > len) {
        LOG(WARNING) << "One pass data iteration finished, restart dataloader !\n";
        shuffle();
        curr = 0;
    }

    for (int i{0}; i < batchsize; ++i) {
        offset = indices[curr++] * 3073;
        fin.seekg(offset);
        fin.read(&buf[0], 3073);
        lb_ptr[i] = static_cast<double>(static_cast<unsigned char>(buf[0]));

        double *ptr = mat[i];
        for (int j{0}; j < 3072; ++j) {
            ptr[j] = static_cast<double>(static_cast<unsigned char>(buf[j + 1]));
        }
    }

    return make_pair(mat, label);
}


// one pass iterator
std::pair<MATRIX, MATRIX> Dataloader::get_one_batch() {
    using namespace std;

    CHECK_GT(batch_size, 0) << "batch size should not be set <= 0\n";
    CHECK_LT(curr, len) << "data iterations ended but continue works: \n"
        "curr: " << curr << " , len: " << len << endl;

    int batchsize = batch_size;
    if (curr + batchsize > len) {
        batchsize = len - curr;
    }

    long offset; 
    vector<char> buf(3073);
    MATRIX mat(batchsize, 3072);
    MATRIX label(batchsize, 1);
    double *lb_ptr{label.data.get()};

    for (int i{0}; i < batchsize; ++i) {
        offset = indices[curr++] * 3073;
        fin.seekg(offset);
        fin.read(&buf[0], 3073);
        lb_ptr[i] = static_cast<double>(static_cast<unsigned char>(buf[0]));

        double *ptr = mat[i];
        for (int j{0}; j < 3072; ++j) {
            ptr[j] = static_cast<double>(static_cast<unsigned char>(buf[j + 1]));
        }
    }

    return make_pair(mat, label);
}


int Dataloader::get_iter_num(int batchsize) {
    int iter_num;

    iter_num = len / batchsize;
    if (len % batchsize != 0) ++iter_num;

    return iter_num;
}



// uncomment the following line to add the debug code
// #define DATALOADER_DEBUG
#ifdef DATALOADER_DEBUG

#include<opencv2/opencv.hpp>
#include<cmath>

void show_batch(MATRIX&);
cv::Mat get_one_mat(MATRIX&, int);

int main() {
    Dataloader dl("../Data/cifar_dbs/train.db");

    auto batch = dl.get_one_batch(10);
    batch = dl.get_one_batch(64);
    auto img = batch.first;
    auto lb = batch.second;

    show_batch(img);

    return 0;
}


void show_batch(MATRIX& img) {
    using namespace std;
    using namespace cv;

    int row = static_cast<int>(sqrt(img.N));
    int bs = row * row;

    vector<Mat> mats;
    for (int i{0}; i < bs; ++i) {
        mats.push_back(get_one_mat(img, i));
    }

    Mat convas(row << 5, row << 5, CV_64FC3);
    int ind = 0;
    for (int i{0}; i < row; ++i) {
        for (int j{0}; j < row; ++j) {
            auto rect = cv::Rect(i << 5, j << 5, 32, 32);
            auto roi = convas(rect);
            mats[ind++].copyTo(roi);
        }
    }
    imshow("iii2", convas);
    waitKey(0);
}


cv::Mat get_one_mat(MATRIX& m, int row) {
    using namespace std;
    using namespace cv;

    vector<Mat> chs;
    double channel1[1024];
    double channel2[1024];
    double channel3[1024];
    double *p;
    MATRIX mat = m.get_row_mtx(row);

    p = mat.data.get();
    for (int i{0}; i < 1024; ++i) channel1[i] = p[i] / 256;
    chs.emplace_back(cv::Size(32, 32), CV_64FC1, channel1);
    p = mat.data.get() + 1024;
    for (int i{0}; i < 1024; ++i) channel2[i] = p[i] / 256;
    chs.emplace_back(cv::Size(32, 32), CV_64FC1, channel2);
    p = mat.data.get() + 2048;
    for (int i{0}; i < 1024; ++i) channel3[i] = p[i] / 256;
    chs.emplace_back(cv::Size(32, 32), CV_64FC1, channel3);

    Mat im;
    cv::merge(chs, im);

    return im;
}

#endif
