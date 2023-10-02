#include<bits/stdc++.h>
#include"../Regression_Headers/linearRegression.h"

using namespace std;

void logisticRegModelTrain(int rows, int column, vector< vector<double> > &dataset, vector<string> &strHeaders);
int getPrediction();
double getZ();
double sigmoid(double z);

void logisticRegModelTrain(int rows, int column, vector< vector<double> > &dataset, vector<string> &strHeaders)
{
    InputforLogisticReg(rows, column, dataset, strHeaders);
    trainingModel();
    getPrediction();
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
    cout << "p= " << p << endl;
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