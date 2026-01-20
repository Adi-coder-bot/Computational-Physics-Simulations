#include<iostream>
#include<vector>
#include<fstream>
#include<iomanip>
#include<cstdlib>
#include<cmath>
using namespace std;

class NR4{
    private:
        double x0 = 0, y0 = 1, h = 0.01;

        double dy(double x, double y){
            return y; 
        }

    public:
        NR4(double X0, double Y0, double H){
            x0 = X0;
            y0 = Y0;
            h = H;
        }
        
        vector<double> k(double x, double y){
            vector<double> K(4);
            K[0] = h*dy(x, y);
            K[1] = h*dy((x + (h/2)), (y + (K[0]/2)));
            K[2] = h*dy((x + (h/2)), (y + (K[1]/2)));
            K[3] = h*dy((x + h), (y + K[2]));

            return K;
        }

        vector<vector<double>> method(double end){
            vector<vector<double>> values(2);

            while (x0 <= end)
            {
                vector<double> a = k(x0, y0);
                values[0].push_back(x0);
                values[1].push_back(y0);
    
                x0 += h;
                y0 += (1/6.0)*(a[0] + 2*a[1] + 2*a[2] + a[3]);
            }

            return values;
        }
};

int main(){
    cout<<"This Progarm will plot a graph of differential Equation using Range Kutta 4 method."<<endl;
    double x0, y0, h, e;

    cout<<"Enter the starting value of X:- ";
    cin>>x0;
    cout<<"Enter the value of Y at X = "<<x0<<":- ";
    cin>>y0;
    cout<<"Enter the small difference by which to increase the x values:- ";
    cin>>h;
    cout<<"Enter the value of x till which you want to find the y values.( like from x = 0 to 25, then enter 25.):- ";
    cin>>e;

    NR4 equation(x0, y0, h);
    vector<vector<double>> data = equation.method(e);

    try
    {
        ofstream Data("C:/Users/lenovo/OneDrive/Desktop/Coding/SIES C++/Range Kutta 4/data.txt");
        if (Data.is_open())
        {
            for (size_t i = 0; i < data[0].size(); i++)
            {
                Data<<fixed<<setprecision(4)<<data[0][i]<<" "<<data[1][i]<<endl;
            }
        }
        else
        {
            throw runtime_error("An error occured. The file couldn't be opened.");
        }
    }
    catch(const exception& e)
    {
        cerr<<e.what()<<endl;
        return 1;
    }
    
    try
    {
        ofstream gp("C:/Users/lenovo/OneDrive/Desktop/Coding/SIES C++/Range Kutta 4/RK4.gp");
        if (gp.is_open())
        {
            gp<<"set terminal window enhanced font 'Arial, 18'\n"<<endl;
            gp<<"set label 'Plot of solution dy/dx - y = 0' at screen 0.5, 0.95 center font ',30' tc rgb 'red'"<<endl;
            gp<<"set xlabel 'X Values' tc rgb 'red'"<<endl;
            gp<<"set ylabel 'Y values' tc rgb 'red'"<<endl;
            gp<<"set key top left\n"<<endl;
            gp<<"set tmargin 3"<<endl;
            gp<<"set bmargin 3"<<endl;
            gp<<"set lmargin 10"<<endl;
            gp<<"set lmargin 10"<<endl;
            gp<<"set grid lt 1 lw 2 lc rgb 'gray'\n"<<endl;
            gp<<"plot 'data.txt' u 1:2 w l lt 1 lw 2 lc rgb 'green' notitle"<<endl;
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
    
    system("gnuplot RK4.gp");

    return 0;
}