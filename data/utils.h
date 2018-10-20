#ifndef _UTILS_H_
#define _UTILS_H_

#include<fstream>
#include<string>
#include<vector>
#include<opencv2/opencv.hpp>
#include<utility>


class FileIn {
    public:
        std::ifstream fin;
        std::string fn;

        FileIn() {}
        FileIn(std::string fpth);
        ~FileIn();

        void set_file(std::string fpth);
        void restart();
        int get_length();
        std::pair<cv::Mat, int> get_one_img();
        int peek();
        int tellg();
        void seekg(int pos);
        void read(std::vector<char>&, int size);
        // void read(char *, int size);
};


class FileOut {
    public:
        std::ofstream fout;
        std::string fn;

        FileOut() {}
        FileOut(std::string fpth);
        ~FileOut();

        void set_file(std::string fpth);
        void write(std::vector<char>&, int size);
        // void write(char *, int size);
};

#endif
