#include<iostream>
#include<vector>
#include<iomanip>
#include<random>
#include<ctime>
using namespace std;

double Determinant(vector<vector<double>> M){
    if (M.size() == 1)
    {
        return M[0][0];
    }
    else if (M.size() == 2)
    {
        return M[0][0]*M[1][1]-M[0][1]*M[1][0];
    }
    else
    {
        int columnN = 0;
        int sign = 1;
        double sum = 0;
        while (columnN < M[0].size())
        {
            vector<vector<double>> N;
            for (size_t k = 1; k < M.size(); k++)
            {
                vector<double> r1;
                for (size_t l = 0; l < M[k].size(); l++)
                {
                    if (l != columnN)
                    {
                        r1.push_back(M[k][l]);
                    }
                }
                N.push_back(r1);
            }
            
            double det = Determinant(N);
            sum += M[0][columnN]*det*sign;
            sign = -sign;
            columnN++;
        }
        return sum;
    }
}

int main(){
    size_t order;
    cout<<"This Program is supposed to find the determinant of a square matrix of any order that yout enter.\nSo, enter the order of matrix:- (3 for 3x3, 2 for 2x2, etc.):- ";
    cin>>order;

    vector<vector<double>> matrix;
    if (order < 4)
    {
        cout<<"Now, Enter the elements."<<endl;
        double element;
    
        for (size_t i = 0; i < order; i++)
        {
            vector<double> row;
            for (size_t j = 0; j < order; j++)
            {
                cout<<"Enter the element at row number "<<i + 1<<" and column number "<<j + 1<<" :- ";
                cin>>element;
                row.push_back(element);
            }
            matrix.push_back(row);
        }
    }
    else if (order >= 4 && order <=10)
    {
        mt19937 a(static_cast<unsigned int>(time(0)));
        uniform_real_distribution<double> num(-99, 99);
        
        for (size_t i = 0; i < order; i++)
        {
            vector<double> row;
            for (size_t j = 0; j < order; j++)
            {
                double r = num(a);
                row.push_back(r);
            }
            matrix.push_back(row);
        }

        cout<<"The random matrix is :- "<<endl;
        for (size_t m = 0; m < matrix.size(); m++)
        {
            cout<<"|";
            for (size_t n = 0; n < matrix[m].size(); n++)
            {
                cout<<fixed<<setprecision(2)<<setw(8)<<matrix[m][n];
            }
            cout<<"|"<<endl;
        }
        
    }
    else
    {
        cout<<"This order is too large and will take a lot of time, so, the program will be terminated."<<endl;
        return 0;
    }
    
    cout<<"The determinant of the "<<order<<" X "<<order<<" matrix is "<<Determinant(matrix)<<endl;
    return 0;   
}