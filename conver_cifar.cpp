#include<fstream>
#include<string>
#include<sstream>
#include<vector>
// #include<opencv2/opencv.hpp>

#include<iostream>


class File {
    public:
        std::ifstream fin;
        std::string fn;

        File() {}
        File(std::string fpth);
        ~File();

        void set_file(std::string fpth);
        // cv::Mat get_one_img();
        bool peek();

};

File::File(std::string fpth) {
    set_file(fpth);
}


void File::set_file(std::string fpth) {
    if (fin.is_open())  {
        std::cout << "closing previous file: " << fn << std::endl;
        fin.close(); 
    }

    fin.open(fpth, std::ifstream::in);
    fn.assign(fpth);
    // TODO: use glog to check this
    if (!fin.is_open())  {
        std::cout << "file: " << fpth << "open failed !!\n";
        return;
    }
}

File::~File() {
    if (fin.is_open())  {
        std::cout << "closing file: " << fn << std::endl;
        fin.close();
    }
}

// cv::Mat File::get_one_img() {
//     char label;
//     char bytes[3072];
//     if (fin.peek()) {
//         std::cout << "file comes to end, read filed !!\n";
//     } else {
//         fin >> label;
//         fin >> bytes;
//     }
//     std::cout << bytes << std::endl;
//     std::cout << label << std::endl;
//
// }


bool File::peek() {
    return fin.peek();
}


void convert_cifar();


int main() {
    convert_cifar();
    return 0;
}

void convert_cifar() {
    using namespace std;

    string img_dir = "data/cifar_images/";
    string data_bins_dir = "data/cifar-10-batches-bin/";
    vector<string> train_bin_fns;
    string test_bin_fn;
    stringstream ss;

    File fin;

    // for (int i{0}; i < 5; ++i) {
    for (int i{0}; i < 1; ++i) {
        ss.clear();
        ss.str("");
        ss << data_bins_dir << "data_batch_" << i + 1 << ".bin";
        // cout << ss.str() << endl;
        fin.set_file(ss.str());
    }
    
}
