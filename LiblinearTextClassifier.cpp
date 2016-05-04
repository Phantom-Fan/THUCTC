//
// Created by 范子豪 on 16/4/25.
//

#include "LiblinearTextClassifier.h"
#include "TfIdfTermWeighter.h"
#include "liblinear-2.1/linear.h"
#include <iostream>
#include <algorithm>
using namespace std;
using namespace thunlp;

BEGIN_THUNLP_NAMESPACE

    LiblinearTextClassifier::~LiblinearTextClassifier(){
        if (lexicon != nullptr){
            delete lexicon;
        }
        if(trainingVectorBuilder != nullptr) {
            delete trainingVectorBuilder;
        }
        if(testVectorBuilder != nullptr) {
            delete testVectorBuilder;
        }
        if(lmodel != nullptr) {
            delete lmodel;
        }
        if(seg != nullptr) {
            delete seg;
        }
    }

    void LiblinearTextClassifier::clear() {
        lexicon = nullptr;
        trainingVectorBuilder = nullptr;
        testVectorBuilder = nullptr;
        lmodel = nullptr;
        seg = nullptr;
        labelIndex.clear();
    }

    void LiblinearTextClassifier::init( int nclasses, thunlp::WordSegment* seg) {
        lexicon = new Lexicon();
        testVectorBuilder = nullptr;
        //model = null;
        lmodel = nullptr;
        this->nclasses = nclasses;
        ndocs = 0;
        this->seg = seg;
    }

    bool LiblinearTextClassifier::loadModel(const std::string &filename) {
        ifstream lexiconFile;
        ifstream modelFile;
        string lexiconFilePath = filename + "/lexicon";
        string modelFilePath = filename + "/model";
        try{
            lexiconFile.open(lexiconFilePath);
            modelFile.open(modelFilePath);
        } catch (...) {
            cerr << "load Model failed.\n";
            return false;
        }

        try{
            if ( exists_test(lexiconFilePath) ) {
                lexicon->loadFromFile(lexiconFilePath);
                cout << "lexicon exists!\n";
            } else {
                return false;
            }

            if ( exists_test(modelFilePath) ) {
                this->lmodel = load_model(modelFilePath.c_str());
                cout << "model exists!\n";
            } else {
                return false;
            }
        } catch (...) {
            return false;
        }
        lexicon->setLock(true);
        trainingVectorBuilder = nullptr;
        testVectorBuilder = new DocumentVector(lexicon, new TfIdfTermWeighter(lexicon));
        lexiconFile.close();
        modelFile.close();
        return true;
    }

    bool ClassifyResultcmp(const ClassifyResult& a, const ClassifyResult& b) {
            if(a.probability_ > b.probability_ + 1e-20) return true;
            else return false;
    }

    vector<ClassifyResult> LiblinearTextClassifier::classify(const string& text, int topN) {
        vector<string> bigrams = seg->segment(text);
        vector<Lexicon::Word> words = lexicon->convertDocument(bigrams);
        vector<Term> terms = testVectorBuilder->build(words, true);
        int m = terms.size();
        feature_node lx[m + 1];
        for(int j = 0; j < m; ++j) {
            lx[j].index = terms[j].id + 1;
            lx[j].value = terms[j].weight;
        }
        lx[m].index = -1;
        double probs[lmodel->nr_class];
        vector<ClassifyResult> cr;
        predict_probability(lmodel, lx, probs);
        for (int i=0; i < lmodel->nr_class; ++i) {
            cr.push_back(ClassifyResult(i, probs[i]));
        }
        std::sort(cr.begin(), cr.end(), ClassifyResultcmp);
        vector<ClassifyResult> result;
        for (int i = 0; i < topN; ++i) {
            result.push_back(ClassifyResult(cr.at(i).label_, cr.at(i).probability_));
        }
        cr.clear();
        return result;
    }

END_THUNLP_NAMESPACE