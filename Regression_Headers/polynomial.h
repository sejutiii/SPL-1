#include<iostream>
#include<vector>
#include"../OLS/ols.h"

using namespace std;

vector <vector <double>> poly_X;
vector <vector <double>> poly_Y;
vector <vector <double>> poly_beta;

int degree;

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


    poly_X.resize(rows, vector<double> (degree+1));
    poly_Y.resize(rows, vector<double> (1));
    
    double xi, yi;
    for(int i=0; i<rows; i++)
    {
        yi= dataset[i][yCol];
        poly_Y[i][0]= yi;
        xi= dataset[i][xCol];
        poly_X[i][0]= 1;
        poly_X[i][1]= xi;
        for(int j=1; j<degree; j++)
        {
            poly_X[i][j+1]= (poly_X[i][j]* xi);
        }
    }
}

void trainingThePolynomialModel()
{
    ols_calculation(poly_X, poly_Y, poly_beta);
    cout << endl << "beta= " << endl;
    printMat(poly_beta);
    cout << endl;
}

// double get_SSE()
// {
//     int n= poly_X.size();
//     double SSE= 0;
//     for(int i=0; i<n; i++)
//     {
//         double y_val=0;
//         for(int j=0; j<=degree; j++)
//         {
//             y_val += (poly_X[i][j] * poly_beta[j][0]);
//         }
//         double error= poly_Y[i][0]- y_val;
//         SSE += (error * error);
//     }
//     return SSE;
// }

double poly_test_for_y()
{
    vector<double> x;
    //x.resize(degree+1);
    x.push_back(1);
    cout << "Enter the x value to test: ";
    double xi;
    cin >> xi;
    x.push_back(xi);
    for(int i=1; i<degree; i++)
    {
        x.push_back((x[i]* xi));
    }

    double y=0;
    for(int i=0; i<=degree; i++)
    {
        y += (x[i] * poly_beta[i][0]);
    }

    return y;
}



void interpretation_polynomial()
{
    double R= get_Rsquare(poly_X, poly_Y, poly_beta);
    cout << "R_sq= " << R << endl;
    if(R < 0 || R >1 )
    {
        cout << "This degree of the polynomial is a terrible fit for the model. ";
    }
    else interpretation_of_Rsq(R);
}
  

// void test_poly()
// {
//     double SSE= get_SSE();
//     double Syy= get_Syy(poly_Y);
//     double R_sq= 1- (SSE/ Syy);
//     cout << "R_sq= " << R_sq << endl;
// }
