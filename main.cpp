#include <iostream>
#include <vector>
#include "ClassifyResult.h"
#include "BasicTextClassifier.h"
#include "LinearBigramChineseTextClassifier.h"
#include "pthread.h"
using namespace std;
using namespace thunlp;

#define THREADS_NUM 10

struct Parameter{
    string text;
    int topN;
    BasicTextClassifier* classifier;
};


void *classifyText(void* args) {
    Parameter* p = (Parameter*) args;
    vector<ClassifyResult> results = p->classifier->classifyText(p->text, p->topN);
    for (int i = 0; i < p->topN; ++i) {
        printf("%d\t\t%lf\n", results[i].label_, results[i].probability_);
    }
    pthread_exit(nullptr);
}

BasicTextClassifier* initClassifier(const string& category, const string& model){
    BasicTextClassifier* classifier = new BasicTextClassifier();
    classifier->loadCategoryListFromFile(category);
    classifier->setTextClassifier(new LinearBigramChineseTextClassifier(classifier->getCategorySize()));
    classifier->getTextClassifier()->loadModel(model);
    return classifier;
}

int main() {

    //新建分类对象
    BasicTextClassifier* classifier = initClassifier("/Users/Fan/Downloads/tencent_model_100W/category",
                                                     "/Users/Fan/Downloads/tencent_model_100W");

    //使用分类器进行分类
    string text = "再次回到世锦赛的赛场上,林丹终于变回了以前的那个超级丹.";
    int topN = 3;

    //单线程
//    vector<ClassifyResult> results = classifier->classifyText(text, topN);
//    for (int i = 0; i < topN; ++i) {
//        printf("%d\t\t%lf\n", results[i].label_, results[i].probability_);
//    }

    //pthread多线程测试
    pthread_t threads[THREADS_NUM];
    int rc;
    Parameter para[THREADS_NUM];
    for (int i = 0; i < THREADS_NUM; ++i) {
        printf("main() : creating thread, %d\n", i);
//        BasicTextClassifier* tempclass = initClassifier("/Users/Fan/Downloads/tencent_model_100W/category",
//                                                        "/Users/Fan/Downloads/tencent_model_100W");
        para[i] = {text, topN, classifier};
        rc = pthread_create(&threads[i], NULL, classifyText, (void *)&para[i]);
    }
    pthread_exit(nullptr);
}
