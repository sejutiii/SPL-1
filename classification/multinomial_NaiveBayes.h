#include"../classification_headers/multinomial_NB.h"

void NaiveBayesTextModule(int rows, int columns, vector<vector<string>> &dataset, vector<string> &strHeaders)
{
    processingtheDataset(rows, columns, dataset, strHeaders);
    int choice;
    while(true)
    {
        cout << endl << "Do you want to- " << endl;
        cout << "1. Print Frequency table" << endl;
        cout << "2. Test for an input value" << endl;
        cout << "3. Quit" << endl;
        cout << "Enter your choice here: ";
        cin >> choice;
        if(choice == 1) printFreqTable(strHeaders);
        else if(choice ==2) predict_for_a_newPoint(strHeaders);
        else break;
    }
}