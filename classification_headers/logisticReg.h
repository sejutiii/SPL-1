#include<bits/stdc++.h>
#include"../Regression_Headers/linearRegression.h"

using namespace std;

void logisticRegModelTrain(int rows, int column, vector< vector<double> > &dataset, vector<string> &strHeaders);
int getPrediction();
double getZ();
double sigmoid(double z);
//void InputforLogisticReg(int rows, int columns, vector< vector<double> >dataset, vector<string>strHeaders);

void InputforLogisticReg(int rows, int columns, vector< vector<double> >dataset, vector<string>strHeaders)
{
   int xCol, yCol;
   double threshold;
    if(columns == 2)
    {
        xCol= 0;
        yCol= 1;
    }
    else
    {
        cout << "For logistic regression- " << endl;
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

void logisticRegModelTrain(int rows, int column, vector< vector<double> > &dataset, vector<string> &strHeaders)
{
    InputforLogisticReg(rows, column, dataset, strHeaders);
    trainingModel();
    char q= 'c';
    while (q != 'q')
    {
        getPrediction();
        cout <<"press q to quit, anything else to continue: ";
        cin >> q;
    }
}
double getZ()
{
    double xi, z;
    cout <<"Enter the new x value for testing: "<< endl;
    cin >> xi;
    z= predictor(xi);
    return z;
}

double sigmoid(double z)
{
    double val= 1.0/(1.0 + exp(-z));
    return val;
}

int getPrediction()
{
    double z= getZ();
    double p= sigmoid(z);
    if(p < 0.5 ) 
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