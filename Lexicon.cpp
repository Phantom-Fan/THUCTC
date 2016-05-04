//
// Created by 范子豪 on 16/4/25.
//

#include "Lexicon.h"
#include <iostream>
using namespace std;
using namespace thunlp;

BEGIN_THUNLP_NAMESPACE

    void substrReplace(string& str, const string& from, const string& to){
        if(from.empty())
            return;
        size_t start_pos = 0;
        while((start_pos = str.find(from, start_pos)) != std::string::npos) {
            str.replace(start_pos, from.length(), to);
            start_pos += to.length();
        }
    }

    bool Lexicon::Word::equals(Lexicon::Word &other) {
        if (other.name != this->name)
            return false;
        if (other.id != this-> id)
            return false;
        return true;
    }

    Lexicon::Word Lexicon::Word::clone(){
        Lexicon::Word t;
        t.name = name;
        t.id = id;
        t.tf = tf;
        t.df = df;
        return t;
    }

    std::string Lexicon::Word::toString() {
        string temp(name);
        substrReplace(temp, ":", COLON_REPLACER);
        return to_string(id) + ":" + temp + ":" + to_string(tf) + ":" + to_string(df);
    }

    Lexicon::Lexicon() {
        idHash.clear();
        nameHash.clear();
        termSet.clear();
        locked = false;
        numDocs = 0;
    }

    Lexicon::Lexicon(std::string& f) {
        idHash.clear();
        nameHash.clear();
        termSet.clear();
        locked = false;
        numDocs = 0;
        loadFromFile(f);
    }

    void Lexicon::addDocument(std::vector<string> &doc) {
        termSet.clear();
        for(int i = 0; i < doc.size(); i++){
            std::map<std::string, Lexicon::Word>::iterator target = nameHash.find(doc[i]);
            Lexicon::Word t;
            if(target == nameHash.end()) {
                if(locked) {
                    continue;
                }
                t.name = doc[i];
                t.tf = 0;
                t.df = 0;
                t.id = nameHash.size();
                nameHash.insert(make_pair(doc[i], t));
                idHash.insert(make_pair(t.id, t));
            }
            target = nameHash.find(doc[i]);
            target->second.tf += 1;
            if (termSet.find(target->second.id) == termSet.end()) {
                termSet.insert(target->second.id);
                target->second.df += 1;
            }
        }
        numDocs++;
    }

    vector<Lexicon::Word> Lexicon::convertDocument(std::vector<std::string> &doc) {
        vector<Lexicon::Word> terms(doc.size());
        int n = 0;
        for (int i = 0; i < doc.size(); ++i) {
            string token = doc[i];
            Lexicon::Word t;
            std::map<std::string, Lexicon::Word>::iterator target = nameHash.find(token);
            if (target == nameHash.end()) {
                if (locked){
                    continue;
                }
                t.name = token;
                t.tf = 1;
                t.df = 1;
                t.id = nameHash.size();
                nameHash.insert(make_pair(t.name, t));
                idHash.insert(make_pair(t.id, t));
            } else {
                t = target->second;
            }
            terms[n++] = t;
        }
        if (n < doc.size()) {
            vector<Lexicon::Word> finalterms(n);
            for (int i = 0; i < n; ++i) {
                finalterms[i] = terms[i];
            }
            terms = finalterms;
        }
        return terms;
    }

    bool Lexicon::loadFromFile(const std::string& filename) {
        if (exists_test(filename)){
            cout << filename << endl;
            ifstream fin(filename);
            return loadFromInputStream(fin);
        } else {
            cerr << "File not found in Lexicon::loadFromFile\n";
            return false;
        }
    }

    bool Lexicon::loadFromInputStream(std::ifstream &input) {
        nameHash.clear();
        idHash.clear();
        try {
            string termString;
            getline(input, termString);
            numDocs = atoi(termString.c_str());
            cout << numDocs << " documents in total.\n";
            while (getline(input, termString)) {
                Lexicon::Word* t = buildWord(termString);
                if (t != nullptr) {
                    nameHash.insert(make_pair(t->name, *t));
                    idHash.insert(make_pair(t->id, *t));
                    delete t;
                }
            }
            input.close();
        } catch (...) {
            cerr << "File stream read failed in Lexicon::loadFromFileStream.\n";
            return false;
        }
        return true;
    }

    void SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c) {
        std::string::size_type pos1, pos2;
        pos2 = s.find(c);
        pos1 = 0;
        while(std::string::npos != pos2) {
            v.push_back(s.substr(pos1, pos2-pos1));
            pos1 = pos2 + c.size();
            pos2 = s.find(c, pos1);
        }
        if(pos1 != s.length())
            v.push_back(s.substr(pos1));
    }

    //Memory leak
    Lexicon::Word* Lexicon::buildWord(const std::string &termString) {
        Lexicon::Word* t = nullptr;
        vector<string> parts;
        SplitString(termString, parts, ":");
        if (parts.size() == 4) {
            t = new Lexicon::Word();
            t->id = atoi(parts[0].c_str());
            string temp(parts[1]);
            substrReplace(temp, COLON_REPLACER, ":");
            t->name = temp;
            t->tf = atoi(parts[2].c_str());
            t->df = atoi(parts[3].c_str());
        }
        return t;
    }

    Lexicon Lexicon::map(std::map<int, int>& translation) {
        Lexicon newlex;
        std::map<int, Lexicon::Word> newIdHash;
        std::map<std::string, Lexicon::Word> newNameHash;
        for (std::map<int, int>::iterator it = translation.begin(); it != translation.end(); ++it) {
            Lexicon::Word w = idHash.find(it->first)->second;
            Lexicon::Word nw = w.clone();
            nw.id = it->second;
            newIdHash.insert(std::make_pair(nw.id, nw));
            newNameHash.insert(std::make_pair(nw.getName(), nw));
        }
        newlex.idHash = newIdHash;
        newlex.nameHash = newNameHash;
        newlex.numDocs = this->numDocs;
        return newlex;
    }

    Lexicon Lexicon::removeLowDfWords(int minDf) {
        int id = 0;
        std::map<int, int> translation;
        for (std::map<int, Lexicon::Word>::iterator it = idHash.begin(); it != idHash.end(); ++it) {
            Lexicon::Word w = it->second;
            if (w.df < minDf) {
                continue;
            }
            translation.insert(std::make_pair(w.id, id));
            ++id;
        }
        return map(translation);
    }

END_THUNLP_NAMESPACE
