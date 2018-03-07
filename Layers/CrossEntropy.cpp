#include"CrossEntropy.h"


CrossEntropy::CrossEntropy()
{

}


MATRIX CrossEntropy::forward(MATRIX& prob, MATRIX& label)
{
    MATRIX one = MATRIX::ones(1,1);
    MATRIX CE = label * (prob + 1e-12).log() + (one - label) * (one - prob + 1e-12).log();

    return CE;
}



MATRIX CrossEntropy::backward(MATRIX& Loss)
{

}
