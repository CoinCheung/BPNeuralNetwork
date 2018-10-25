#ifndef _DATALOADER_H_
#define _DATALOADER_H_

#include<string>
#include<vector>
#include<fstream>
#include<utility>

#include"Matrix.h"


class Dataloader {
    public:
        std::string fpth;
        std::ifstream fin;
        long len;
        long curr;
        int batch_size;
        std::vector<int> indices;

        Dataloader();
        Dataloader(const Dataloader&);
        Dataloader(Dataloader&&);
        Dataloader(std::string db_path);
        ~Dataloader();
        Dataloader shuffle();
        Dataloader set_batch_size(int batch_size);
        Dataloader reset();
        std::pair<MATRIX, MATRIX> get_one_batch(int batch_size); // infinite iterator
        std::pair<MATRIX, MATRIX> get_one_batch(); // one pass iterator
        int get_iter_num(int batch_size);
};

#endif
