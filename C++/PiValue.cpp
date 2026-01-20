#define _USE_MATH_DEFINES
#include<iostream>
#include<random>
#include<ctime>
#include<cmath>
#include<fstream>
#include<iomanip>
#include<stdexcept>
#include<cstdlib>
using namespace std;

class pifinder{
    private:
        int Ns[5] = {500, 5000, 50000, 500000, 10000000};
        mt19937 generator;
        uniform_real_distribution<double> range;
    
    public:
        pifinder() : generator(static_cast<unsigned int> (time(0))), range(-1, 1) {}

        double pi(int N){
            double circle = 0, square = 0;
            for (size_t i = 0; i < N; i++)
            {
                double x = range(generator), y = range(generator);
                if (pow(x, 2) + pow(y, 2) <= 1)
                {
                    circle++;
                }
                else
                {
                    square++;
                }
            }
            
            double pi = 4*(circle/N);
            return pi;
        }

        void filewriter(){
            try
            {
                double pivalues[5];
                for (size_t k = 0; k < 5; k++)
                {
                    pivalues[k] = pi(Ns[k]);
                }

                ofstream file("C:/Users/lenovo/OneDrive/Desktop/Coding/SIES C++/Value of pi/value_of_pi.txt");
                if (file.is_open())
                {
                    file<<"| Iterations | Value of Pi | Absolute error | Relativistic Error | Percentage Error |"<<endl;
                    for (size_t j = 0; j < 5; j++)
                    {

                        file<<"| "<<setw(11)<<fixed<<setprecision(0)<<left<<Ns[j]<<"| "<<setw(12)<<fixed<<setprecision(6)<<left<<pivalues[j]<<"| "<<setw(15)<<fixed<<setprecision(6)<<left<<abs(pivalues[j] - M_PI)<<"| "<<setw(19)<<fixed<<setprecision(6)<<left<<(abs(pivalues[j] - M_PI)/M_PI)<<"| "<<setw(7)<<fixed<<setprecision(6)<<left<<(abs(pivalues[j] - M_PI)/M_PI)*100<<setw(9)<<fixed<<setprecision(6)<<left<<"%"<<"|"<<endl;
                    }

                    file<<"\nThe actual value of Pi is "<<setw(7)<<fixed<<setprecision(6)<<M_PI<<endl;
                }
                else
                {
                    throw runtime_error("The file couldn't be opened");
                }
            }
            catch(const exception& e)
            {
                cerr << e.what() <<endl;
            }
        }
};

int main(){
    cout<<"This Program will print the values of pi in a file for different iterations."<<endl;
    pifinder object;
    object.filewriter();
    system("start value_of_pi.txt");
    return 0;
}