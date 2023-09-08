#include<stdio.h>
#include<iostream>
#include<vector>
#include"../Regression_Headers/multilinear_regHeader.h"

void multilinear_regression(int rows, int columns, vector< vector<double> > &dataset, vector<string> &strHeaders)
{
    getInputMatrix(rows, columns, dataset, strHeaders);
    trainTheModel();
    //double y= test_for_y();
    //cout << "y= " << y << endl;

    interpretation();
}