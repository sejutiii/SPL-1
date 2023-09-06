#include <iostream>
#include <vector>
#include <cmath> 
#define EPS 10e-5

using namespace std;

vector<vector<double>> matrix;
vector<vector<double>> inverseMat;
bool isSingular= false;
int n;

void matrixInitialization(vector<vector<double>> x)
{
    if(x.empty()) return;

    int n= x.size();
    matrix.resize(n, vector<double>(n));
    inverseMat.resize(n, vector<double>(n));

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            matrix[i][j]= x[i][j];
        }
    }

    for(int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
            if( i== j) inverseMat[i][j] =1 ;
            else inverseMat[i][j] =0 ;
        }
    }
}

void GetinverseMatrix(vector<vector<double>> x) 
{
    matrixInitialization(x);

    for (int p = 0; p < n; p++) 
    {
        
        int pivRow = p;

        for (int i = p + 1; i < n; i++) {
            if (fabs(matrix[i][p]) > fabs(matrix[pivRow][p])) {
                pivRow = i;
            }
        }

        if (pivRow != p) {
            swap(matrix[p], matrix[pivRow]);
            swap(inverseMat[p], inverseMat[pivRow]);
        }

        double pivot = matrix[p][p];

        if (fabs(pivot) < EPS) 
        {
            isSingular= true;
            return;
        }

        for(int i=0; i<n; i++)
        {
            if(i != p)
            {
                double ratio= pivot/ matrix[i][p];
                for(int j=0; j<n; j++)
                {
                    matrix[i][j]= matrix[p][j] - (ratio * matrix[i][j]);
                    inverseMat[i][j]= inverseMat[p][j] - (ratio * inverseMat[i][j]);
                }
            }   
        }
    }
}

void printInverse(vector<vector<double>> x)
{
    GetinverseMatrix(x);
    if(isSingular == true)
    {
        cout << "Cannot calculate inverse." << endl;
        return;
    }
    cout << "The inverse matrix:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << inverseMat[i][j] << " ";
        }
        cout << endl;
    }
}