#ifndef CLASSIFIERLIB_TFONLYTERMWEIGHTER_H
#define CLASSIFIERLIB_TFONLYTERMWEIGHTER_H
#include "TermWeighter.h"
BEGIN_THUNLP_NAMESPACE

    class TfOnlyTermWeighter:public thunlp::TermWeighter {
    private:
    protected:
    public:
    	TfOnlyTermWeighter() {}
    	virtual double weight (int id, double tf, int doclen) {
    		return tf;
    	}
	};

END_THUNLP_NAMESPACE
#endif //CLASSIFIERLIB_TFONLYTERMWEIGHTER_H