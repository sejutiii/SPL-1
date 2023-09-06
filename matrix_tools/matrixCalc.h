#include<iostream>
#include<vector>

using namespace std;

vector< vector<double> > matX;
vector <vector<double>> matY;
vector< vector<double> > mat_Xtranspose;
vector< vector<double> > mat_multiplicationOutput;

void transpose()
{
    int row= matX.size();
    int col= matX[0].size();

    mat_Xtranspose.resize(col, vector<double> (row));

    for(int i=0; i<col; i++)
    {
        //cout << "it = " << i+1 << endl; // tbd;
        for(int j=0; j<row; j++)
        {
            mat_Xtranspose[i][j]= matX[j][i];
           // cout <<  mat_Xtranspose[i][j] << " "; //tbd
        }
        //cout << endl;
    }
}

void matrixMultiplication(vector< vector<double> > A, vector< vector<double> > B)
{
    int row_A, col_A, row_B, col_B;
    row_A= A.size();
    col_A= A[0].size();

    row_B= B.size();
    col_B= B[0].size();

    if(col_A != row_B)
    {
        cout << "The dimensions are not suitable for multiplication." << endl;
        return;
    }

    mat_multiplicationOutput.resize(row_A, vector<double>(col_B));

    cout << row_A << " " << col_B << endl;

    for(int i=0; i<row_A; i++)
    {
       // cout << "it = " << i+1 << " "; // tbd;
        for(int j=0; j<col_B; j++)
        {
            double sum=0;
            for(int k=0; k<col_A; k++)
            {
                sum += A[i][k] * B[k][j];
            }
            mat_multiplicationOutput[i][j]= sum;
           //cout <<  mat_multiplicationOutput[i][j] << " "; // tbd
        }
        //cout << endl;
    }
}

// int main()
// {
//     int row, col;
//     cout << "Enter the dimensions of the matrix: ";
//     cin >> row >> col;

//     // vector< vector<double> > x;
//     matX.resize(row, vector<double>(col));
//     cout << "Enter the input matrix:" << endl;
//     for (int i = 0; i < row; i++) {
//         for (int j = 0; j < col; j++) {
//             cin >> matX[i][j];
//         }
//     }

//     //transpose();

//     for (int i = 0; i < col; i++) {
//         for (int j = 0; j < row; j++) {
//             cout << mat_Xtranspose[i][j] << " ";
//         }
//         cout << endl;
//     }
// }