#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

class equation{
    private:
        float X;

        float equ(){
            return pow(X, 2) - 25; 
        }

    public:
        void SetX(double val){
            X = val;
        }

        double fx(){
            return equ();
        }
};

int main(){
    float guess1, guess2, e = pow(10, -6);
    cout<<"This Program will find the root of a equation using two guesses that you provide with the help of False Position method."<<endl;

start:

    cout<<"Enter the 1st guess:- ";
    cin>>guess1;
    cout<<"Enter the 2nd guess:- ";
    cin>>guess2;

    equation one, two, New, M, P;
    one.SetX(guess1);
    two.SetX(guess2);

    if (abs(one.fx()) <= e)
    {
        cout<<guess1<<" is the root of the equ x^2 - 25"<<endl;
    }
    else if (abs(two.fx()) <= e)
    {
        cout<<guess2<<" is the root of the equ x^2 - 25"<<endl;
    }
    else if ((one.fx() < 0 && two.fx() < 0) || (one.fx() >= 0 && two.fx() >= 0))
    {
        cout<<"The Entered guess values will not work for this method. Try other values."<<endl;
        goto start;
    }
    else
    {
        float Xm, Xp, Xnew;
        if (one.fx() < 0)
        {
            Xm = guess1;
            Xp = guess2;
        }
        else
        {
            Xm = guess2;
            Xp = guess1;
        }
        
        bool root = false;
        int count = 0;
        cout<<setw(8)<<"Sr.no."<<setw(14)<<"Xm"<<setw(14)<<"Xp"<<setw(14)<<"Xnew"<<setw(14)<<"f(Xm)"<<setw(14)<<"f(Xp)"<<setw(14)<<"f(Xnew)"<<endl;
        while (root != true)
        {
            M.SetX(Xm);
            P.SetX(Xp);
            Xnew = (P.fx()*Xm - M.fx()*Xp)/(P.fx() - M.fx());
            New.SetX(Xnew);
            cout<<setw(8)<<count<<setw(14)<<Xm<<setw(14)<<Xp<<setw(14)<<Xnew<<setw(14)<<M.fx()<<setw(14)<<P.fx()<<setw(14)<<New.fx()<<endl;
            
            if (New.fx() < 0)
            {
                Xm = Xnew;
            }
            else
            {
                Xp = Xnew;
            }
            
            count++;

            if (abs(New.fx()) <= e)
            {
                root = true;
            }
            
        }

        cout<<"The root of the equation x^2 - 25 is "<<Xnew<<endl;
         
    }
    
    return 0;
}