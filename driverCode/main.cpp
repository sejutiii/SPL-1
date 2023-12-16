#include<iostream>
#include"csvFileReader.h"
#include"textfileReader.h"
#include"../Regression/simple_linear_reg.h"
#include"../Regression/multiple_linear_reg.h"
#include"../Regression/polynomial_reg.h"
#include"../classification_headers/logisticReg.h"
#include"../classification/multinomial_NaiveBayes.h"
#include"../classification/KNN_classification.h"
#include"../kMeans/kmeans_implementation.h"

using namespace std;

void introductoryInterface();
void learn_about_the_program();
void startTheProgram();

int main()
{
    startTheProgram();
}

void introductoryInterface()
{
    cout << "--------------------------------------------------------------------------------------------" << endl;
    cout << endl << "welcome to DataSift!" << endl << endl;
    cout << "-------------------------------------------------------------------------------------------" << endl;
    cout << endl << "The program can currently perform- " << endl << endl;
    cout << "1. Simple Linear Regression" << endl;
    cout << "2. Multiple Linear Regression" << endl;
    cout << "3. Simple Polynomial Regression" << endl << endl;
    cout << "4. Logistic Regression" << endl;
    cout << "5. Naive Bayes Classification" << endl;
    cout << "6. KNN classification" << endl << endl;
    cout << "7. K means clustering" << endl << endl;
}

void startTheProgram()
{
    introductoryInterface();
    int choice;

    cout << "Please Enter which operation you want to perform (1/2/3/4/5/6/7) or any other number to quit: " ;

    cin >> choice;

    if(choice == 5)
    {
        vector< vector <string>> str_dataset;
        vector <string> header;
        readTextFile(str_dataset, header);
        int rows= str_dataset.size();
        int columns= str_dataset[0].size();
        cout << rows << " " << columns << " " << endl;
        NaiveBayesTextModule(rows, columns, str_dataset, header);
        return;
    }

    vector< vector <double>> dataset;
    vector <string> title;
    readFile(dataset, title);
    int rows= dataset.size();
    int columns= dataset[0].size();

    switch(choice)
    {
        case 1:
        simple_linear_regression(rows, columns, dataset, title);
        break;
        case 2:
        multilinear_regression(rows, columns, dataset, title);
        break;
        case 3:
        polynomial_regression(rows, columns, dataset, title);
        break;
        case 4:
        logisticRegModelTrain(rows, columns, dataset, title);
        break;
        case 6: 
        knn_classification(rows, columns, dataset, title);
        break;
        case 7: 
        kMeansClustering(rows, columns, dataset, title);
        break;
        default:
        cout <<"Exit" <<endl;
        break;
    }
}