#ifndef CLASSIFIERLIB_TERM_H
#define CLASSIFIERLIB_TERM_H
#include "classifier_def.h"
#include <map>
#include <string>
#include <vector>
BEGIN_THUNLP_NAMESPACE

	class Term {
	public:
		int id;
		double weight;
		int label;

		Term() {
			id = 0;
			weight = 0;
			label = 0;
		}

		static bool TermIdComparator(const Term &a,const Term &b) {
			return a.id > b.id ? false : true;
		}

		static bool TermWeightComparator(const Term &a,const Term &b) {
			return a.weight > b.weight;
		}
	};

END_THUNLP_NAMESPACE
#endif //CLASSIFIERLIB_TERM_H
