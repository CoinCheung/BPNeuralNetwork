#ifndef _CROSSENTROPYLOSS_H_
#define _CROSSENTROPYLOSS_H_


#include"CrossEntropy.h"
#include"Softmax.h"


CrossEntropyLoss::CrossEntropyLoss()
{

}


MATRIX CrossEntropyLoss::forward(MATRIX softmax_scores, MATRIX label)
{
    label = label.flatten();
    MATRIX label_one_hot = label.one_hot(1, softmax_scores.D);
    MATRIX CE = label_one_hot * (softmax_scores + 1e-12).log();
    CE = - CE.sum(1).mean();

    return CE;
}



MATRIX CrossEntropyLoss::backward(MATRIX Loss)
{

}



#endif
