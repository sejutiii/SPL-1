#include <iostream>
#include <vector>
#include <cmath> 
#define EPS 10e-9

using namespace std;

vector<vector<double>> matrix;
vector<vector<double>> inverseMat;
vector<vector<double>> augMat;
bool isSingular= false;
int n;

void matrixInitialization(vector<vector<double>> x)
{
    if(x.empty()) return;

    n= x.size();
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

    augMat.resize(n, vector<double> (2*n));

    int k=n;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            augMat[i][j]= matrix[i][j];
            augMat[i][k+j]= inverseMat[i][j];
        }
    }
}

void setInverse()
{
    int temp = n;
    cout <<"n= " <<  n << endl;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            inverseMat[i][j]= augMat[i][j+n];
        }
    }
}

void inverseAugMat()
{
    for(int i=0; i<n; i++)
    {
        int temp=0;
        double pivot= augMat[i][i];

        if(fabs(pivot) < EPS)
        {
            for(int j= i+1; j<n; j++)
            {
                if(fabs(augMat[j][i]) !=0)
                {
                    temp= j;
                    break;
                }
            }

            swap(augMat[i], augMat[temp]);
        }

        pivot= augMat[i][i];

        for(int j=i+1; j<n; j++)
        {
            double ratio= augMat[j][i]/ pivot;
            //temp= n;
            for(int k=0; k<2*n; k++)
            {
                augMat[j][k] = augMat[j][k]- (ratio* augMat[i][k]);
                if(fabs(augMat[j][k]) < EPS)
                {
                    augMat[j][k]= 0;
                }
            }
        }
    }

    for(int i=n-1; i>=0; i--)
    {
        double pivot= augMat[i][i];
        for(int j=i-1; j>=0; j--)
        {
            double ratio = augMat[j][i]/ pivot;
            for(int k=0; k<2*n; k++)
            {
                augMat[j][k] = augMat[j][k]- (ratio* augMat[i][k]);
                if(fabs(augMat[j][k]) < EPS)
                {
                    augMat[j][k]= 0;
                }
            }
        }
    }

    for(int i=0; i<n; i++)
    {
        double temp= augMat[i][i];
        for(int j=0; j<2*n; j++)
        {
            augMat[i][j]= augMat[i][j]/ temp;
        }
    }
}

void GetinverseMatrix(vector<vector<double>> x) 
{
    matrixInitialization(x);
    
    inverseAugMat();

    setInverse();
}

void printInverse(vector<vector<double>> x)
{
    GetinverseMatrix(x);
    cout << "n= " << n;
    if(isSingular == true)
    {
        cout << "Cannot calculate inverse." << endl;
        return;
    }
    cout << "The inverse matrix:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = n; j < 2*n; j++) {
            cout << augMat[i][j] << " ";
        }
        cout << endl;
    }
}