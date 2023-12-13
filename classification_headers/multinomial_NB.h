#include<bits/stdc++.h>

using namespace std;

int MNB_numfeatures, MNB_target;
vector<int> MNB_features;
vector<vector<pair <string, vector<int>>>> MNB_freqTable; /*
x1 -> [c1, [t1_count_c1, t2_count1, ...]], [c2, [t1_count_c2, t2_count2, ...]], ...
x2 -> [c1, [t1_count_c1, t2_count1, ...]], [c2, [t1_count_c2, t2_count2, ...]], ...
...
*/
vector< pair <string, int>> MNB_target_freq; //frequency table for target variable
int MNB_target_cats; // number of categories in the target column
vector<string> MNB_target_tags; // the string values for the target categories
vector<double> MNB_prior_probabilities, MNB_posterior_probabilities;
vector<vector<double>> MNB_likelihoodTable;
/*
    x1 -> P(c|t1), P(c|t2), ...
    x2 -> P(c|t1), P(c|t2), ...
    ...
*/
double allTotal;

vector<string> MNB_new_datapoint;

int containsIn(string word, vector<string> arr)
{
    for(int i=0; i<arr.size(); i++)
    {
        if(arr[i]== word) return i;
    }
    return -1;
}

void makeTarget_frequencyTable(int rows, vector<vector<string>> dataset)
{
    for(int j=0; j<rows; j++)
    {
        int index = containsIn(dataset[j][MNB_target], MNB_target_tags);
        if(index == -1)
        {
            MNB_target_tags.push_back(dataset[j][MNB_target]);
            pair<string, int> temp;
            temp.first= dataset[j][MNB_target];
            temp.second= 1;
            MNB_target_freq.push_back(temp);
        }
        else{
            MNB_target_freq[index].second++;
        }
    }
    MNB_target_cats= MNB_target_tags.size();
}

void createFrequencyTable(int rows, int columns, vector<vector<string>> dataset)
{   
    allTotal= rows;
    makeTarget_frequencyTable(rows, dataset);
    for(int i=0; i<MNB_numfeatures; i++)
    {
        vector<pair <string, vector<int>>> feature_cats;
        vector<string> cat;
        for(int j=0; j<rows; j++)
        {
            int index = containsIn(dataset[j][MNB_features[i]], cat);
            int targetIndex= containsIn(dataset[j][MNB_target], MNB_target_tags);
            if(index == -1)
            {
                cat.push_back(dataset[j][MNB_features[i]]);
                pair<string, vector<int>> temp;
                temp.first= dataset[j][MNB_features[i]];
                temp.second.resize(MNB_target_cats);
                temp.second[targetIndex]++;
                feature_cats.push_back(temp);
            }
            else{
                feature_cats[index].second[targetIndex]++;
            }
        }
        MNB_freqTable.push_back(feature_cats);
    }
}

bool isDiscrete(int rows, int index, vector<vector<string>>dataset)
{
    vector<string> temp;
    int range = ceil(sqrt(rows));
    range = range*2;
    for(int i=0; i<rows; i++)
    {
        if(containsIn(dataset[i][index], temp)== -1)
            temp.push_back(dataset[i][index]);
    }
    if(temp.size()> 0 && temp.size() <= range) return true;
    else return false;
}

void initialize_BayesTable(int rows, int columns, vector<vector<string>>dataset, vector<string>strHeaders)
{
    cout << endl << "The dataset contains the following columns: " << endl;
    int i=1;
    for(auto a: strHeaders)
    {
        cout << i << ". " << a << endl;
        i++;
    }
    cout << endl;
    cout << "Enter the target column: ";
    cin >> MNB_target;
    MNB_target--;
    if(!isDiscrete(rows, MNB_target, dataset))
    {
        cout << "Cannot perform Naive Bayes classification since the dataset is not discrete" << endl;
        exit(1);
    }
    cout << "Enter the number of features to classify on (Must contain discrete/ categorical values): ";
    cin >> MNB_numfeatures;
    cout << "Enter the feature columns: ";
    for(int i=0; i<MNB_numfeatures; i++)
    {
        int index;
        cin >> index;
        index--;
        if(isDiscrete(rows, index, dataset))
        {
            MNB_features.push_back(index);
        }
        else cout<< endl << strHeaders[index] << " contains continuous variables." << endl << endl;
    }
    MNB_numfeatures= MNB_features.size();
}

