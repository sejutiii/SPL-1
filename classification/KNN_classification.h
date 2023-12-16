#include"../classification_headers/KNN.h"

void knn_classification(int rows, int columns, vector< vector<double> > &dataset, vector<string> &strHeaders)
{
    KNN_initialize(rows, columns, dataset);
    KNN_classify(rows, columns, dataset);
    int choice;
    while(true)
    {
        cout << endl << "Do you want to- " << endl;
        cout << "1. Print the classes" << endl;
        cout << "2. Test for a new data point" << endl;
        cout << "3. Quit" << endl << endl;
        cout << "Enter your choice here: ";
        cin >> choice;
        cout << endl;
        if(choice == 1) KNN_printClusters();
        else if(choice ==2) 
        {
            add_newPoint(rows, columns, dataset, strHeaders);
            classify_newPoint(rows, dataset);
        }
        else break;
    }
    
}