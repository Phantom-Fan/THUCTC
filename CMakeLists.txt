cmake_minimum_required(VERSION 3.3)
project(classifierlib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lpthread")

set(LIBLINEAR liblinear-2.1/linear.cpp
        liblinear-2.1/linear.h
        liblinear-2.1/tron.cpp
        liblinear-2.1/tron.h
        liblinear-2.1/blas/daxpy.c
        liblinear-2.1/blas/ddot.c
        liblinear-2.1/blas/dnrm2.c
        liblinear-2.1/blas/dscal.c
        liblinear-2.1/blas/blas.h
        liblinear-2.1/blas/blasp.h)
set(LIBCLASSIFY classifier_def.h ClassifyResult.h BasicTextClassifier.cpp BasicTextClassifier.h TextClassifier.h LiblinearTextClassifier.cpp LiblinearTextClassifier.h WordSegment.h TermWeighter.h Lexicon.cpp Lexicon.h DocumentVector.cpp DocumentVector.h Term.h TfOnlyTermWeighter.h LinearBigramChineseTextClassifier.h TfIdfTermWeighter.h BigramWordSegment.h BigramWordSegment.cpp ChineseLanguageConstants.h LangUtils.cpp LangUtils.h)
set(SOURCE_FILES main.cpp)

add_library(linear ${LIBLINEAR})
add_library(classify ${LIBCLASSIFY})

add_executable(classifierlib ${SOURCE_FILES})

target_link_libraries(classify linear)
target_link_libraries(classifierlib classify)