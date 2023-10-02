#include<bits/stdc++.h>

using namespace std;

int numRow, numColumn;
bool strHeader= false;

void readFile(vector< vector<double> > &dataset, vector<string> &strHeaders)
{
    cout << "Enter the number of rows and columns: " << endl;
    cin >> numRow >> numColumn ;

    if(numColumn < 2)
    {
        cout << "At least 2 columns are required. " << endl;
        exit(1);
    }

    char checker;
    cout << "Does the dataset contain any string headers? (y/n): ";
    cin >> checker;
    if(checker== 'y' || checker =='Y')
    {
        strHeader= true;
    }

    FILE *fp= fopen("data.txt", "r");

    if(fp == NULL) 
    {
        cout << "Error in opening file"<< endl;
        exit (1);
    }

    if(strHeader == true)
    {
        for(int i=0; i<numColumn; i++)
        {
            char temp[50];
            fscanf(fp, "%s", temp);
            strHeaders.push_back(temp);
        }
    }

    dataset.resize(numRow,vector<double>(numColumn));
    for(int i=0; i<numRow; i++)
    {
        for(int j=0; j<numColumn; j++)
        {
            fscanf(fp, "%lf", &dataset[i][j]);
        }
    }

    fclose(fp);  
}