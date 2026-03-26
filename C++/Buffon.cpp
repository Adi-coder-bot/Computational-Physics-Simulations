#define _USE_MATH_DEFINES
#include<iostream>
#include<cmath>
#include<random>
#include<ctime>
#include"pcg_random.hpp"
#include<iomanip>
#include<chrono>
using namespace std;
class Buffon{
    private:
        const unsigned int limit = pow(10, 9);
        const double l = 1;
        pcg64 g;
        uniform_real_distribution<double>r1, r2;

        double count = 0;
    public:
        Buffon():g(static_cast<unsigned long long>(time(0))), r1(0, (l/2)), r2(0, (M_PI/2)){}

        double pival(){
            for (size_t i = 0; i < limit; i++)
            {
                double theta = r2(g), d = r1(g);
                if (d < (l/2)*sin(theta))
                {
                    count++;
                }
                
            }
            double PI = (2*limit)/count;
            return PI;
        }
};

int main(){
    auto start = chrono::high_resolution_clock::now();
    cout<<"This Program will give an approximate value of Pi."<<endl;
    Buffon needle;
    cout<<"The value of Pi is "<<fixed<<setprecision(6)<<needle.pival()<<endl;
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout<<"Time Elapsed: "<<fixed<<setprecision(4)<<elapsed.count()<<" seconds."<<endl;
    return 0;
}