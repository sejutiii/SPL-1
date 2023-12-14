#include<bits/stdc++.h> 
#define DIST 10e5

using namespace std;

int numNodes, numFeatures; 
vector<int> testOnFeatures;

int k;

vector<vector<int>> clusters;
vector<int> centroids;
vector<vector<double>> centroidPoints;

vector<double> meanFeatureNode;

bool isACentroid(int index)
{
    for(int x: centroids)
    {
        if(index == x) return true;
    }
    return false;
}

void initializeCentroids(vector< vector<double>> dataset)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(0, numNodes-1);

    centroids.resize(k);
    for(int i=0; i<k; i++)
    {
        int cent = distribution(gen);
        while(isACentroid(cent))
        {
            cent = distribution(gen);
        }
        centroids[i]= cent;
    }
    
    for(int i=0; i<k; i++)
    {
        vector<int> temp;
        temp.push_back(centroids[i]);
       // cout << centroids[i] << endl; 
        clusters.push_back(temp);

        vector<double> centroidFeatures;
        for(int j=0; j<numFeatures; j++)
        {
            double val= dataset[centroids[i]][testOnFeatures[j]];
            centroidFeatures.push_back(val);
        }
        centroidPoints.push_back(centroidFeatures);
    }
}

void initialize (int rows, int columns, vector<vector<double>> dataset)
{
    numNodes= rows;
    cout << "Enter the number of features to base the clustering on: ";
    cin >> numFeatures;
    testOnFeatures.resize(numFeatures);
    cout << "Enter the feature numbers: ";
    int temp;
    for(int i=0; i<numFeatures; i++)
    {
        cin >> temp;
        testOnFeatures[i]= temp-1;
    }

    cout << "Enter the value of k: ";
    cin >> k;

    initializeCentroids(dataset);
}

double euclideanDistance(int centroid_index, int dataPoint_index, vector< vector<double>> dataset)
{
    double sum= 0;
    for(int i=0; i<numFeatures; i++)
    {
        double diff= centroidPoints[centroid_index][i]- dataset[dataPoint_index][testOnFeatures[i]];
        diff = diff* diff;
        sum += diff;
    }
    return sqrt(sum);
}

void updateCentroids(int index, vector< vector<double>> dataset)
{
    int n= clusters[index].size();
   for(int i=0; i<numFeatures; i++)
   {
        double mean= 0;
        for(int j=0; j<n; j++)
        {
            mean += dataset[clusters[index][j]][testOnFeatures[i]];
        }
        mean = mean/n;
        centroidPoints[index][i] = mean;
   }
}

int addToCluster(int point, vector<vector<double>> dataset)
{
    double minDistance= DIST;
    int clusterNum= -1;

    for(int j=0; j<k; j++)
    {
        double distance= euclideanDistance(j, point, dataset);

        if(distance < minDistance)
        {
            minDistance= distance;
            clusterNum= j;
        }
    }
    clusters[clusterNum].push_back(point);
    updateCentroids(clusterNum, dataset);
    return clusterNum;
}

void formClusters(vector<vector<double>> dataset)
{
    for(int i=0; i<numNodes; i++)
    {
        if(isACentroid(i))
            continue;
        addToCluster(i, dataset);
    }
}

void calculateMeanNode(vector<vector<double>> dataset)
{
    for(int i=0; i<numFeatures; i++)
    {
        double mean= 0;
        for(int j=0; j<numNodes; j++)
        {
            mean += dataset[j][testOnFeatures[i]];
        }
        mean = mean/ numNodes;
        meanFeatureNode.push_back(mean);
    }
}

double measureVariation(vector<vector<double>> dataset)
{
    calculateMeanNode(dataset);
    double variance = 0;
    for(int i=0; i<k; i++)
    {
        double sum= 0;
        for(int j=0; j<numFeatures; j++)
        {
            double diff= centroidPoints[i][j]- meanFeatureNode[j];
            diff = diff* diff;
            sum += diff;
        }
        variance += sum;
    }
    variance = variance/ k-1;
    return variance;
}

void printClusters(vector<vector<double>> dataset)
{
    cout << endl;
    int count =1;
    for(auto cluster: clusters)
    {
        cout << "Cluster- " << count<< " : " <<endl;
        for(auto cl: cluster)
        {
            cout << cl << " ";
        }
        cout << endl << endl << endl;
        count++;
    }

    cout << endl << "variance= " << measureVariation(dataset) << endl << endl;
}

void KmeansTrainingModel(int rows, int columns, vector<vector<double>> dataset)
{
    formClusters(dataset);
}

void add_new_dataPoint(int columns, vector< vector<double> > &dataset, vector<string> strHeaders)
{
    cout << endl << "Enter the values for the new node: " << endl << endl;
    vector<double> tempRow;
    for(int i=0; i<columns; i++)
    {
        double temp;
        cout << "For " << strHeaders[i] << " : ";
        cin >> temp;
        tempRow.push_back(temp);
    }
    dataset.push_back(tempRow);
    numNodes++;
}

void assign_newPoint_toCluster(int columns, vector< vector<double> > &dataset, vector<string> strHeaders)
{
    add_new_dataPoint(columns, dataset, strHeaders);
    int clusterNum= addToCluster(numNodes-1, dataset);
    cout << endl << "The data point was added to cluster- " << clusterNum+1 << endl;
}