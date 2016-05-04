//
// Created by 范子豪 on 16/4/27.
//

#ifndef CLASSIFIERLIB_BIGRAMWORDSEGMENT_H
#define CLASSIFIERLIB_BIGRAMWORDSEGMENT_H
#include "classifier_def.h"
#include "WordSegment.h"
#include <vector>
#include <string>
BEGIN_THUNLP_NAMESPACE

    class BigramWordSegment : public WordSegment {
    private:
        std::vector<std::wstring> segs;
    public:
        BigramWordSegment() {}
        ~BigramWordSegment(){ segs.clear(); }
        bool outputPosTag() { return false; }
        std::vector<std::string> segment(const std::string& text);
    };

END_THUNLP_NAMESPACE

#endif //CLASSIFIERLIB_BIGRAMWORDSEGMENT_H
