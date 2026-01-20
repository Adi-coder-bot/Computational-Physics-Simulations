#include<iostream>
#include<vector>
#include<iomanip>
#include<cmath>
using namespace std;

void displayM(vector<vector<double>> A){
    for (size_t i = 0; i < A.size(); i++)
    {
        cout<<"|";
        for (size_t j = 0; j < A[i].size(); j++)
        {
            if (j == 0)
            {
                cout<<fixed<<setprecision(4)<<setw(8)<<A[i][j];
            }
            else
            {
                cout<<fixed<<setprecision(4)<<setw(10)<<A[i][j];
            }
            
        }
        cout<<"|"<<endl;
    }
}

vector<vector<double>> Matrixform(int R, int C){
    vector<vector<double>> matrix;
    for (size_t i = 0; i < R; i++)
    {
        vector<double> row;
        for (size_t j = 0; j < C; j++)
        {
            double element;
            cout<<"Enter the element at row number "<<i + 1<<" and column number "<<j + 1<<" :- ";
            cin>>element;
            row.push_back(element);
        }
        matrix.push_back(row);
    }
    return matrix;
}

vector<vector<double>> Maddition(vector<vector<double>> A, vector<vector<double>> B){
    vector<vector<double>> C;
    for (size_t i = 0; i < A.size(); i++)
    {
        vector<double> r;
        for (size_t j = 0; j < A[i].size(); j++)
        {
            r.push_back(A[i][j] + B[i][j]);
        }
        C.push_back(r);
    }
    return C;
}

vector<vector<double>> Msubtraction(vector<vector<double>> A, vector<vector<double>> B){
    vector<vector<double>> C;
    for (size_t i = 0; i < A.size(); i++)
    {
        vector<double> r;
        for (size_t j = 0; j < A[i].size(); j++)
        {
            r.push_back(A[i][j] - B[i][j]);
        }
        C.push_back(r);
    }
    return C;
}

vector<vector<double>> Mmultiplication(vector<vector<double>> A, vector<vector<double>> B){
    vector<vector<double>> C;
    for (size_t i = 0; i < A.size(); i++)
    {
        vector<double> r;
        for (size_t j = 0; j < B[0].size(); j++)
        {
            double sum = 0;
            for (size_t k = 0; k < A[0].size(); k++)
            {
                sum += A[i][k] * B[k][j];
            }
            r.push_back(sum);
        }
        C.push_back(r);
    }
    return C;
}

double Mdeterminant(vector<vector<double>> A){
    if (A.size() == 1)
    {
        return A[0][0];
    }
    else if (A.size() == 2)
    {
        return ((A[0][0]*A[1][1]) - (A[0][1]*A[1][0])); 
    }
    else
    {
        int columnN = 0, sign = 1;
        double sum = 0;
        while (columnN < A[0].size())
        {
            vector<vector<double>> NM;
            for (size_t i = 1; i < A.size(); i++)
            {
                vector<double> r;
                for (size_t j = 0; j < A[i].size(); j++)
                {
                    if (columnN != j)
                    {
                        r.push_back(A[i][j]);
                    }
                }
                NM.push_back(r);
            }
            
            double det = Mdeterminant(NM);
            sum += ((A[0][columnN] * det) * sign);
            sign = -sign;
            columnN++;
        }
        return sum;
    }
}

vector<vector<double>>Mtranspose(vector<vector<double>> A){
    vector<vector<double>> C;
    for (size_t i = 0; i < A[0].size(); i++)
    {
        vector<double> r;
        for (size_t j = 0; j < A.size(); j++)
        {
            r.push_back(A[j][i]);
        }
        C.push_back(r);
    }
    return C;
}

vector<vector<double>> Mcofactor(vector<vector<double>> A){
    vector<vector<double>> C;
    int RN = 0, CN = 0;
    double sum = 0;
    while (RN < A.size())
    {
        vector<double> R;
        while (CN < A[0].size())
        {
            vector<vector<double>> NM;
            for (size_t i = 0; i < A.size(); i++)
            {
                if (i == RN)
                {
                    continue;
                }
                else
                {
                    vector<double> r;
                    for (size_t j = 0; j < A[i].size(); j++)
                    {
                        if (CN != j)
                        {
                            r.push_back(A[i][j]);
                        }
                    }
                    NM.push_back(r);
                }
            }
            R.push_back(pow(-1, (RN + CN))*Mdeterminant(NM));
            CN++;
        }
        CN = 0;
        C.push_back(R);
        RN++;
    }
    return C;
}

vector<vector<double>> Mscamul(vector<vector<double>> A, double scalar){
    vector<vector<double>> C;
    for (size_t i = 0; i < A.size(); i++)
    {
        vector<double> r;
        for (size_t j = 0; j < A[0].size(); j++)
        {
            r.push_back(scalar*A[i][j]);
        }
        C.push_back(r);
    }
    return C;
}

vector<vector<double>> Minverse(vector<vector<double>> A){
    return Mscamul(Mtranspose(Mcofactor(A)), (1/Mdeterminant(A)));
}

