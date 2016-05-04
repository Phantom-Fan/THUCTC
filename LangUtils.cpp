//
// Created by 范子豪 on 16/4/27.
//

#include "LangUtils.h"
#include "ChineseLanguageConstants.h"
#include <locale>
#include <codecvt>
using namespace std;
using namespace thunlp;
BEGIN_THUNLP_NAMESPACE

    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    bool thunlp::LangUtils::isSpaceChar(wchar_t character) {
        return character == converter.from_bytes(' ')[0];
    }
    bool thunlp::LangUtils::isChinese(wchar_t character) {
        return (int)character >= ChineseLanguageConstants::CHINESE_START && (int)character <= ChineseLanguageConstants::CHINESE_END;
    }

END_THUNLP_NAMESPACE

