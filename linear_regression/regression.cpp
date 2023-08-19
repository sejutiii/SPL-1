#include<iostream>
#include<stdio.h>
#include<vector>

using namespace std;

vector <float> x;
vector <float> y;
float slope, intercept;
float sumXY, sumX, sumY, sumX_square, sumY_square;

void calculateSlope()
{
    float N= x.size();
    float numerator= (N* sumXY - (sumX * sumY));
    float denominator= (N* sumX_square - (sumX * sumX));
    slope= numerator/ denominator;
}

void calculateIntercept()
{
    float N = x.size();
    float numerator = (sumY * sumX_square - sumX * sumXY);
    float denominator = (N * sumX_square - sumX * sumX);
    intercept = numerator / denominator;
}

int sizeOfData()
{
    return x.size();
}

float getSlope()
{
    if(slope== 0) calculateSlope();
    return slope;
}

float getIntercept()
{
    if(intercept== 0) calculateIntercept();
    return intercept;
}

void getInput(int n)
{
    for (int i = 0; i < n; i++) 
    {
        float xi;
        float yi;
        cin >> xi >> yi;
        sumXY += xi * yi;
        sumX += xi;
        sumY += yi;
        sumX_square += xi * xi;
        sumY_square += yi * yi;
        x.push_back(xi);
        y.push_back(yi);
    }
}

float predict(float x)
{
    getSlope();
    getIntercept();
    return (slope*x) + intercept;
}

float errorSquare()
{
    float ans = 0;
    for (int i = 0; i < x.size(); i++) 
    {
        float temp= (predict(x[i]) - y[i]);
        ans += temp * temp ;
    }
    return ans;
}

float errorIn(float num)
{
    for (int i = 0; i < x.size(); i++) 
    {
        if (num == x[i]) {
            return (y[i] - predict(x[i]));
        }
    }
    return 0;
}

int main()
{
    freopen("file.txt", "r", stdin);
 
    int n;
    cin >> n;
 
    getInput(n);

    cout << "Predicted value at 2060 = " << predict(2060) << endl;
    cout << "The errorSquared  = " << errorSquare() << endl;
    cout << "Error in 2050 = " << errorIn(2050) << endl;
}