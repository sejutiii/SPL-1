#include<iostream>
#include<vector>
#include<math.h>
#define EPS 10e-5

using namespace std;

vector < vector<double> > matrix;
vector <vector <double>> matCalc;
vector <vector <double> > inverseMat;
vector <vector <double> > augmentedMatrix;

double determinant;
bool flag = true;
int n; // n= dimension of the square matrix

void recDet(int i)
{

    if(i == 2*n-1) return;
    
    double prod;
    int col= i;
    if(flag) 
    {
        prod = 1;
        for(int row=0; row<n; row++)
        {
            prod *= matCalc[row][col];
            col++;
        }
    }
    
    else 
    {
        prod = -1;
        for(int row=0; row<n; row++)
        {
            prod *= matCalc[row][col];
            col--;
        }

    }

    determinant += prod;

    if(i == n-1 && flag == true)
    {
        flag = false;
        i= n-2;
    }
    recDet(i+1);
}

// calculates the inverse by Gauss Elimination
void inverse()
{
    
}

int main()
{
    cout<< "Enter the dimensions of the matrix: ";
    cin >> n;
    matrix.resize(n, vector<double> (n));
    matCalc.resize(n, vector<double> (2*n));
    augmentedMatrix.resize(n, vector<double> (2*n));
    cout << "Enter the input matrix:" << endl;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            cin >> matrix[i][j];
        }
    }

    for(int i=0; i<n; i++)
    {
        for(int j=0; j< (2*n); j++)
        {
            if(j<n)
            {
                matCalc[i][j]= matrix[i][j];
            }
            else
            {
                matCalc[i][j]= matrix[i][j-n];
            }
        }
    }

    determinant=0;
    inverse();

    cout << "print the inverse matrix:" << endl;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j< n ; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    // recDet(0);

    cout << "The determinant is " << determinant << endl; 
}