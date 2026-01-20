#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

class NRfunction{
    private:
        double X;

        double fx(){
            return ((pow(X, 2) - (2*X)) + 1);
        }

        double dfx(){
            return 2*X - 2;
        }

    public:
        void SetX(double guess){
            X = guess;
        }

        double getfx(){
            return fx();
        }

        double getdfx(){
            return dfx();
        }
};

int main(){
    double X0, X1, e = pow(10, (-6));
    cout<<"This function finds the solution of a equation using Newton Raphson Method. For that you will have to make a guess."<<endl;
    cout<<"Enter your guess:- ";
    cin>>X0;

    NRfunction one, two;
    one.SetX(X0);
    cout<<setw(8)<<"Sr. no."<<setw(14)<<"X0"<<setw(14)<<"X1"<<setw(14)<<"f(X0)"<<setw(14)<<"f'(X0)"<<setw(14)<<"f(X1)"<<endl;
    int count = 0;
    do
    {
        X1 = (X0 - ((one.getfx())/(one.getdfx())));
        two.SetX(X1);
        cout<<setw(8)<<count<<setw(14)<<X0<<setw(14)<<X1<<setw(14)<<one.getfx()<<setw(14)<<one.getdfx()<<setw(14)<<two.getfx()<<endl;
        count++;

        X0 = X1;
        one.SetX(X0);
        
    } while (abs(two.getfx()) >= e);
    
    cout<<"The solution of the equation x^2 - 2X + 1 = 0 is "<<X1<<endl;

    return 0;
}