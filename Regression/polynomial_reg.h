#include<iostream>
#include<vector>
#include"../Regression_Headers/polynomial.h"

void polynomial_regression(int rows, int columns, vector< vector<double> > &dataset, vector<string> &strHeaders)
{
    initialization(rows, columns, dataset, strHeaders);
    trainingThePolynomialModel();

    int choice;
    cout << "Do you want to- " << endl;
    cout << "1. Test for a fitted value" << endl;
    cout << "2. Get the interpretation of the model" << endl;
    cout << "3. Quit" << endl << endl;
    cout << "Enter choice: ";
    cin >> choice;

    if(choice == 1)
    {
        bool flag= true;
        while(flag)
        {
            double y= poly_test_for_y();
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
        cout << "Interpretation of the model: " << endl << endl;
        interpretation_polynomial();
        cout << endl;
    }
}