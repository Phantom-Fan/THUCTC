#ifndef CLASSIFIERLIB_TFIDFTERMWEIGHTER_H
#define CLASSIFIERLIB_TFIDFTERMWEIGHTER_H
#include "TermWeighter.h"
#include "math.h"
BEGIN_THUNLP_NAMESPACE
    class TfIdfTermWeighter:public thunlp::TermWeighter {
    private:
    protected:
    public:
    	TfIdfTermWeighter(thunlp::Lexicon* l):TermWeighter(l) {}
    	virtual double weight (int id, double tf, int doclen) {
    		int n = lexicon->getNumDocs();
			thunlp::Lexicon::Word w = lexicon->getWord(id);
			return log10(tf + 1) * (log10((double) n / w.df + 1 ));
    	}
	};
END_THUNLP_NAMESPACE
#endif //CLASSIFIERLIB_TFIDFTERMWEIGHTER_H