#include"../classification_headers/multinomial_NB.h"

void NaiveBayesTextModule(vector<vector<string>> dataset, vector<string> header)
{
    trainingOntheDataset(dataset);
    prediction_model(header);
}