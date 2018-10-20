#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include<opencv2/opencv.hpp>
#include<utility>

#include<iostream>

// TODO: use args to assign cifar bin directories

class FileIn {
    public:
        std::ifstream fin;
        std::string fn;

        FileIn() {}
        FileIn(std::string fpth);
        ~FileIn();

        void set_file(std::string fpth);
        std::pair<cv::Mat, int> get_one_img();
        int peek();

};

FileIn::FileIn(std::string fpth) {
    set_file(fpth);
}


void FileIn::set_file(std::string fpth) {
    if (fin.is_open())  {
        fin.close(); 
    }

    fin.open(fpth, std::ifstream::in | std::ifstream::binary);
    fn.assign(fpth);
    // TODO: use glog to check this
    if (!fin.is_open())  {
        return;
    }
}

FileIn::~FileIn() {
    if (fin.is_open())  {
        fin.close();
    }
}

std::pair<cv::Mat, int> FileIn::get_one_img() {
    char label;
    char r[1024];
    char g[1024];
    char b[1024];
    std::vector<cv::Mat> channels;

    if (fin.peek() == EOF) {
        // TODO: check here with glog
        std::cout << "file comes to end, read filed !!\n";
    } else {
        fin.read(&label, 1);
        fin.read(r, 1024);
        fin.read(g, 1024);
        fin.read(b, 1024);
        channels.emplace_back(cv::Mat(
                    cv::Size(32, 32),
                    CV_8UC1, 
                    r));
        channels.emplace_back(cv::Mat(
                    cv::Size(32, 32),
                    CV_8UC1, 
                    g));
        channels.emplace_back(cv::Mat(
                    cv::Size(32, 32),
                    CV_8UC1, 
                    b));
        cv::Mat img;
        cv::merge(channels, img);
        return std::make_pair(img, static_cast<int>(label));
    }

}


int FileIn::peek() {
    return fin.peek();
}


void convert_cifar();


int main() {
    convert_cifar();
    return 0;
}

void convert_cifar() {
    using namespace std;

    string train_img_dir = "/home/coin/myprojects/BPNeuralNetwork/data/cifar_images/train/";
    string test_img_dir = "/home/coin/myprojects/BPNeuralNetwork/data/cifar_images/test/";
    string data_bins_dir = "/home/coin/myprojects/BPNeuralNetwork/data/cifar-10-batches-bin/";
    string img_dir;
    stringstream ss;

    FileIn fin;
    string img_name;
    vector<int> lb_nums(10, 0);

    for (int i{0}; i < 6; ++i) {
        ss.clear();
        ss.str("");
        if (i != 5) {
            ss << data_bins_dir << "data_batch_" << i + 1 << ".bin";
            img_dir = train_img_dir;
        } else {
            ss << data_bins_dir << "test_batch.bin";
            img_dir = test_img_dir;
        }
        cout << "Processing: " << ss.str() << endl;
        fin.set_file(ss.str());
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
    }
    cout << "finished" << endl;
}
