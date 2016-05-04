#ifndef CLASSIFIERLIB_DOCUMENTVECTOR_H
#define CLASSIFIERLIB_DOCUMENTVECTOR_H
#include "classifier_def.h"
#include "TermWeighter.h"
#include "TfIdfTermWeighter.h"
#include "Term.h"
#include <map>
#include <set>
#include <string>
#include <vector>
#include <fstream>
BEGIN_THUNLP_NAMESPACE

    class DocumentVector {
    private:
    	thunlp::TermWeighter* weighter = nullptr;
    protected:
    public:
    	DocumentVector(thunlp::Lexicon* l);
    	DocumentVector(thunlp::Lexicon* l, thunlp::TermWeighter* w);
        ~DocumentVector();
        std::vector<thunlp::Term> build(std::vector<thunlp::Lexicon::Word> doc, bool normalized);
        double dotProduct(const std::vector<thunlp::Term>& v1, const std::vector<thunlp::Term>& v2 );
	};

END_THUNLP_NAMESPACE
#endif //CLASSIFIERLIB_DOCUMENTVECTOR_H
