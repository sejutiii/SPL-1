#include<iostream>
#include<vector>

using namespace std;

void transpose(vector<vector<double>> &matX, vector<vector<double>> &mat_Xtranspose)
{
    int row= matX.size();
    int col= matX[0].size();

    mat_Xtranspose.resize(col, vector<double> (row));

    for(int i=0; i<col; i++)
    {
        for(int j=0; j<row; j++)
        {
            mat_Xtranspose[i][j]= matX[j][i];
        }
    }
}

void matrixMultiplication(vector<vector<double>> &A, vector<vector<double>> &B, vector<vector<double>> &mat_multiplicationOutput)
{
    int row_A, col_A, row_B, col_B;
    row_A= A.size();
    col_A= A[0].size();

    row_B= B.size();
    col_B= B[0].size();

    if(col_A != row_B)
    {
        cout << "The dimensions are not suitable for multiplication." << endl;
        cout << row_A << "x" << col_A << " " << row_B << "x" << col_B << endl;
        return;
    }

    mat_multiplicationOutput.resize(row_A, vector<double>(col_B));

    for(int i=0; i<row_A; i++)
    {
        for(int j=0; j<col_B; j++)
        {
            double sum=0;
            for(int k=0; k<col_A; k++)
            {
                sum += A[i][k] * B[k][j];
            }
            mat_multiplicationOutput[i][j]= sum;
        }
    }
}

void mat_subtraction(vector<vector<double>> &A, vector<vector<double>> &B, vector<vector<double>> &C)
{
    int row_A, col_A, row_B, col_B;
    row_A= A.size();
    col_A= A[0].size();

    row_B= B.size();
    col_B= B[0].size();

    if(row_A == row_B && col_A == col_B)
    {
        C.resize(row_A, vector<double>(col_A));
        for(int i=0; i<row_A; i++)
        {
            for(int j=0; j<col_A; j++)
            {
                C[i][j]= A[i][j]- B[i][j];
            }
        }
    }
    else cout << "The dimensions are not suitable for subtraction" << endl;
}

void printMat(vector<vector<double>> &A)
{
    int row_A, col_A;
    row_A= A.size();
    col_A= A[0].size();

    for(int i=0; i<row_A; i++)
    {
        for(int j=0; j<col_A; j++)
        {
            cout << A[i][j] <<  " ";
        }
        cout << endl;
    }
}