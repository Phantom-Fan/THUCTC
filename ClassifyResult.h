//
// Created by 范子豪 on 16/4/23.
//

#ifndef CLASSIFIERLIB_CLASSIFYRESULT_H
#define CLASSIFIERLIB_CLASSIFYRESULT_H
#include <string>
#include "classifier_def.h"
BEGIN_THUNLP_NAMESPACE

    class ClassifyResult {
    public:
        int label_; //分类标签编号
        double probability_; //分类概率
        ClassifyResult(int label, double prob) : label_(label), probability_(prob) {}
        ~ClassifyResult(){}
        std::string toString() { return std::to_string(label_) + "\t" + std::to_string(probability_); }
    };

END_THUNLP_NAMESPACE
#endif //CLASSIFIERLIB_CLASSIFYRESULT_H
