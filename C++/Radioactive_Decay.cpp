#include<iostream>
#include<random>
#include<ctime>
#include<cmath>
#include<vector>
#include<tuple>
#include<fstream>
#include<stdexcept>
#include<iomanip>
#include<cstdlib>
using namespace std;

class AtoB{
    private:
        double kA = 2, kB = 12, tfinal = 10;
        mt19937 generator;
        uniform_real_distribution<double> range;

    public:
        AtoB():generator(static_cast<unsigned int> (time(0))), range(0, 1) {}

        vector<double> rates(int A, int B){
            vector<double> a(2);
            a[0] = kA*A;
            a[1] = kB*B;

            return a;
        }

        tuple<vector<int>, vector<int>, vector<double>> values(){
            double t = 0, a0, a1, a2, r1, r2, T;
            vector<int> Avals, Bvals;
            vector<double> tvals;
            int A = 1000, B = 0;
            while (t <= tfinal)
            {
                Avals.push_back(A);
                Bvals.push_back(B);
                tvals.push_back(t);
                a1 = rates(A, B)[0];
                a2 = rates(A, B)[1];
                a0 = a1 + a2;

                r1 = range(generator);
                r2 = range(generator);

                T = (1/a0)*log(1/r1);

                if (r2*a0 <= a1)
                {
                    A -= 1;
                    B += 1;
                }
                else
                {
                    B -= 1;
                    A += 1;
                }
                
                t += T;
            }
            
            tuple<vector<int>, vector<int>, vector<double>> values = make_tuple(Avals, Bvals, tvals);
            return values;
        }

        void plot(){
            tuple<vector<int>, vector<int>, vector<double>> V = values();
            try
            {
                ofstream file("C:/Users/lenovo/OneDrive/Desktop/Coding/SIES C++/Law of Radioactive Decay/data.txt");
                if (file.is_open())
                {
                    for (size_t i = 0; i < get<2>(V).size(); i++)
                    {
                        file<<setw(9)<<fixed<<setprecision(6)<<left<<get<2>(V)[i]<<setw(5)<<fixed<<setprecision(0)<<left<<get<0>(V)[i]<<setw(5)<<fixed<<setprecision(0)<<left<<get<1>(V)[i]<<endl;
                    }
                    
                }
                else
                {
                    throw runtime_error("The file couldn't be opened.");
                }
                
            }
            catch(const exception& e)
            {
                cerr << e.what() <<endl;
            }
            
            try
            {
                ofstream gp("C:/Users/lenovo/OneDrive/Desktop/Coding/SIES C++/Law of Radioactive Decay/plot.gp");
                if (gp.is_open())
                {
                    gp<<"set terminal window enhanced font 'Papyrus, 18'\n"<<endl;
                    gp<<"set title 'Plot of A-->B and B-->A' tc rgb 'brown' font ', 30'"<<endl;
                    gp<<"set xlabel 'time in minutes' tc rgb 'brown'"<<endl;
                    gp<<"set ylabel 'number of molecules' tc rgb 'brown'"<<endl;
                    gp<<"set grid lt 1 lw 2 lc rgb 'gray'\n"<<endl;
                    gp<<"set style line 1 lc rgb 'red' lt 2 lw 2"<<endl;
                    gp<<"set style line 2 lc rgb 'blue' lt 2 lw 2"<<endl;
                    gp<<"set key top right\n"<<endl;
                    gp<<"plot\\"<<endl;
                    gp<<"'data.txt' u 1:2 w l ls 1 t 'molecules of A',\\"<<endl;
                    gp<<"'data.txt' u 1:3 w l ls 2 t 'molecules of B',\n"<<endl;
                    gp<<"pause -1"<<endl;
                }
                else
                {
                    throw runtime_error("The file couldn't be opened");
                }
                
            }
            catch(const std::exception& f)
            {
                std::cerr << f.what() << '\n';
            }
            
        }
};

int main(){
    cout<<"This program will plot a graph of decay of A with rise of B and vice versa."<<endl;
    AtoB object;
    object.plot();
    system("gnuplot \"C:/Users/lenovo/OneDrive/Desktop/Coding/SIES C++/Law of Radioactive Decay/plot.gp\"");
    return 0;
}