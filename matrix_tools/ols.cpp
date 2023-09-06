#include<bits/stdc++.h>
#include "inverseMatrix.h"
#include"matrixCalc.h"

using namespace std;

int numRow, numColumn;

void getInputMat()
{
    vector< vector<double> > dataset;
    vector<string> parameters;

    FILE *fp= fopen("ins.txt", "r");

    if(fp == NULL) 
    {
        cout << "Error in opening file"<< endl;
        exit (1);
    }

    fscanf(fp, "%d %d", &numColumn, &numRow);

    //parameters.resize(numParameters);
    //cout << numParameters << " " << numRows << endl;

    for(int i=0; i<numColumn; i++)
    {
        char temp[20];
        fscanf(fp, "%s", temp);
        parameters.push_back(temp);
    }

    dataset.resize(numRow,vector<double>(numColumn));
    matX.resize(numRow, vector<double> (numColumn));
    matY.resize(numRow, vector<double> (1));

    for(int i=0; i<numRow; i++)
    {
        for(int j=0; j<numColumn; j++)
        {
            fscanf(fp, "%lf", &dataset[i][j]);
        }
    }

    fclose(fp);

    for(int i=0; i<numRow; i++)
    {
        matX[i][0]= 1;
        for(int j=0; j<numColumn; j++)
        {
            if(j== numColumn-1)
            {
                matY[i][0]= dataset[i][j];
            }
            else 
            {
                matX[i][j+1]= dataset[i][j];
            }
        }

    }

    // for(int i=0; i<numRow; i++)
    // {
    //     cout<< i+1 << "   ";
    //     for(int j=0; j<=numColumn; j++)
    //     {
    //         cout<< matX[i][j] << " ";
    //     }
    //     cout << matY[i][0] << " ";
    //     cout<< endl << endl;
    // }

}

int main() 
{
    // cout << "Enter the dimensions of the matrix: ";
    // cin >> n;

    // vector< vector<double> > x;
    // x.resize(n, vector<double>(n));

    // cout << "Enter the input matrix:" << endl;
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++) {
    //         cin >> x[i][j];
    //     }
    // }

    // GetinverseMatrix(x);

    // printInverse();

    getInputMat();
    transpose();
    matrixMultiplication(mat_Xtranspose, matX);
    n= mat_Xtranspose.size();
    GetinverseMatrix(mat_multiplicationOutput);
    //printInverse(mat_multiplicationOutput);

    cout << mat_Xtranspose.size() << endl; 
    matrixMultiplication(inverseMat, mat_Xtranspose);
    matrixMultiplication(mat_multiplicationOutput, matY);

    cout << endl << "beta= " << endl;

    for(int i=0; i<mat_multiplicationOutput.size(); i++)
    {
        for(int j=0; j<mat_multiplicationOutput[0].size(); j++)
        {
            cout << mat_multiplicationOutput[i][j] << " ";
        }
        cout << endl ;
    }

    return 0;
}