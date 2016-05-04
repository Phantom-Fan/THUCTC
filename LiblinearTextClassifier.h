//
// Created by 范子豪 on 16/4/25.
//

#ifndef CLASSIFIERLIB_LIBLINEARTEXTCLASSIFIER_H
#define CLASSIFIERLIB_LIBLINEARTEXTCLASSIFIER_H
#include "classifier_def.h"
#include "TextClassifier.h"
#include "liblinear-2.1/linear.h"
#include "WordSegment.h"
#include "Lexicon.h"
#include "DocumentVector.h"
#include <fstream>
#include <vector>
#include <string>
BEGIN_THUNLP_NAMESPACE

    class LiblinearTextClassifier : public thunlp::TextClassifier {
    private:
        thunlp::DocumentVector* trainingVectorBuilder;
        thunlp::DocumentVector* testVectorBuilder;
        thunlp::WordSegment* seg;
        int maxFeatures = 5000;
        int nclasses;
        int longestDoc;
        int ndocs;
        model* lmodel;
    protected:
        virtual thunlp::WordSegment* initWordSegment() { return nullptr; }
    public:
        thunlp::Lexicon* lexicon;
        std::vector<int> labelIndex;
        std::fstream* tsCacheFile = nullptr;
        std::ofstream* tsCache = nullptr;
        LiblinearTextClassifier(){}
        LiblinearTextClassifier(int nclasses){ init(nclasses, initWordSegment()); }
        LiblinearTextClassifier(int nclasses, thunlp::WordSegment* seg) { init(nclasses, seg); }
        virtual ~LiblinearTextClassifier();
        int getLongestDoc() { return longestDoc; }
        void init( int nclasses, thunlp::WordSegment* seg);
        void clear();
        bool loadModel(const std::string& filename);
        thunlp::ClassifyResult classify( const std::string& text );
        std::vector<thunlp::ClassifyResult> classify( const std::string& text, int topN );
        thunlp::Lexicon* getLexicon() { return lexicon; }
    };

END_THUNLP_NAMESPACE

#endif //CLASSIFIERLIB_LIBLINEARTEXTCLASSIFIER_H
