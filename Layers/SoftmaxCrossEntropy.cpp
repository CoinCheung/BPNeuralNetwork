#include"SoftmaxCrossEntropy.h"



MATRIX CrossEntropyFunc(MATRIX, MATRIX);
MATRIX SoftmaxFunc(MATRIX scores);


/* class functions */
SoftmaxCrossEntropy::SoftmaxCrossEntropy()
{

}



MATRIX SoftmaxCrossEntropy::forward(MATRIX scores, MATRIX _label)
{
    scores = scores - scores.max(1);
    softmax = SoftmaxFunc(scores);
    label = _label;

    MATRIX Loss{CrossEntropyFunc(softmax, label)};

    return Loss;
}



MATRIX SoftmaxCrossEntropy::backward()
{
    if (softmax.data.get()==nullptr)
    {
        std::cout << "must compute forward path first" << std::endl;
        assert(false);
    }

    MATRIX mat{softmax};
    DataType* mp{mat.data.get()};
    DataType* lp{label.data.get()};
    long num{label.ele_num};
    int ind;
    long linepos{0};

    for (long i{0}; i<num; i++)
    {
        ind = static_cast<int>(lp[i]);
        mp[ind+linepos] -= 1.0;
        linepos += mat.D;
    }

    return mat;
}



/* local functions */
MATRIX CrossEntropyFunc(MATRIX softmax_scores, MATRIX label)
{
    label = label.flatten();
    assert(softmax_scores.N==label.ele_num);

    DataType eps{static_cast<DataType>(1e-12)};
    MATRIX label_one_hot{label.one_hot(1, softmax_scores.D)};
    MATRIX CE = label_one_hot * (softmax_scores + eps).log();
    CE = - CE.sum(1).mean();

    return CE;
}



MATRIX SoftmaxFunc(MATRIX scores)
{
    MATRIX scores_exp{scores.exp()};
    MATRIX scores_exp_sum{scores_exp.sum(1)};
    MATRIX softmaxMat{scores_exp / scores_exp_sum};

    return softmaxMat;
}
