#include<iostream>
#include<stdio.h>
#include<vector>

using namespace std;

vector <double> x;
vector <double> y;
double slope, intercept;
double x_mean, y_mean;
double sumXY, sumX, sumY, sumX_square, sumY_square, Syy, SSR;

bool parametersCalculated = false;

void sumCalc()
{
    int n= x.size();
    for(int i=0; i<n; i++)
    {
        sumX += x[i];
        sumY += y[i];
        sumXY += x[i]*y[i];
        sumX_square += x[i]*x[i];
        sumY_square += y[i]*y[i];
    }
}

void calcMean()
{
    int n= x.size();
    sumCalc();
    x_mean= sumX/ n;
    y_mean= sumY/ n;
}

void calcSlope()
{
    int n= x.size();
    calcMean();

    double numerator = sumXY - (n * x_mean * y_mean);
    double denominator= sumX_square - ( n * x_mean* x_mean);

    slope= numerator/ denominator;
}

void calcIntercept()
{
    calcSlope();
    intercept= y_mean - (slope* x_mean);
    parametersCalculated = true;
}

double predictor(double xi)
{
    double yi;
    if(!parametersCalculated) calcIntercept();
    yi= intercept + (slope* xi);
    return yi;
}

double ResidualinValue(double xi, double yi)
{
    double fittedValue= predictor(xi);
    double error= (yi- fittedValue); 
    return error;
}

double coefficientOfDetermination()
{
    double R_sq;
    
    int n= y.size();
    Syy= 0, SSR=0;

    for(int i=0; i<n; i++)
    {
        Syy += (y[i]- y_mean) * (y[i]- y_mean);
        double pred= predictor(x[i]);
        SSR += (y[i]- pred)* (y[i]- pred);
    }
    
    R_sq = 1- (SSR/ Syy);
    return R_sq;
}

void interpretationOfCOD()
{
    double R_sq= coefficientOfDetermination();
    cout << "The Co-efficient of determination is "<< R_sq << endl;
    cout << "So, the model can explain " << 100*R_sq << "% of the variation in the data";
}

void getInput()
{
    freopen("file.txt", "r", stdin);
    int n;
    cin>> n;
    double xi, yi;
    for(int i=0; i<n; i++)
    {
        cin >> xi >> yi;
        x.push_back(xi);
        y.push_back(yi);
    }
}

int main()
{
    getInput();

    cout << "Predicted value at 2060 = " << predictor(2060) << endl;
    interpretationOfCOD();
}