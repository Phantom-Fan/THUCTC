//
// Created by 范子豪 on 16/4/27.
//

#include "BigramWordSegment.h"
#include "LangUtils.h"
#include <locale>
//#include <codecvt>
#include "utf8.h"
#include <iostream>
using namespace std;
using namespace thunlp;
//std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
BEGIN_THUNLP_NAMESPACE

    std::vector<std::string> thunlp::BigramWordSegment::segment(const std::string &text) {
        std::vector<std::wstring> segs;
        int start = 0, end = 0;
        segs.clear();
        bool precedentByChinese = false;
//        wstring wtext = converter.from_bytes(text);
        wstring wtext;
        utf8::utf8to16(text.begin(), text.end(), back_inserter(wtext));
        while ( end < wtext.size() ) {
            if (LangUtils::isSpaceChar(wtext[end])) {
                segs.push_back(wtext.substr(start, end-start));
                while(end < wtext.size() && LangUtils::isSpaceChar(wtext[end]))
                    end++;
                if (end >= wtext.size() )
                    break;
                start = end;
            }
            if (LangUtils::isChinese(wtext[end])) {
                if (end > start) {
                    segs.push_back(wtext.substr(start,end-start));
                    precedentByChinese = false;
                } else {
                    precedentByChinese = true;
                }
                start = end;
                if (start < wtext.size() - 1 && LangUtils::isChinese(wtext[start+1])) {
                    segs.push_back(wtext.substr(start, 2));
                    end = ++start;
                } else {
                    if (!precedentByChinese){
                        segs.push_back(wtext.substr(start, 1));
                    }
                    end = ++start;
                }
            } else {
                end++;
            }
        }
        vector<string> result;
        for (int i = 0; i < segs.size(); ++i) {
//            result.push_back(converter.to_bytes(segs[i]));
            string res;
            utf8::utf16to8(segs[i].begin(), segs[i].end(), back_inserter(res));
            result.push_back(res);
        }
        return result;
    }

END_THUNLP_NAMESPACE