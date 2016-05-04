//
// Created by 范子豪 on 16/4/25.
//

#ifndef CLASSIFIERLIB_WORDSEGMENT_H
#define CLASSIFIERLIB_WORDSEGMENT_H
#include "classifier_def.h"
#include <string>
#include <vector>
BEGIN_THUNLP_NAMESPACE

    class WordSegment{
    public:
    	WordSegment(){}
        virtual ~WordSegment(){}
        virtual bool outputPosTag() = 0;
        virtual std::vector<std::string> segment(const std::string& text) = 0;
    };

END_THUNLP_NAMESPACE
#endif //CLASSIFIERLIB_WORDSEGMENT_H
