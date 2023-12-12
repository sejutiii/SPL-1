#include"../classification_headers/KNN.h"

void knn_classification(int rows, int columns, vector< vector<double> > &dataset, vector<string> &strHeaders)
{
    KNN_initialize(rows, columns, dataset);
    KNN_classify(rows, columns, dataset);
    KNN_printClusters();
    add_newPoint(rows, columns, dataset, strHeaders);
    classify_newPoint(rows, dataset);
}