void printFreqTable(vector<string>strHeaders)
{
    cout << endl << "------------------------------------- Frequency Table -----------------------------------------" << endl << endl;
    cout<< "Output column contains: ";
    for(auto a: MNB_target_tags)
    {
        cout << a << " ";
    }
    cout << endl << endl;
    for(int i=0; i<MNB_numfeatures; i++)
    {
        cout << "For " << strHeaders[MNB_features[i]] << ": " << endl;
        for(int j=0; j<MNB_freqTable[i].size(); j++)
        {
            cout << MNB_freqTable[i][j].first << ": ";
            for(int k=0; k<MNB_target_cats; k++)
            {
                cout << MNB_freqTable[i][j].second[k] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}

void calculate_prior_probability()
{
    for(int i=0; i<MNB_target_cats; i++)
    {
        double p= MNB_target_freq[i].second/ allTotal;
        MNB_prior_probabilities.push_back(p);
    }
}

void calculate_likelihoodTable()
{
    for(int i=0; i<MNB_numfeatures; i++)
    {
        vector<double> temp;
        for(int j=0; j<MNB_freqTable[i].size(); j++)
        {
            if(MNB_freqTable[i][j].first == MNB_new_datapoint[i])
            {
                for(int k=0; k<MNB_target_cats; k++)
                {
                    double probability= MNB_freqTable[i][j].second[k]/ MNB_target_freq[k].second;
                    temp.push_back(probability);
                }
                break;
            }
        }
        MNB_likelihoodTable.push_back(temp);
    }
}

void calculate_posterior_probability()
{
    for(int i=0; i<MNB_target_cats; i++)
    {
        double p= 1;
        for(int j=0; j<MNB_numfeatures; j++)
        {
            p *= MNB_likelihoodTable[j][i];
        }
        p*= MNB_prior_probabilities[i];
        MNB_posterior_probabilities.push_back(p);
    }
}

void MNB_addNew_datapoint(vector<string>strHeaders)
{
    MNB_new_datapoint.clear();
    cout << "Enter the input values: " << endl;
    for(int i=0; i<MNB_numfeatures; i++)
    {
        string temp;
        cout << strHeaders[MNB_features[i]] << "(" << MNB_freqTable[i][0].first;
        for(int j=1; j<MNB_freqTable[i].size(); j++)
        {
            cout << "/ " << MNB_freqTable[i][j].first;
        }
        cout << ") : ";
        cin >> temp;
        MNB_new_datapoint.push_back(temp);
    }
}

void print_output_for_Newpoint(vector<string>strHeaders)
{
    double max = -1;
    int index= -1;
    for(int i=0; i<MNB_target_cats; i++)
    {
        if(MNB_posterior_probabilities[i] > max)
        {
            max= MNB_posterior_probabilities[i];
            index= i;
        }
    }
    cout << endl << strHeaders[MNB_target] << ": " << MNB_target_tags[index] << endl << endl;
}

void processingtheDataset(int rows, int columns, vector<vector<string>> dataset, vector<string>strHeaders)
{
    initialize_BayesTable(rows, columns, dataset, strHeaders);
    createFrequencyTable(rows, columns, dataset);
    calculate_prior_probability();
}

void predict_for_a_newPoint(vector<string>strHeaders)
{
    MNB_addNew_datapoint(strHeaders);
    calculate_likelihoodTable();
    calculate_posterior_probability();
    print_output_for_Newpoint(strHeaders);
}