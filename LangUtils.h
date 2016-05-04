//
// Created by 范子豪 on 16/4/27.
//

#ifndef CLASSIFIERLIB_LANGUTILS_H
#define CLASSIFIERLIB_LANGUTILS_H
#include "classifier_def.h"
#include <string>
BEGIN_THUNLP_NAMESPACE

    class LangUtils {
    public:
        LangUtils(){}
        ~LangUtils(){}
        static bool isSpaceChar(wchar_t character);
        static bool isChinese(wchar_t character);
    };

END_THUNLP_NAMESPACE

#endif //CLASSIFIERLIB_LANGUTILS_H
