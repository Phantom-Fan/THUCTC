//
// Created by 范子豪 on 16/4/22.
//
#pragma once
#ifndef CLASSIFIERLIB_CLASSIFIER_DEF_H
#define CLASSIFIERLIB_CLASSIFIER_DEF_H
#define BEGIN_THUNLP_NAMESPACE namespace thunlp {
#define END_THUNLP_NAMESPACE }
#include <unistd.h>
#include <string>
inline bool exists_test (const std::string& name) {
    return ( access( name.c_str(), F_OK ) != -1 );
}
#endif //CLASSIFIERLIB_CLASSIFIER_DEF_H
