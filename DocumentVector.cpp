#include "DocumentVector.h"
#include "Lexicon.h"
#include <iostream>
using namespace std;
using namespace thunlp;

BEGIN_THUNLP_NAMESPACE

	DocumentVector::DocumentVector(thunlp::Lexicon* l) {
		weighter = new TfIdfTermWeighter(l);
	}

    DocumentVector::DocumentVector(thunlp::Lexicon* l, thunlp::TermWeighter* w) {
    	weighter = w;
    }

    DocumentVector::~DocumentVector() {
		if (weighter != nullptr)
    	    delete weighter;
    }

	std::vector<thunlp::Term> DocumentVector::build(std::vector<thunlp::Lexicon::Word> doc, bool normalized) {
        std::map<int, Term> terms;
		terms.clear();
		for(int i = 0; i < doc.size(); i++) {
			map<int, Term>::iterator target = terms.find(doc[i].id);
			if(target == terms.end()) {
				Term t;
				t.id = doc[i].id;
				t.weight = 1;
				terms.insert(make_pair(t.id, t));
			}
			else {
				target->second.weight ++;
			}
		}

		std::vector<thunlp::Term> vec(terms.size());
		double normalizer = 0;
		int i = 0;
		for(map<int, Term>::iterator target = terms.begin(); target != terms.end(); target ++) {
			vec[i] = target->second;
			vec[i].weight = weighter->weight(vec[i].id, vec[i].weight, doc.size());
			normalizer += vec[i].weight * vec[i].weight;
			i++;
		}
		if (normalized) { 
			normalizer = sqrt(normalizer);
			for(int i = 0; i < terms.size(); i++) {
				vec[i].weight /= normalizer;
			}
		}
		
		sort(vec.begin(), vec.end(), Term::TermIdComparator);
		
		return vec;
	}

	double DocumentVector::dotProduct(const std::vector<thunlp::Term>& v1, const std::vector<thunlp::Term>& v2) {
		int p1 = 0, p2 = 0;
		double product = 0.0;
		while (p1 < v1.size() && p2 < v2.size()) {
			if (v1[p1].id < v2[p2].id) {
				p1++;
			} else if (v2[p2].id < v1[p1].id) {
				p2++;
			} else {
				product += v1[p1].weight * v2[p2].weight;
				p1++;
				p2++;
			}
		}
		return product;
	}
	
END_THUNLP_NAMESPACE