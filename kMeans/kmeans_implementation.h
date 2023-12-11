#include<bits/stdc++.h>
#include"../kMeans/kmeansHeader.h"

void kMeansClustering(int rows, int columns, vector< vector<double> > &dataset, vector<string> &strHeaders)
{
    initialize(rows, columns, dataset);
    KmeansTrainingModel(rows, columns, dataset);

    bool flag= true;
    while(flag)
    {
        int choice;
        cout << "Do you want to (Enter any other number to quit)- " << endl;
        cout << "1. print the clusters" << endl;
        cout << "2. Test for a new data point" << endl;
        cout << "3. Run the Algorithm again" << endl;

        switch(choice)
        {
            case 1: printClusters(dataset);
            break;
            case 2: assign_newPoint_toCluster(columns, dataset, strHeaders);
            break;
            case 3: KmeansTrainingModel(rows, columns, dataset);
            break;
            default: 
            flag = false;
        }

    }
}