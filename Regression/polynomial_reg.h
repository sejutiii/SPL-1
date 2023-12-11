#include<iostream>
#include<vector>
#include"../Regression_Headers/polynomial_reg.h"

void polynomial_regression(int rows, int columns, vector< vector<double> > &dataset, vector<string> &strHeaders)
{
    initialization(rows, columns, dataset, strHeaders);
    trainingThePolynomialModel();
//     double y= poly_test_for_y();
//     cout << "y= " << y <<endl;
    //interpretation_polynomial();
}