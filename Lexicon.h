//
// Created by 范子豪 on 16/4/25.
//

#ifndef CLASSIFIERLIB_LEXICON_H
#define CLASSIFIERLIB_LEXICON_H
#include "classifier_def.h"
#include <map>
#include <set>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>
BEGIN_THUNLP_NAMESPACE
    static std::string COLON_REPLACER = "~CLN~";
    class Lexicon {
    public:
        //WORD
        class Word {
        public:
            int id;
            std::string name;
            int tf;
            int df;
            Word() {}
            Word(int id, std::string name) {
                this->id = id;
                this->name = name;
            }
            Word clone();
        public:
            std::string toString();
            int getId() { return id; }
            std::string& getName() { return name; }
            int getFrequency() { return tf; }
            int getDocumentFrequency() { return df; }
            bool equals(Word& other);
            //static void substrReplace(std::string& str, const std::string& from, const std::string& to);
        };
        Lexicon();
        Lexicon(std::string& f);
        void setLock(bool locked) { this->locked = locked; }
        bool getLock() { return this->locked; }
        Lexicon::Word getWord(int id) { return idHash.find(id)->second; }
        Lexicon::Word getWord(const std::string& name) { return nameHash.find(name)->second; }
        void addDocument(std::vector<std::string>& doc);
        std::vector<Lexicon::Word> convertDocument(std::vector<std::string>& doc);
        int getSize() { return idHash.size(); }
        long long getNumDocs() { return numDocs; }
        bool loadFromInputStream(std::ifstream& input);
        bool loadFromFile(const std::string& filename);
        Lexicon map(std::map<int, int>& translation);
        Lexicon removeLowDfWords(int minDf);
    private:
    protected:
        std::map<int, Lexicon::Word> idHash;
        std::map<std::string, Lexicon::Word> nameHash;
        std::set<int> termSet;
        bool locked;
        long long numDocs;
        Lexicon::Word* buildWord (const std::string& termString);
    };
END_THUNLP_NAMESPACE
#endif //CLASSIFIERLIB_LEXICON_H
