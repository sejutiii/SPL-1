#include<bits/stdc++.h>

using namespace std;

void readTextFile(vector<vector<string>> &dataset, vector<string> &headers)
{
    int numRow, numColumn;
    cout << "Enter the number of rows and columns: ";
    cin >> numRow >> numColumn;

    char filename[100];
    cout << "Enter the file name: ";
    cin >> filename;

    FILE *fp= fopen(filename, "r");

    if(fp == NULL) 
    {
        cout << "Error in opening file"<< endl;
        exit (1);
    }

    for(int i=0; i<numColumn; i++)
    {
        char temp[50];
        fscanf(fp, "%s", temp);
        headers.push_back(temp);
    }


    for(int i=0; i<numRow; i++)
    {
        vector<string> row;
        for(int j=0; j<numColumn; j++)
        {
            char temp[50];
            fscanf(fp, "%s", temp);
            row.push_back(temp);
        }
        dataset.push_back(row);
    }
}