int main(){
    int rowno, columnno;

start1:
    cout<<"This Program will perform operations on matrices that you enter.\n Enter the number of rows in the matrix:- ";
    cin>>rowno;
    if (rowno == 0)
    {
        cout<<"A matrix cannot have 0 rows."<<endl;
        goto start1;
    }
    
start2:
    cout<<"Enter the number of columns in the matrix:- ";
    cin>>columnno;
    if (columnno == 0)
    {
        cout<<"A matrix cannot have 0 columns."<<endl;
        goto start2;
    }
    
    vector<vector<double>> M1, M2;

    M1 = Matrixform(abs(rowno), (columnno));

    char option;
    cout<<"Enter the operation you want to perform on it (Enter '+' for addition, '-' for subtraction, '*' for multiplication, 's or S' for Scalar multiplication, 'd or D' for Determinant, 't or T' for Transposition, 'i or I' for Inverse and enter anything else to exit.):- "<<endl;
    cin>>option;

    switch (tolower(option))
    {
    case '+':
    {
        int r1, c1;

sp1:
        cout<<"Enter the number of rows for the other matrix:- ";
        cin>>r1;
        if (r1 == 0)
        {
            cout<<"A matrix cannot have 0 rows."<<endl;
            goto sp1;
        }

sp2:
        cout<<"Enter the number of columns for the other matrix:- ";
        cin>>c1;
        if (c1 == 0)
        {
            cout<<"A matrix cannot have 0 columns."<<endl;
            goto sp2;
        }
        M2 = Matrixform(r1, c1);

        if (M1.size() == M2.size() && M1[0].size() == M2[0].size())
        {
            cout<<"The addition of the two matrices you entered is,"<<endl;
            displayM(Maddition(M1, M2));
        }
        else
        {
            cout<<"Addition cannot be performed, as number of rows and number of columns of both the matrices is not same."<<endl;
        }
    }
        break;
        
    case '-':
    {
        int r1, c1;

ss1:
        cout<<"Enter the number of rows for the other matrix:- ";
        cin>>r1;
        if (r1 == 0)
        {
            cout<<"A matrix cannot have 0 rows."<<endl;
            goto ss1;
        }

ss2:
        cout<<"Enter the number of columns for the other matrix:- ";
        cin>>c1;
        if (c1 == 0)
        {
            cout<<"A matrix cannot have 0 columns."<<endl;
            goto ss2;
        }
        M2 = Matrixform(r1, c1);
        
        if (M1.size() == M2.size() && M1[0].size() == M2[0].size())
        {
            cout<<"The subtraction of the two matrices you entered is,"<<endl;
            displayM(Msubtraction(M1, M2));
        }
        else
        {
            cout<<"Subtraction cannot be performed, as number of rows and number of columns of both the matrices is not same."<<endl;
        }
    }   
        break;
        
    case '*':
    {
        int r1, c1;

sm1:
        cout<<"Enter the number of rows for the other matrix:- ";
        cin>>r1;
        if (r1 == 0)
        {
            cout<<"A matrix cannot have 0 rows."<<endl;
            goto sm1;
        }

sm2:
        cout<<"Enter the number of columns for the other matrix:- ";
        cin>>c1;
        if (c1 == 0)
        {
            cout<<"A matrix cannot have 0 columns."<<endl;
            goto sm2;
        }
        M2 = Matrixform(r1, c1);
        
        if (M1[0].size() == M2.size())
        {
            cout<<"The multiplication of the two matrices you entered is,"<<endl;
            displayM(Mmultiplication(M1, M2));
        }
        else
        {
            cout<<"Multiplication cannot be performed, as number of rows of 2nd matrix is not equal to the number of columns of 1st matrix."<<endl;
        }
    }
        break;

    case 's':
    {
        double S;
        cout<<"Enter the scalar you want to multiply with the matrix:- ";
        cin>>S;
        
        cout<<"The multiplication of the scalar with the matrix you entered is,"<<endl;
        displayM(Mscamul(M1, S));
        
    }
        break;

    case 'd':
    {
        if (M1.size() == M1[0].size())
        {
            cout<<"The determinant of the matrix you entered is "<<Mdeterminant(M1)<<endl;
        }
        else
        {
            cout<<"Determinant cannot be found as the matrix is not square."<<endl;
        }
    }
        break;

    case 't':
    {
        cout<<"The transpose of the matrix you entered is,"<<endl;
        displayM(Mtranspose(M1));
    }
        break;

    case 'i':
    {
        double determinant = Mdeterminant(M1);
        if ((M1.size() == M1[0].size()) && (determinant != 0))
        {
            cout<<"The inverse of the matrix you entered is,"<<endl;
            displayM(Minverse(M1));
        }
        else
        {
            cout<<"Inverse of this matrix doesn't exist. As it is a non-invertible matrix, because its determinant is 0."<<endl;
        }
    }
        break;

    default:
        cout<<"Thankyou for using this program!"<<endl;
        break;
    }
    return 0;
}