#include<iostream>
#include<random>
#include<ctime>
#include<iomanip>
using namespace std;

int main(){
    cout<<"This Program finds the probability of each number that comes in a fair dice when rolled a 1000 times."<<endl;
    int face[6] = {0, 0, 0, 0, 0, 0}; 
    mt19937 a(static_cast<unsigned int> (time(0)));
    uniform_real_distribution<double>num(0, 1);
    
    for (size_t i = 0; i < 1000000; i++)
    {
        double r1 = num(a);
        if (r1 >=0 && r1 < (1.0/6))
        {
            face[0]++;
        }
        else if (r1 >= (1.0/6) && r1 < (2.0/6))
        {
            face[1]++;
        }
        else if (r1 >= (2.0/6) && r1 < (3.0/6))
        {
            face[2]++;
        }
        else if (r1 >= (3.0/6) && r1 < (4.0/6))
        {
            face[3]++;
        }
        else if (r1 >= (4.0/6) && r1 < (5.0/6))
        {
            face[4]++;
        }
        else
        {
            face[5]++;
        }
        
    }
    
    float sum = 0;
    for (size_t j = 1; j <= 6; j++)
    {
        cout<<"The probability of getting "<<j<<" on the upper face is "<<fixed<<setprecision(4)<<(face[j-1]/1000000.0)<<endl;
        sum += face[j-1]/1000000.0;
    }
    
    cout<<"And the sum of all the probabilities is "<<sum<<endl;
    return 0;
}