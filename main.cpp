#include <iostream>
#include <vector>
#include "ClassifyResult.h"
#include "BasicTextClassifier.h"
#include "LinearBigramChineseTextClassifier.h"
#include "pthread.h"
using namespace std;
using namespace thunlp;

#define THREADS_NUM 5

struct Parameter{
    string text;
    int topN;
    BasicTextClassifier* classifier;
};


void *classifyText(void* args) {
    Parameter* p = (Parameter*) args;
    vector<ClassifyResult> results = p->classifier->classifyText(p->text, p->topN);
    for (int i = 0; i < p->topN; ++i) {
        cout << results[i].label_ << "\t\t"
        << results[i].probability_ << endl;
    }
}

int main() {

    //新建分类对象
    BasicTextClassifier* classifier = new BasicTextClassifier();

    //设置分类器种类 读取模型
    classifier->loadCategoryListFromFile("/Users/Fan/Downloads/tencent_model_100W/category");
    classifier->setTextClassifier(new LinearBigramChineseTextClassifier(classifier->getCategorySize()));
    classifier->getTextClassifier()->loadModel("/Users/Fan/Downloads/tencent_model_100W");

    //使用分类器进行分类
    string text = "再次回到世锦赛的赛场上,林丹终于变回了以前的那个超级丹.";
//    int topN = 3;
//    vector<ClassifyResult> results = classifier->classifyText(text, topN);
//    for (int i = 0; i < topN; ++i) {
//        cout << results[i].label_ << "\t\t"
//        << results[i].probability_ << endl;
//    }

    //pthread多线程测试
    pthread_t threads[THREADS_NUM];
    int rc;
    Parameter para = {text, 3, classifier};
    for (int i = 0; i < THREADS_NUM; ++i) {
        cout << "main() : creating thread, " << i << endl;
        rc = pthread_create(&threads[i], NULL, classifyText, (void *)&para);
        if (rc){
            cout << "Error:unable to create thread," << rc << endl;
            exit(-1);
        }
    }
    pthread_exit(NULL);
}
