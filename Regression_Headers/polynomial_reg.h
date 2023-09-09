#include<iostream>
#include<vector>
#include"../OLS/matrixCalc.h"
#include"../OLS/inverseMatrix.h"

using namespace std;

vector <vector <double>> poly_X;
vector <vector <double>> poly_Y;
vector <vector <double>> poly_beta;
vector <vector <double>> poly_sumY;
vector <vector <double>> poly_sumX;

int degree;

void poly_sumCalc(int rows);

void initialization(int rows, int columns, vector< vector<double> >dataset, vector<string>strHeaders)
{
   int xCol, yCol;
    if(columns == 2)
    {
        xCol= 0;
        yCol= 1;
    }
    else
    {
        cout << "For polynomial regression- " << endl;
        cout << "Enter the x column: " ;
        cin >> xCol;
        xCol--;
        cout << "Enter the y column: ";
        cin >> yCol;
        yCol--;
    }

    cout << "Enter the degree for the polynomial: ";
    cin >> degree;

    if(degree >= rows/2)
    {
        cout << "For this degree the model is highly overfitting the data" << endl;
        cout << "Please Enter a more suitable degree: ";
        cin >> degree;
    }

    else if(degree >= 15)
    {
        char temp;
        cout << "For this degree the model might be highly overfitting the data" << endl;
        cout << "Do you want to change the degree ?(y/n): ";
        cin >> temp;
        if(temp == 'y' || temp == 'Y')
        {
            cout << "Please Enter the new degree: ";
            cin >> degree;
        }
    }

    poly_X.resize(rows, vector<double> (2*degree+1));
    poly_Y.resize(rows, vector<double> (degree+1));
    
    double xi, yi;
    for(int i=0; i<rows; i++)
    {
        xi= dataset[i][xCol];
        poly_X[i][0]= 1;
        poly_X[i][1]= xi;
        for(int j=2; j<= 2*degree; j++)
        {
            poly_X[i][j]= (poly_X[i][j-1]* xi);
        }
        yi= dataset[i][yCol];
        poly_Y[i][0]= yi;

        for(int j=1; j<= degree; j++)
        {
            poly_Y[i][j]= (yi* poly_X[i][j]);
        }
    }

    poly_sumCalc(rows);
}

void poly_sumCalc(int rows)
{
    int n= degree+1;
    poly_sumX.resize(n, vector<double> (n));
    poly_sumY.resize(n, vector<double> (1));
    vector<double> sumX;
    vector<double> sumY;
    int m= 2*degree+1;
    sumX.resize(m);
    sumY.resize(n);

    for(int i=0; i<m; i++)
    {
        sumX[i]=0;
        if(i<n)
        {
            sumY[i]= 0;
        }
        for(int j=0; j<rows; j++)
        {
            sumX[i]+= poly_X[j][i];
            if(i<n)
            {
                sumY[i] += poly_Y[j][i];
            }
        }
    }

    cout << "Sum calc- " << endl;
    for(int i=0; i<n; i++)
    {
        poly_sumY[i][0]= sumY[i];
        cout << poly_sumY[i][0] << " ";
        for(int j=0; j<n; j++)
        {
            poly_sumX[i][j]= sumX[i+j];
            cout << poly_sumX[i][0] << " ";
        }
        cout << endl;
    }

}

void trainingThePolynomialModel()
{
    vector< vector<double> > mat_inverse;
    GetinverseMatrix(poly_sumX, mat_inverse);
    matrixMultiplication(mat_inverse, poly_sumY, poly_beta); 
    cout << endl << "beta= " << endl;
    printMat(poly_beta);
}