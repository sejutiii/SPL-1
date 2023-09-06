#include<bits/stdc++.h>
#include "inverseMatrix.h"
#include"matrixCalc.h"

using namespace std;

int numRow, numColumn;

void getInputMat(vector< vector<double> > &matX, vector <vector<double>> &matY)
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
    vector< vector<double> > matX;
    vector <vector<double>> matY;
    vector< vector<double> > mat_Xtranspose;
    vector< vector<double> > matZ;
    vector< vector<double> > temp;
    vector< vector<double> > Beta;
    getInputMat(matX, matY);
    transpose(matX, mat_Xtranspose);
    matrixMultiplication(mat_Xtranspose, matX, matZ);
    n= mat_Xtranspose.size();
    cout << "n= " << n << endl;
    GetinverseMatrix(matZ);
    //printMat(matZ);
    //printInverse(matZ);

    // cout << mat_Xtranspose.size() << endl; 
    matrixMultiplication(inverseMat, mat_Xtranspose, temp);
    matrixMultiplication(temp, matY, Beta);

    cout << endl << "beta= " << endl;

    for(int i=0; i<Beta.size(); i++)
    {
        for(int j=0; j<Beta[0].size(); j++)
        {
            cout << Beta[i][j] << " ";
        }
        cout << endl ;
    }

    return 0;
}