#include<iostream>
#include<vector>
#include<random>
#include"pcg_random.hpp"
#include<ctime>
#include<cmath>
#include<fstream>
#include<stdexcept>
#include<filesystem>
#include<cstdlib>
#include<chrono>
using namespace std;
namespace fs = filesystem;
class Model{
    private:
        static constexpr double k_B = 1.0;
        const unsigned int NOS;
        const double T_low, T_high, dt = 0.01, J = 1;
        pcg64 g;
        uniform_int_distribution<int> r1;
        uniform_real_distribution<double> r2;
        vector<double> Ms, T;

        inline int flip(int spin){
            spin = -spin;
            return spin;
        }

        double maggen(double temp){
            vector<vector<int>> spins(NOS, vector<int>(NOS, 1));
            double Msum = 0;
            unsigned int count = 0;
            for (size_t i = 0; i < (NOS*NOS)*200; i++)
            {
                int rnd1 = r1(g);
                int rnd3 = r1(g);
                double dE = 2*J*spins[rnd1][rnd3]*(spins[((rnd1 - 1) + NOS)%NOS][rnd3] + spins[(rnd1 + 1)%NOS][rnd3] + spins[rnd1][((rnd3 - 1) + NOS)%NOS] + spins[rnd1][(rnd3 + 1)%NOS]);
                if (dE <= 0)
                {
                    spins[rnd1][rnd3] = flip(spins[rnd1][rnd3]);
                }
                else
                {
                    double P = exp(-dE/(k_B*temp));
                    double rnd2 = r2(g);
                    if (rnd2 < P)
                    {
                        spins[rnd1][rnd3] = flip(spins[rnd1][rnd3]);
                    }
                }
                if ((i >= (NOS*NOS)*100) && (i%(NOS*NOS) == 0))
                {
                    count++;
                    double sum = 0;
                    for (size_t j = 0; j < NOS; j++)
                    {
                        for (size_t k = 0; k < NOS; k++)
                        {
                            sum += spins[j][k];
                        }
                        
                    }
                    double M = sum/(NOS*NOS);
                    Msum += abs(M);
                }
                
            }
            double Mavg = Msum/count;
            return Mavg;
        }

    public:
        Model(unsigned int N, double tl, double th): NOS(N), T_low(tl), T_high(th), g(static_cast<unsigned long long>(time(0))), r1(0, (N - 1)), r2(0.0, 1.0) {}

        void plot(){
            try
            {
                ofstream file("docs/data.bin", ios::binary);
                if (file.is_open())
                {
                    double temp = T_low;
                    while (temp <= T_high)
                    {
                        double M = maggen(temp);
                        file.write(reinterpret_cast<const char*>(&temp), sizeof(temp));
                        file.write(reinterpret_cast<const char*>(&M), sizeof(M));
                        temp += dt;
                    }
                    
                }
                else
                {
                    throw runtime_error("The file couldn't be opened.");
                }
                
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
            
            try
            {
                ofstream gp("docs/plot.gp");
                if (gp.is_open())
                {
                    gp<<"set terminal pngcairo size 1920, 1080 font 'Cursive, 18'"<<endl;
                    gp<<"set output 'docs/graphs/2D Ising Phase Transition.png'\n"<<endl;
                    gp<<"set style line 1 lt 1 lc rgb 'blue' lw 2"<<endl;
                    gp<<"set style line 2 lt 1 lc rgb 'gray' lw 0.5\n"<<endl;
                    gp<<"set title '2D Ising Model Phase Transition' tc rgb 'red' font ', 30'"<<endl;
                    gp<<"set xlabel 'Temperature (K)' tc rgb 'black'"<<endl;
                    gp<<"set ylabel 'Magnetization' tc rgb 'black'"<<endl;
                    gp<<"set grid ls 2\n"<<endl;
                    gp<<"plot 'docs/data.bin' binary format='%double%double' u 1:2 w l ls 1 notitle"<<endl;
                }
                else
                {
                    throw runtime_error("The file couldn't be opened.");
                }
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
            
        }
};

int main(){
    cout<<"This code will plot a graph of Phase transition of a 2D Ising model in a temperature range."<<endl;
    cout<<"Enter the number of spins the ensemble should contain: - ";
    unsigned int N;
    cin>>N;
    cout<<"Enter the lower temperature range: - ";
    double tl, th;
    cin>>tl;
    cout<<"Enter the higher temperature range: - ";
    cin>>th;
    auto start = chrono::high_resolution_clock::now();
    if (!(fs::exists("docs/graphs")))
    {
        fs::create_directories("docs/graphs");
    }
    Model Ising(N, tl, th);
    Ising.plot();
    system("gnuplot \"docs\\plot.gp\"");
    system("start \"\" \"docs\\graphs\\2D Ising Phase Transition.png\"");
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double>elapsed = end - start;
    cout<<"Time Elapsed: "<<elapsed.count()<<" seconds."<<endl;
    return 0;
}