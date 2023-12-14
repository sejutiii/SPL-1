#include<bits/stdc++.h>
#include"../Regression_Headers/linearRegression.h"

using namespace std;

double z, p;
int xCol, yCol;

void logisticRegModelTrain(int rows, int column, vector< vector<double> >dataset, vector<string>strHeaders);
int getPrediction(vector<string>strHeaders);
double getZ(vector<string>strHeaders);
double sigmoid(double z);
//void InputforLogisticReg(int rows, int columns, vector< vector<double> >dataset, vector<string>strHeaders);

void InputforLogisticReg(int rows, int columns, vector< vector<double> >dataset, vector<string>strHeaders)
{
   double threshold;
    if(columns == 2)
    {
        xCol= 0;
        yCol= 1;
    }
    else
    {
        cout << endl << "For logistic regression- " << endl;
        cout << "Enter the x column: " ;
        cin >> xCol;
        xCol--;
        cout << "Enter the y column: ";
        cin >> yCol;
        yCol--;
    }
    
    double xi, yi;
    for(int i=0; i<rows; i++)
    {
        yi= dataset[i][yCol];
        if(yi == 0 || yi == 1)
        {
           threshold=1;
        }
        else 
        {
            cout <<"The target variable is not binary. " << endl;
            cout << "Set a threshold for the target variable " << strHeaders[yCol] << ": ";
            cin >> threshold;
            break;
        }
    }

    for(int i=0; i<rows; i++)
    {
        xi= dataset[i][xCol];
        yi= dataset[i][yCol];
        if(yi < threshold) yi= 0;
        else yi= 1;
        x.push_back(xi);
        y.push_back(yi);
    }
}

void log_reg_interpretation()
{
    cout<< endl << "For this input value the probability in sigmoid function, p= " << p << endl << endl;
}

void logisticRegModelTrain(int rows, int column, vector< vector<double> >dataset, vector<string>strHeaders)
{
    InputforLogisticReg(rows, column, dataset, strHeaders);
    trainingModel();
    char q= 'c';
    while (q != 'q')
    {
        getPrediction(strHeaders);
        cout << endl << "press q to quit, anything else to continue: ";
        cin >> q;
    }
    cout << endl << "Do you want the interpretation of this output value? (y/n): ";
    cin >> q;

    if(q== 'y'|| q== 'Y')
    {
        log_reg_interpretation();
    }
}
double getZ(vector<string>strHeaders)
{
    double xi, z;
    cout <<"Enter the new x value for testing ("<< strHeaders[xCol] << "): "<< endl;
    cin >> xi;
    z= predictor(xi); //In linear regression
    return z;
}

double sigmoid(double z)
{
    double val= 1.0/(1.0 + exp(-z));
    return val;
}

int getPrediction(vector<string>strHeaders)
{
    z= getZ(strHeaders);
    p= sigmoid(z);
    if(p < 0.5) 
    {
        cout << "The predicted value= 0" << endl;
        return 0;
    }
    else
    {
        cout << "The predicted value= 1" << endl;
        return 1;
    }
}