#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include<opencv2/opencv.hpp>
#include<utility>
#include<iostream>

#include"utils.h"



//// member functions of FileIn class
FileIn::FileIn(std::string fpth) {
    set_file(fpth);
}


FileIn::~FileIn() {
    if (fin.is_open()) {
        fin.close();
    }
}


void FileIn::set_file(std::string fpth) {
    if (fin.is_open()) {
        fin.close(); 
    }

    fin.open(fpth, std::ios_base::in | std::ios_base::binary);
    fn.assign(fpth);
    // TODO: use glog to check this
    if (!fin.is_open()) {
        std::cout << "file: \"" << fn << "\" open failed !!\n";
        return;
    }
}


void FileIn::restart() {
    fin.clear();
    fin.seekg(0, fin.beg);
}


int FileIn::get_length() {
    int pos = fin.tellg();
    fin.clear();
    fin.seekg(0, fin.end);
    int len = fin.tellg();
    fin.clear();
    fin.seekg(pos);

    return len;
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
        channels.emplace_back(
                    cv::Size(32, 32),
                    CV_8UC1, 
                    r);
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


int FileIn::tellg() {
    return fin.tellg();
}


void FileIn::seekg(int pos) {
    fin.clear();
    fin.seekg(pos);
}


void FileIn::read(std::vector<char>& buf, int size) {
    fin.read(&buf[0], size);
}


//// member functions of FileOut class
FileOut::FileOut(std::string fpth) {
    set_file(fpth);
}


FileOut::~FileOut() {
    if (fout.is_open()) {
        fout.close();
    }
}


void FileOut::set_file(std::string fpth) {
    if (fout.is_open()) {
        fout.close();
    }

    fout.open(fpth, std::ios_base::out | std::ios_base::binary);
    fn.assign(fpth);

    // TODO: use glog to check this
    if (!fout.is_open()) {
        std::cout << "file: \"" << fn << "\" open failed !!\n";
        return;
    }
}


void FileOut::write(std::vector<char>& buf, int size) {
    fout.write(&buf[0], size);
}
