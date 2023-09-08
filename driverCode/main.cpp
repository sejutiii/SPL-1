#include<iostream>
#include"regression_fileread.h"
#include"../Regression/simple_linear_reg.h"

using namespace std;

void introductoryInterface();
void startTheProgram();

int main()
{
    startTheProgram();
}

void introductoryInterface()
{
    cout << endl << "welcome to DataSift!" << endl << endl;
    cout << "The program can currently perform- " << endl;
    cout << "1. Simple Linear Regression" << endl;
    cout << "2. Multiple Linear Regression" << endl;
    cout << "3. Simple Polynomial Regression" << endl << endl;
}

void startTheProgram()
{
    introductoryInterface();
    int choice;

    cout << "Please Enter which operation you want to perform (1/2/3) or any other number to quit: " ;

    cin >> choice;

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
        cout << "MLR" << endl;
        break;
        case 3:
        cout << "PR" << endl;
        break;
        default:
        return;
    }

}

