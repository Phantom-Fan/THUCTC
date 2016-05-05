//
// Created by 范子豪 on 16/4/23.
//

#include "BasicTextClassifier.h"
#include <fstream>
#include <iostream>
#include <cstdio>
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
        printf("--------------------------------\nCategory List:\n");
        for (int i = 0; i < categoryList.size(); ++i) {
            categoryToInt.insert(map<string, int>::value_type(categoryList.at(i), i));
            printf("%d\t\t%s\n", i, categoryList.at(i).c_str());
        }
        printf("--------------------------------\n");

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
//gzrd_Lib_CPP_Version_ID--start
#ifndef GZRD_SVN_ATTR
#define GZRD_SVN_ATTR "0"
#endif
static char gzrd_Lib_CPP_Version_ID[] __attribute__((used))="$HeadURL$ $Id$ " GZRD_SVN_ATTR "__file__";
// gzrd_Lib_CPP_Version_ID--end

