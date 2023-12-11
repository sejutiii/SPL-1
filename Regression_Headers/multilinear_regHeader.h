#include<bits/stdc++.h>
#include"../OLS/ols.h"

using namespace std;

vector<int> xColumns;
int yColumn;

vector <vector <double>> matX;
vector <vector <double>> matY;
vector <vector <double>> matBeta;
vector<string> titles;

void getInputMatrix(int rows, int columns, vector< vector<double> >dataset, vector<string>strHeaders)
{
    int numV;
    cout << "How many independent variables do you want to test? ";
    cin >> numV;
    if(numV >= columns)
    {
        cout << "The number of independent variables has to be less than " << columns << endl;
        exit(1);
    }
    else if(numV == columns-1)
    {
        for(int i=0; i<columns-1; i++)
        {
            xColumns.push_back(i);
        }
        yColumn= columns-1;
    }
    else{
        cout << "Enter the x columns: " << endl;
        int temp;
        for(int i=0; i<numV; i++)
        {
            cin >> temp;
            xColumns.push_back(temp-1);
        }
        cout << "Enter the y column: "<< endl ;
        cin >> yColumn;
        yColumn--;
    }
    
    matX.resize(rows, vector<double> (numV+1));
    matY.resize(rows, vector<double> (1));

    for(int i=0; i<rows; i++)
    {
        matX[i][0]= 1;
        for(int j=0; j<columns; j++)
        {
            if(j== yColumn)
            {
                matY[i][0]= dataset[i][j];
            }
            else
            {
                for(int k=0; k<numV; k++)
                {
                    if(xColumns[k]== j)
                    {
                        matX[i][k+1]= dataset[i][j];
                    }
                }
            }
        }
    }

    if(!strHeaders.empty())
    {
        for(int i=0; i<columns; i++)
        {
            titles.push_back(strHeaders[i]);
        }
    }
}

void trainTheModel()
{
    ols_calculation(matX, matY, matBeta);
    // cout << endl << "beta= " << endl;
    // printMat(matBeta);
    // cout << endl;
}

double test_for_y()
{
    int k= xColumns.size();
    vector<double> x;
    x.resize(k+1);
    x[0]= 1;
    for(int i=0; i<k; i++)
    {
        cout << "Enter the x value for " 
        << titles[xColumns[i]] << ": ";
        cin >> x[i+1];
    }
    double y=0;
    for(int i=0; i<=k; i++)
    {
        y += (x[i] * matBeta[i][0]);
    }
    return y;
}

void interpretation()
{
    double R_sq= get_Rsquare(matX, matY, matBeta);
    cout << "R_sq= " << R_sq << endl;
    interpretation_of_Rsq(R_sq);
}