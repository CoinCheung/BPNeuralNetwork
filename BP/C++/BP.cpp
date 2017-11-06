#include"BP.h"


BPnet::BPnet(): in_num(0), out_num(0), hlayer_num(0), W(NULL), b(NULL)
{}



BPnet::BPnet(const int in, const int hn, const int on): in_num(in), out_num(on), hlayer_num(hn), W(new Matrix2<double>[hlayer_num+1]), b(new Matrix2<double>[hlayer_num+1])
{

}


// void BPnet::train()
// {
//     double r;
//
// }
