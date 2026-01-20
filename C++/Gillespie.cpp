#include<iostream>
#include<random>
#include<vector>
#include<cmath>
#include<ctime>
#include<fstream>
#include<iomanip>
#include<cstdlib>
using namespace std;

class reaction{
    private:
        float k1 = 0.005, k2 = 0.002, k3 = 0.01, k4 = 0.0001, k5 = 0.01, k6 = 0.5;
        int G0 = 1500, R0 = 500, F0 = 500;

    public:
        vector<double> val(){
            vector<double> a(7);
            a[1] = k1*G0*R0;
            a[2] = k2*R0*F0;
            a[3] = k3*F0*G0;
            a[4] = k4*R0;
            a[5] = k5*F0;
            a[6] = k6*G0;
            a[0] = a[1] + a[2] + a[3] + a[4] + a[5] + a[6];

            return a;
        }
        
        float time(double r1){
            return ((1/val()[0])*log(1/r1));
        }

        vector<double> choice(double r2){
            vector<double> values(3), A = val();
            if ((r2*A[0] >= 0) && (r2*A[0] < A[1]))
            {
                values[0] = --G0;
                values[1] = ++R0;
                values[2] = F0;
            }
            else if ((r2*A[0] >= A[1]) && (r2*A[0] < (A[1] + A[2])))
            {
                values[0] = G0;
                values[1] = --R0;
                values[2] = ++F0;
            }
            else if ((r2*A[0] >= (A[1] + A[2])) && (r2*A[0] < (A[1] + A[2] + A[3])))
            {
                values[0] = ++G0;
                values[1] = R0;
                values[2] = --F0;
            }
            else if ((r2*A[0] >= (A[1] + A[2] + A[3])) && (r2*A[0] < (A[1] + A[2] + A[3] + A[4])))
            {
                values[0] = G0;
                values[1] = --R0;
                values[2] = F0;
            }
            else if ((r2*A[0] >= (A[1] + A[2] + A[3] + A[4])) && (r2*A[0] < (A[1] + A[2] + A[3] + A[4] + A[5])))
            {
                values[0] = G0;
                values[1] = R0;
                values[2] = --F0;
            }
            else if ((r2*A[0] >=  (A[1] + A[2] + A[3] + A[4] + A[5])) && (r2*A[0] < A[0]))
            {
                values[0] = ++G0;
                values[1] = R0;
                values[2] = F0;
            }

            return values;
        } 
};

int main(){
    cout<<"This is a graphical showcase of a system of Grass, Rabbits and Foxes."<<endl;
    
    mt19937 rng(static_cast<unsigned int> (time(0)));
    uniform_real_distribution<double> rn(0, 1);
    reaction nature;
    vector<vector<double>> data = {{0,}, {500,}, {50,}, {10,}};
    double time = 0;
    do
    {
        double r1 = rn(rng), r2 = rn(rng);
        time += nature.time(r1);
        vector<double> react = nature.choice(r2);
        data[0].push_back(time);
        data[1].push_back(react[0]);
        data[2].push_back(react[1]);
        data[3].push_back(react[2]);

    } while ((data[0].size() <= 20000) && ((data[2][data[2].size()-1] > 0) || (data[3][data[3].size()-1] > 0)));
    
    try
    {
        ofstream file("C:/Users/lenovo/OneDrive/Desktop/Coding/SIES C++/Gillespie/data.txt");
        if (file.is_open())
        {
            for (size_t i = 0; i < data[0].size(); i++)
            {
                file<<fixed<<setprecision(4)<<setw(10)<<data[0][i]<<setw(10)<<data[1][i]<<setw(10)<<data[2][i]<<setw(10)<<data[3][i]<<endl;
            }
            
        }
        else
        {
            throw runtime_error("An error occured. The file couldn't be opened");
        }
    }
    catch(const exception& e)
    {
        cerr<<e.what()<<endl;
        return 1;
    }
    
    try
    {
        ofstream gp("C:/Users/lenovo/OneDrive/Desktop/Coding/SIES C++/Gillespie/Gillespie.gp");
        if (gp.is_open())
        {
            gp<<"set terminal window enhanced font 'Arial, 18'\n"<<endl;
            gp<<"set label 'simulation of population of Grass, Rabbits and Foxes' at screen 0.5, 0.95 center font ',30' tc rgb 'red'"<<endl;
            gp<<"set xlabel 'time (months)' tc rgb 'red'"<<endl;
            gp<<"set ylabel 'population' tc rgb 'red'"<<endl;
            gp<<"set key center right\n"<<endl;
            gp<<"set tmargin 3"<<endl;
            gp<<"set bmargin 3"<<endl;
            gp<<"set lmargin 10"<<endl;
            gp<<"set lmargin 10"<<endl;
            gp<<"set grid lt 1 lw 2 lc rgb 'gray'\n"<<endl;
            gp<<"set style line 1 lt 1 lw 2 lc rgb 'green'"<<endl;
            gp<<"set style line 2 lt 1 lw 2 lc rgb 'red'"<<endl;
            gp<<"set style line 3 lt 1 lw 2 lc rgb 'blue'\n"<<endl;
            gp<<"plot\\"<<endl;
            gp<<"'data.txt' u 1:2 w l ls 1 t 'grass',\\"<<endl;
            gp<<"'data.txt' u 1:3 w l ls 2 t 'rabbit',\\"<<endl;
            gp<<"'data.txt' u 1:4 w l ls 3 t 'fox'\n"<<endl;
            gp<<"pause mouse"<<endl;
        }
        else
        {
            throw runtime_error("An error occured. The file couldn't be opened.");
        }
        
    }
    catch(const exception& e1)
    {
        cerr<<e1.what()<<endl;
        return 1;
    }

    system("gnuplot Gillespie.gp");
    
    return 0;
}