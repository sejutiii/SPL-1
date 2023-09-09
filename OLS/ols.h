#ifndef OLS_h
#define OLS_h

#include<bits/stdc++.h>
#include "inverseMatrix.h"
#include"matrixCalc.h"

using namespace std;

void ols_calculation(vector< vector<double> > &matX, vector <vector<double>> &matY, vector< vector<double> > &beta) 
{
    vector< vector<double> > mat_Xtranspose;
    vector< vector<double> > mat_inverse;
    vector< vector<double> > mat_temp1;
    vector< vector<double> > mat_temp2;
    
    transpose(matX, mat_Xtranspose);
    matrixMultiplication(mat_Xtranspose, matX, mat_temp1);
    GetinverseMatrix(mat_temp1, mat_inverse);

    matrixMultiplication(mat_inverse, mat_Xtranspose, mat_temp2);
    matrixMultiplication(mat_temp2, matY, beta);
}

double get_Syy(vector <vector<double>> &matY)
{
    double mean= 0;
    int n= matY.size();
    double sum= 0;
    for(int i=0; i<n; i++)
    {
        sum += matY[i][0];
    }

    mean= sum/n;

    double Syy= 0;
    for(int i=0; i<n; i++)
    {
        Syy += (matY[i][0]- mean)* (matY[i][0]- mean);
    }
    return Syy;
}

double get_SSR(vector< vector<double> > &matX, vector <vector<double>> &matY, vector< vector<double> > &beta)
{
    vector< vector<double> > mat_Xtranspose;
    vector< vector<double> > mat_Ytranspose;
    vector< vector<double> > beta_transpose;
    vector< vector<double> > mat_temp1;
    vector< vector<double> > mat_temp2;
    vector< vector<double> > mat_temp3;

    vector< vector<double> > resultant;

    transpose(matY, mat_Ytranspose);
    transpose(matX, mat_Xtranspose);
    transpose(beta, beta_transpose);
    matrixMultiplication(mat_Ytranspose, matY, mat_temp1);
    matrixMultiplication(beta_transpose, mat_Xtranspose, mat_temp2);
    matrixMultiplication(mat_temp2, matY, mat_temp3);

    mat_subtraction(mat_temp1, mat_temp3, resultant);

    double SSR= resultant[0][0] ;

    return SSR;
}

double get_Rsquare(vector< vector<double> > &matX, vector <vector<double>> &matY, vector< vector<double> > &beta)
{
    double Syy= get_Syy(matY);
    double SSR= get_SSR(matX, matY, beta);
    double R_sq= 1- (SSR/ Syy);
    return R_sq;
}

void interpretation_of_Rsq(double R)
{
    cout << "The co-efficient of determination explains how well the model fits the data. "<< endl;
    cout << "This model can explain " << R*100 << "% of the variation in the data. "<< endl << endl;
}

#endif