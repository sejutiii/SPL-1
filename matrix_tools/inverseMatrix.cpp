#include <iostream>
#include <vector>
#include <cmath> 
#define EPS 10e-5

using namespace std;

vector<vector<double>> matrix;
vector<vector<double>> inverseMat;
bool isSingular= false;
int n; 

void GetinverseMatrix() 
{
    for(int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
            if( i== j) inverseMat[i][j] =1 ;
            else inverseMat[i][j] =0 ;
        }
    }

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

        // for (int j = 0; j < n; j++) 
        // {
        //     matrix[p][j] /= pivot;
        //     inverseMat[p][j] /= pivot;
        // }

        // for (int i = 0; i < n; i++) 
        // {
        //     if (i != p) 
        //     {
        //         double ratio = matrix[i][p];
        //         for (int j = 0; j < n; j++) 
        //         {
        //             matrix[i][j] -= ratio * matrix[p][j];
        //             inverseMat[i][j] -= ratio * inverseMat[p][j];
        //         }
        //     }
        // }

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

void printInverse()
{
    if(isSingular == true)
    {
        cout << "This is a singular matrix. Cannot calculate inverse." << endl;
        return;
    }
    cout << "Print the inverse matrix:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << inverseMat[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    cout << "Enter the dimensions of the matrix: ";
    cin >> n;
    matrix.resize(n, vector<double>(n));
    inverseMat.resize(n, vector<double>(n));

    cout << "Enter the input matrix:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> matrix[i][j];
        }
    }

    GetinverseMatrix();

    printInverse();

    return 0;
}
