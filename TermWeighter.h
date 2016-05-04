#ifndef CLASSIFIERLIB_TERMWEIGHTER_H
#define CLASSIFIERLIB_TERMWEIGHTER_H
#include "classifier_def.h"
#include "Lexicon.h"
BEGIN_THUNLP_NAMESPACE

    class TermWeighter {
    private:
    protected:
    	thunlp::Lexicon* lexicon;
    public:
    	TermWeighter() {}
    	TermWeighter(thunlp::Lexicon* l) {lexicon = l;}
		virtual ~TermWeighter() {}
    	virtual double weight (int id, double tf, int doclen) = 0;
	};

END_THUNLP_NAMESPACE
#endif //CLASSIFIERLIB_TERMWEIGHTER_H