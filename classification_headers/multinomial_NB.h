#include<bits/stdc++.h>

using namespace std;

vector<pair<string, pair<int, int>>> freqTable; 
vector<string> categories, tags;
vector<pair<double, double>> likelihoodTable;
vector<double> cat_probability, tag_probability;
double allTotal;

bool contains (string word, vector<string> arr)
{
    for(auto cat: arr)
    {
        if(cat == word) return true;
    }
    return false;
}

void createFrequencyTable(vector<vector<string>> dataset)
{
    int numRows= dataset.size();
    allTotal= numRows;
    for(int i=0; i<numRows; i++)
    {
        // For row[0]
        vector<string> row= dataset[i];
        if(contains(row[0], categories) == false)
        {
            categories.push_back(row[0]);
            pair<string, pair<int, int>> temp;
            temp.first= row[0];
            temp.second.first= 0;
            temp.second.second= 0;
            freqTable.push_back(temp);
        }

        // For row[1]
        if(contains(row[1], tags)== false)
        {
            tags.push_back(row[1]);
        }
    }

    for(int i=0; i<numRows; i++)
    {
        vector<string> row= dataset[i];
        string word= row[0];
        string tag= row[1];
        for(auto &pairedRow: freqTable)
        {
            if(pairedRow.first== word)
            {
                if(tag == tags[0])
                {
                    pairedRow.second.first++;
                }
                else if(tag== tags[1])
                pairedRow.second.second++;
            }
        }
    }
}

void createLikelihoodTable()
{
    int count_tag1=0, count_tag2=0;
    for(auto row: freqTable)
    {
        double temp= row.second.first+ row.second.second;
        temp= temp/ allTotal;
        cat_probability.push_back(temp);
        count_tag1 += row.second.first;
        count_tag2 += row.second.second;
    }

    for(auto row: freqTable)
    {
        pair <double, double> temp;
        temp.first= (double) row.second.first/ count_tag1;
        temp.second= (double) row.second.second/ count_tag2;
        likelihoodTable.push_back(temp);
    }

    double temp= count_tag1/allTotal;
    tag_probability.push_back(temp);
    temp= count_tag2/allTotal;
    tag_probability.push_back(temp);
}

void printFreqTable()
{
    for(auto row: likelihoodTable)
    {
        cout << row.first << " " << row.second<< endl; 
    }
}

string posterior_probability(string input)
{
   int cats= freqTable.size();
   double probGiven_tag1, probGiven_tag2;
   for(int i=0; i<cats; i++)
   {
        if(input == freqTable[i].first)
        {
            probGiven_tag1= tag_probability[0]* freqTable[i].second.first/ cat_probability[i];
            probGiven_tag2= tag_probability[1]* freqTable[i].second.second/ cat_probability[i];
            break;
        }
   }
   if(probGiven_tag1 > probGiven_tag2) return tags[0];
   else return tags[1];
}

void prediction_model(vector<string> header)
{
    for(auto word: categories)
    {
        cout<< word<< endl;
    }
    cout<< "Enter the input "<< header[0] << ": ";
    string input, output;
    cin >> input;
    output= posterior_probability(input);
    cout << header[1]<< ": " << output << endl;  
}

void trainingOntheDataset(vector<vector<string>> dataset)
{
    createFrequencyTable(dataset);
    createLikelihoodTable();
    // printFreqTable();
}