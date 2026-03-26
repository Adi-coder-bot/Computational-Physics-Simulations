#include<iostream>
#include<random>
#include<ctime>
#include<cmath>
#include<fstream>
#include<vector>
#include<stdexcept>
#include<filesystem>
#include<cstdlib>
#include"pcg_random.hpp"
using namespace std;
namespace fs = filesystem;

class Distribution{
    private:
        pcg64 g;
        uniform_real_distribution<double>r;

        const int limit = pow(10, 7), min = 0, max = 1;
        const string name = "Uniform";
        double binw = (max - min)/100.0;
        vector<int> frequency;
        
        void data(){
            for (size_t i = 0; i < limit; i++)
            {
                double rnd = r(g);
                if (rnd >= min && rnd < max)
                {
                    int A = static_cast<int>((rnd - min)/binw);
                    frequency[A]++;
                }
                else
                {
                    continue;
                }
                
            }
            
        }

    public:
        Distribution(): g(static_cast<uint64_t>(time(0))), r(0, 1), frequency(100, 0){}

        void plot(){
            data();
            try
            {
                ofstream file("docs/data.bin", ios::binary);
                if (file.is_open())
                {
                    for (size_t i = 0; i < frequency.size(); i++)
                    {
                        double val = (min + ((i + 0.5)*binw));
                        file.write(reinterpret_cast<const char*>(&val), sizeof(val));
                        file.write(reinterpret_cast<const char*>(&frequency[i]), sizeof(frequency[i]));
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
                    gp<<"set terminal pngcairo size 1920, 1080 enhanced font 'Arial, 18'"<<endl;
                    gp<<"set output 'docs/graphs/"<<name<<" distribution.png'\n"<<endl;
                    gp<<"set title '"<<name<<" Distribution' tc rgb 'red' font ', 30'"<<endl;
                    gp<<"set xlabel 'bins' tc rgb 'black'"<<endl;
                    gp<<"set xrange ["<<min<<":"<<max<<"]"<<endl;
                    gp<<"set ylabel 'frequency' tc rgb 'black'"<<endl;
                    gp<<"set grid lt 1 lw 0.5 lc rgb 'gray'\n"<<endl;
                    gp<<"set style fill solid border -1"<<endl;
                    gp<<"set boxwidth "<<binw<<" absolute\n"<<endl;
                    gp<<"plot 'docs/data.bin' binary format='%double%int' u 1:2 w boxes lc rgb 'orange' notitle"<<endl;
                }
                
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
        }
};

int main(){
    cout<<"This Program will print the distribution curves of different types of Random number types."<<endl;
    if (!(fs::exists("docs/graphs")))
    {
        fs::create_directories("docs/graphs");
    }
    Distribution RND;
    RND.plot();
    system("gnuplot \"docs\\plot.gp\"");
    system("start \"\" \"docs\\graphs\\Uniform distribution.png\"");
    return 0;
}