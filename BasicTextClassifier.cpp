//
// Created by 范子豪 on 16/4/23.
//

#include "BasicTextClassifier.h"
#include <fstream>
#include <iostream>
using namespace thunlp;
using namespace std;

BEGIN_THUNLP_NAMESPACE

    bool BasicTextClassifier::loadCategoryListFromFile(const std::string &filePath) {
        ifstream fin;
        try{
            if (!exists_test(filePath)) {
                cerr << "load categoryListFromFile failed.\n";
                return false;
            }
            fin.open(filePath);
        } catch(...) {
            cerr << "load categoryListFromFile failed.\n";
        }

        categoryList.clear();
        string s;
        try {
            while(getline(fin, s)){
                categoryList.push_back(s);
            }
        } catch(...) {
            cerr << "load categoryListFromFile failed.\n";
            return false;
        }

        categoryToInt.clear();
        cout << "--------------------------------\nCategory List:\n";
        for (int i = 0; i < categoryList.size(); ++i) {
            categoryToInt.insert(map<string, int>::value_type(categoryList.at(i), i));
            cout << i << "\t\t" << categoryList.at(i) << endl;
        }
        cout << "--------------------------------\n";

        fin.close();
        return true;
    }

    vector<ClassifyResult> BasicTextClassifier::classifyText(const std::string &text, int topN) {
        if (topN > categoryList.size()) {
            topN = categoryList.size();
        }
        return classifier->classify(text, topN);
    }

END_THUNLP_NAMESPACE