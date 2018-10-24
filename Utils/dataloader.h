#ifndef _DATALOADER_H_
#define _DATALOADER_H_
#include<string>
#include<vector>
#include<fstream>
#include<utility>

#include"Matrix.h"


class Dataloader {
    public:
        std::ifstream fin;
        long len;
        long curr;
        std::vector<int> indices;

        Dataloader();
        Dataloader(std::string db_path);
        ~Dataloader();
        void shuffle();
        std::pair<MATRIX, MATRIX> get_one_batch(int batch_size);

};

#endif
