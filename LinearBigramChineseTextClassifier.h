//
// Created by 范子豪 on 16/4/27.
//

#ifndef CLASSIFIERLIB_LINEARBIGRAMCHINESETEXTCLASSIFIER_H
#define CLASSIFIERLIB_LINEARBIGRAMCHINESETEXTCLASSIFIER_H
#include "classifier_def.h"
#include "LiblinearTextClassifier.h"
#include "WordSegment.h"
#include "BigramWordSegment.h"
BEGIN_THUNLP_NAMESPACE
class LinearBigramChineseTextClassifier : public thunlp::LiblinearTextClassifier {
protected:
    thunlp::WordSegment* initWordSegment() { return new thunlp::BigramWordSegment(); }
public:
    LinearBigramChineseTextClassifier(int nclasses):thunlp::LiblinearTextClassifier(nclasses, initWordSegment()) {}
    LinearBigramChineseTextClassifier(int nclasses, thunlp::WordSegment* seg):thunlp::LiblinearTextClassifier(nclasses, seg) {}
};
END_THUNLP_NAMESPACE

#endif //CLASSIFIERLIB_LINEARBIGRAMCHINESETEXTCLASSIFIER_H
