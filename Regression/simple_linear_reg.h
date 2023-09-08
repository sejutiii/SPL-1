#include<stdio.h>
#include<iostream>
#include<vector>
#include"../Regression_Headers/linearRegression.h"

using namespace std;

void simple_linear_regression(int rows, int column, vector< vector<double> > &dataset, vector<string> &strHeaders)
{
    getInput(rows, column, dataset, strHeaders);
    trainingModel();
    int choice;
    cout << "Do you want to- " << endl;
    cout << "1. Test for a fitted value" << endl;
    cout << "2. Get the interpretation of the model" << endl;
    cin >> choice;
    if(choice == 1)
    {
        bool flag= true;
        while(flag)
        {
            double x, y;
            cout << "Enter the x value: ";
            cin >> x;
            y= predictor(x);
            cout << "y= " << y << endl;
            char temp;
            cout << "Press c to continue, q to quit"<< endl;
            cin >> temp;
            if(temp== 'c'|| temp == 'C')
                continue;
            else
                flag= false;
        }

        char temp;
        cout << "Do you want to get the interpretation of the model?(y/n): " << endl;
        cin >> temp;
        if(temp == 'y' || temp == 'Y')
            choice= 2;
    }
    if(choice == 2)
    {
        cout << endl;
        interpretationOfParameters();
        cout << endl;
        interpretationOfCOD();
    }
}