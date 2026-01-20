#include<iostream>
#include<vector>
#include<cmath>
#include<iomanip>
#include<fstream>
#include<cstdio>
using namespace std;

vector<float> Fit(vector<vector<float>> V){
    float SumX = 0, SumY = 0, SumXY = 0, SumX2 = 0, m, c;
    for (size_t i = 0; i < V[0].size(); i++)
    {
        SumX += V[0][i];
        SumY += V[1][i];
        SumXY += (V[0][i]*V[1][i]);
        SumX2 += pow(V[0][i], 2);
    }
    m = (((V[0].size()*SumXY)-(SumX*SumY))/((V[0].size()*SumX2)-pow(SumX, 2)));
    c = (SumY - (m*SumX))/V[0].size();

    vector<float> pair = {m, c};
    return pair;
}

int main(){
    cout<<"This Program finds the linear fit of the data that you enter in the vector.";
    vector<vector<float>> Values = {
        {1, 2, 3, 4, 5},
        {2.2, 3.9, 6, 7.8, 10.2}
    };

    int nums = 1, nume = 10;
    while (nums != nume + 1)
    {
        Values[0].push_back(nums);
        nums += 1;
    }
    
    try
    {
        ofstream f("C:/Users/lenovo/OneDrive/Desktop/Coding/SIES C++/Least Square Fit/LinearaFit.txt");
        if (f.is_open())
        {
            for (size_t j = 0; j < Values[0].size(); j++)
            {
                f<<fixed<<setprecision(4)<<setw(15)<<Values[0][j]<<setw(15)<<Values[1][j]<<setw(15)<<(Fit(Values)[0]*Values[0][j] + Fit(Values)[1])<<endl;
            }
            
        }
        else
        {
            throw("An error occured and the file couldn't be opened.");
        }
    }
    catch(const string &e)
    {
        cerr<<"Error: "<<e<<endl;
    }
    
    try
    {
        ofstream gp("C:/Users/lenovo/OneDrive/Desktop/Coding/SIES C++/Least Square Fit/LinearFit.gp");
        if (gp.is_open())
        {
            gp<<"set terminal pngcairo size 1920, 1080 enhanced font 'Arial, 17'"<<endl;
            gp<<"set output 'LinearFit.png'"<<endl;
            gp<<"set label 'Linear Fit Graph' at screen 0.5, 0.95 center font 'Arial, 17'"<<endl;
            gp<<"set xlabel 'X Values'"<<endl;
            gp<<"set xtics offset 0, -0.5"<<endl;
            gp<<"set xrange [0:11]"<<endl;
            gp<<"set ylabel 'Y Values'"<<endl;
            gp<<"set yrange [0:60]"<<endl;
            gp<<"set ytics offset 0, -0.1"<<endl;
            gp<<"set bmargin 5"<<endl;
            gp<<"set tmargin 5"<<endl;
            gp<<"set grid lw 2 lt 1 lc rgb 'gray'"<<endl;
            gp<<"set style line 1 pt 7 ps 1 lc rgb 'red'"<<endl;
            gp<<"set style line 2 lt 1 lw 2 lc rgb 'blue'"<<endl;
            gp<<"set key top left"<<endl;
            gp<<"plot \\"<<endl;
            gp<<"'LinearaFit.txt' u 1:2 w p ls 1 t 'Given Data Scatter plot',\\"<<endl;
            gp<<"'LinearaFit.txt' u 1:3 w l ls 2 t 'Linear Fit of Data'"<<endl;
        }
        else
        {
            throw("An error occured and the file couldn't be opened.");
        }
        
    }
    catch(const string &e1)
    {
        cerr<<"Error: "<<e1<<endl;
    }
    
    system("gnuplot LinearFit.gp");
    system("start LinearFit.png");
    return 0;
}