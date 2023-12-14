#include<bits/stdc++.h>

using namespace std;

vector<vector<vector<double>>> KNN_clusters;
int KNN_k;
int KNN_numFeatures;
int KNN_target;
vector<int> KNN_features;
vector<double> KNN_targetRow;
vector<double> new_dataPoint;

vector<pair<double, int>> KNN_distances;

bool isInTargetRow(double val)
{
    for(int i=0; i<KNN_targetRow.size(); i++)
    {
        if(KNN_targetRow[i]== val) return true;
    }
    return false;
}

int getCategories(int rows, vector<vector<double>> dataset)
{
    int categories =0;
    for(int i=0; i<rows; i++)
    {
        if(!isInTargetRow(dataset[i][KNN_target]))
        {
            categories++;
            KNN_targetRow.push_back(dataset[i][KNN_target]);
        }
    }
    return categories;
}

void KNN_classify(int rows, int columns, vector<vector<double>> dataset)
{
    int categories= getCategories(rows, dataset);
    //KNN_clusters.resize(categories);
   for(int i=0; i<categories; i++)
   {
        vector<vector<double>> temp;
        KNN_clusters.push_back(temp);
   }
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<categories; j++)
        {
            if(dataset[i][KNN_target]== KNN_targetRow[j])
            {
                KNN_clusters[j].push_back(dataset[i]);
                break;
            }
        }
    }
}

void KNN_printClusters()
{
    cout << endl << "------------------------------------------------ KNN Clusters Table -------------------------------------------" << endl;
    for(int i=0; i<KNN_targetRow.size(); i++)
    {
        cout << "---------------------------------------------------------------------------------------------------------------" << endl << endl;
        cout << "Group- " << i+1 << ": "<< KNN_clusters[i].size() << endl << endl;
        for(int j=0; j<KNN_clusters[i].size(); j++)
        {
            for(auto data: KNN_clusters[i][j])
            {
                cout << data << " ";
            }
            cout << endl;
        }
        cout << endl << endl << endl;
    }
    cout << "---------------------------------------------------------------------------------------------------------------" << endl;
}

void KNN_initialize(int rows, int columns, vector<vector<double>> dataset)
{
    cout << "Enter the target column for classification: ";
    cin >> KNN_target;
    KNN_target--;

    cout << "Enter the number of columns (features) to base the classification on: ";
    cin >> KNN_numFeatures;

    int temp;
    cout << "Enter the feature columns: ";
    for(int i=0; i<KNN_numFeatures; i++)
    {
        cin >> temp;
        KNN_features.push_back(temp-1);
    }

    KNN_k = ceil (sqrt(rows));
    if(KNN_k%2 == 0) KNN_k--;
    cout << endl << "For this dataset, default k= " << KNN_k << endl << endl;
    char choice;
    cout << "Do you want to update the value of k (y/n)? ";
    cin >> choice;
    if(choice== 'y' || choice == 'Y') 
    {
        cout << "Enter the value of k: ";
        cin >> KNN_k;
    }
    if(KNN_k%2 == 0) KNN_k--;
}

void add_newPoint(int rows, int columns, vector< vector<double> >dataset, vector<string>strHeaders)
{
    cout << "Enter the values for the new data point- " << endl;
    new_dataPoint.clear();
    for(int i=0; i<columns; i++)
    {
        if(i == KNN_target)
        {
            new_dataPoint.push_back(-1);
            continue;
        }
        double temp;
        cout << strHeaders[i] << ": ";
        cin >> temp;
        new_dataPoint.push_back(temp);
    }
}

double KNN_euclideanDistance(int index, vector< vector<double> >dataset)
{
    double distance= 0;
    for(int i=0; i<KNN_numFeatures; i++)
    {
        double diff= dataset[index][KNN_features[i]]- new_dataPoint[KNN_features[i]];
        diff = diff*diff;
        distance += diff;
    }
    return sqrt(distance);
}

void calculate_distance(int rows, vector< vector<double> >dataset)
{
    for(int i=0; i<rows; i++)
    {
        pair<double, int> temp;
        double distance= KNN_euclideanDistance(i, dataset);
        temp.first= distance;
        temp.second= i;
        KNN_distances.push_back(temp);
    }
}

int maxCount_cluster(vector<vector<double>>dataset, vector<int>&count)
{
    int categories= KNN_targetRow.size();    
    count.resize(categories);
    for(int i=0; i<categories; i++)
    {
        count[i]= 0;
    }

    for(int i=0; i<KNN_k; i++)
    {
        for(int j=0; j<categories; j++)
        {
            if(dataset[KNN_distances[i].second][KNN_target]== KNN_targetRow[j])
            {
                count[j]++;
                break;
            }
        }
    }

    int max= -1, index= -1;
    for(int i=0; i<categories; i++)
    {
        if(count[i] > max)
        {
            max= count[i];
            index= i;
        }
    }
    return index;
}

void classify_newPoint(int rows, vector< vector<double> >dataset)
{
    calculate_distance(rows, dataset);
    sort(KNN_distances.begin(), KNN_distances.end());
    vector<int> count;
    int max_index= maxCount_cluster(dataset, count);
    cout << endl << "------------------------------------------------ KNN Output Value -------------------------------------------" << endl;
    cout << "The new data point falls in group-" << max_index+1;
    cout << " with target value " << KNN_targetRow[max_index] << " and count " << count[max_index] << "/" << KNN_k << endl;
    cout << "---------------------------------------------------------------------------------------------------------------" << endl;
}