#include<bits/stdc++.h>

using namespace std;

void readFile(vector< vector<double> > &dataset, vector<string> &strHeaders)
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

    string header;
    if(getline(file, header))
    {
        istringstream hstream(header);
        string title;
        while(getline(hstream, title, ','))
        {
            strHeaders.push_back(title);
        }

        string line;
        while(getline(file, line))
        {
            istringstream lstream(line);
            vector<double> row;
            double val;
            while(lstream >> val)
            {
                row.push_back(val);
                if(lstream.peek()== ',') lstream.ignore();
            }

            dataset.push_back(row);
        }
    }

    else{
        cerr<< "Error reading file." << endl;
    }

    file.close();
}