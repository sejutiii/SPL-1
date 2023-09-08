#include <iostream>
#include <vector>
#include <cmath> 
#define EPS 10e-9

using namespace std;

//const double EPS = 1e-9;

vector<vector<double>> matrix;
vector<vector<double>> inverseMat;
vector<vector<double>> augMat;
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

void GetinverseMatrix(vector<vector<double>> x) 
{
    matrixInitialization(x);
    
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
        for (int j = n; j < 2*n; j++) {
            cout << augMat[i][j] << " ";
        }
        cout << endl;
    }
}


int main() 
{
    cout << "Enter the dimensions of the matrix: ";
    //int n;
    cin >> n;

    vector< vector<double> > x;
    x.resize(n, vector<double>(n));

    cout << "Enter the input matrix:" << endl;
    freopen("inverse.txt", "r", stdin);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> x[i][j];
        }
    }

    printInverse(x);
}