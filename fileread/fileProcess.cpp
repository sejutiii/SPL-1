#include<iostream>
#include<stdio.h>
#include<vector>

using namespace std;

int main()
{
    vector< vector<double> > dataset;
    vector< vector<double> > x_array;
    vector <double> y;
    vector<string> parameters;

    int numParameters, numRows;
    FILE *fp= fopen("datafile.txt", "r");

    if(fp == NULL) 
    {
        cout << "Error in opening file"<< endl;
        exit (1);
    }

    fscanf(fp, "%d %d", &numParameters, &numRows);

    //parameters.resize(numParameters);
    //cout << numParameters << " " << numRows << endl;

    for(int i=0; i<numParameters; i++)
    {
        char temp[20];
        fscanf(fp, "%s", temp);
        parameters.push_back(temp);
    }

    dataset.resize(numRows,vector<double>(numParameters));
    x_array.resize(numParameters-1, vector<double> (numRows));
    y.resize(numRows);

    for(int i=0; i<numRows; i++)
    {
        for(int j=0; j<numParameters; j++)
        {
            fscanf(fp, "%lf", &dataset[i][j]);
        }
    }

    fclose(fp);

    // for(int i=0; i<numRows; i++)
    // {
    //     cout << i+1 << " ";
    //     for(int j=0; j<numParameters; j++)
    //     {
    //         cout<< dataset[i][j] << " ";
    //     }
    //     cout<< endl;
    // }

    for(int i=0; i<numParameters; i++)
    {
        if(i== numParameters-1)
        {
            for(int j=0; j<numRows; j++)
            {
                y[j]= dataset[j][i];
            }
        }
        else{
            for(int j=0; j<numRows; j++)
            {
                x_array[i][j]= dataset[j][i];
            }
        }
    }



    // for(int i=0; i<numParameters-1; i++)
    // {
    //     cout<< i+1 << "   ";
    //     for(int j=0; j<numRows; j++)
    //     {
    //         cout<< x_array[i][j] << " ";
    //     }
    //     cout<< endl << endl;
    // }

    //  for(int j=0; j<numRows; j++)
    //     {
    //         cout<< y[j] << " ";
    //     }
    
    //  cout<< endl << endl;
}