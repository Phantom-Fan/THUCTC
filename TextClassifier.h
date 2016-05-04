//
// Created by 范子豪 on 16/4/23.
//

#ifndef CLASSIFIERLIB_TEXTCLASSIFIER_H
#define CLASSIFIERLIB_TEXTCLASSIFIER_H
#include "classifier_def.h"
#include "ClassifyResult.h"
#include "Lexicon.h"
#include <string>
#include <vector>
BEGIN_THUNLP_NAMESPACE

    class TextClassifier {
    public:
        TextClassifier(){}
        virtual ~TextClassifier(){}
    //    virtual bool addTrainingText(const std::string text, int label) = 0;
    //    virtual bool train() = 0;
    //    virtual bool saveModel(const std::string& filename) = 0;
        virtual bool loadModel(const std::string& filename) = 0;
    //    virtual ClassifyResult classify(const std::string& text) = 0;
        virtual std::vector<thunlp::ClassifyResult> classify(const std::string&, int topN) = 0;
    //    virtual std::string saveToString() = 0;
    //    virtual void loadFromString(const std::string& model) = 0;
    //    virtual void setMaxFeatures(int maxFeatures) = 0;
        virtual thunlp::Lexicon* getLexicon() = 0;
    };

END_THUNLP_NAMESPACE

#endif //CLASSIFIERLIB_TEXTCLASSIFIER_H
