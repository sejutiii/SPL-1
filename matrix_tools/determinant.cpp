#include<iostream>
#include<vector>

using namespace std;

vector < vector<double> > matrix;
vector <vector <double>> matCalc;

double determinant;
bool flag = true;

void recDet(int i, int n)
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
    recDet(i+1, n);
}

int main()
{
    cout<< "Enter the dimensions of the matrix: ";
    int n;
    cin >> n;
    matrix.resize(n, vector<double> (n));
    matCalc.resize(n, vector<double> (2*n));
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

    cout << "print the matrix:" << endl;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j< 2*n ; j++)
        {
            cout << matCalc[i][j] << " ";
        }
        cout << endl;
    }

    determinant=0;
    recDet(0, n);

    cout << "The determinant is " << determinant << endl; 
}