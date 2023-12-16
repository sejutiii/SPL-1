#include<bits/stdc++.h>

using namespace std;

void readTextFile(vector<vector<string>> &dataset, vector<string> &strHeaders)
{
    string filename;
    cout << "Enter the input file name (csv): ";
    cin >> filename;

    ifstream file(filename);
    if(!file.is_open())
    {
        cerr << "Error opening in file." << endl;
        exit(1);
    }

    string line;
    if (getline(file, line)) {
        stringstream ss(line);
        string token;

        while (getline(ss, token, ',')) {
            strHeaders.push_back(token);
        }

        while (getline(file, line)) {
            stringstream ss(line);
            vector<string> row;

            while (getline(ss, token, ',')) {
                row.push_back(token);
            }

            dataset.push_back(row);
        }
    }

    else{
        cerr<< "Error reading file." << endl;
    }

    file.close();
}