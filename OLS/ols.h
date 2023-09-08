#include<bits/stdc++.h>
#include "inverseMatrix.h"
#include"matrixCalc.h"

using namespace std;

// double getZ(vector<vector<double>> &beta)
// {
//     vector<double> x;
//     double z= 0;
//     x.resize(numColumn);
//     cout << "Enter the values of x: " << endl;

//     x[0]= 1;
//     for(int i=1; i<numColumn; i++)
//     {
//         cin >> x[i];
//     }

//     for(int i=1; i<numColumn; i++)
//     {
//         z += (x[i]* beta[i][0]);
//     }

//     cout << "z= " << z;
//     return z;
// }

void ols_calculation(vector< vector<double> > &matX, vector <vector<double>> &matY, vector< vector<double> > &beta) 
{
    vector< vector<double> > mat_Xtranspose;
    vector< vector<double> > mat_temp1;
    vector< vector<double> > mat_temp2;
    
    transpose(matX, mat_Xtranspose);
    matrixMultiplication(mat_Xtranspose, matX, mat_temp1);
    GetinverseMatrix(mat_temp1);

    matrixMultiplication(inverseMat, mat_Xtranspose, mat_temp2);
    matrixMultiplication(mat_temp2, matY, beta);
}