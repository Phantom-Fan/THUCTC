//
// Created by 范子豪 on 16/4/23.
//
//TODO 只实现了分类阶段需要做的函数

#ifndef CLASSIFIERLIB_BASICTEXTCLASSIFIER_H
#define CLASSIFIERLIB_BASICTEXTCLASSIFIER_H
#include "classifier_def.h"
#include "ClassifyResult.h"
#include "TextClassifier.h"
#include <string>
#include <vector>
#include <map>
BEGIN_THUNLP_NAMESPACE

    class BasicTextClassifier {
    private:
    protected:
        thunlp::TextClassifier* classifier = nullptr;
        std::vector<std::string> categoryList;
        std::map<std::string, int> categoryToInt;
    public:
        BasicTextClassifier(){ categoryList.clear(); categoryToInt.clear(); }
        virtual ~BasicTextClassifier(){ if (classifier != nullptr) delete classifier; }

        bool loadCategoryListFromFile(const std::string& filePath);
        std::vector<thunlp::ClassifyResult> classifyText(const std::string& text, int topN);
        void setTextClassifier(thunlp::TextClassifier* tc) { classifier = tc; }
        thunlp::TextClassifier* getTextClassifier() { return classifier; }
        std::string getCategoryName (int id) { return categoryList.at(id); }
        int getCategorySize () { return categoryList.size(); }
    };

END_THUNLP_NAMESPACE

#endif //CLASSIFIERLIB_BASICTEXTCLASSIFIER_H
