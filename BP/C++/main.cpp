
#include"BP.h"
#include<iostream>


using std::cout;
using std::endl;


int main(void)
{
    double r = 8.8;
    int i = r;

    cout << i << " ," << r << 1e-3 << endl;

    // double *data;
    int *id = new int[10];
    delete[] id;
    // *data = static_cast<double>(id[0]);

    // BPnet bp(50,1,10);


    return 0;

}



