#include<iostream>
#include<vector>
#include<fstream>
#include<stdexcept>
#include<Eigen/Dense>
#include<filesystem>
#include<cstdlib>
using namespace std;
using namespace Eigen;
namespace fs = filesystem;

class CO{
    private:
        vector<double> M = {1, 2, 1}, Y0 = {0, 0.4, 0.2, 0, 0, 0}, k = {1, 1.5};
        const double h = 0.001, tfinal = 30;
        vector<double> func(vector<double> &Y){
            double dx1, dx2, dx3, dv1, dv2, dv3;
            dx1 = Y[3];
            dv1 = (k[0]/M[0])*Y[1] - (k[0]/M[0])*Y[0];
            dx2 = Y[4];
            dv2 = (k[0]/M[1])*Y[0] - ((k[0] + k[1])/M[1])*Y[1] + (k[1]/M[1])*Y[2];
            dx3 = Y[5];
            dv3 = (k[1]/M[2])*Y[1] - (k[1]/M[2])*Y[2];
            vector<double> vals = {dx1, dx2, dx3, dv1, dv2, dv3};
            return vals;
        }

        vector<double> RK4(vector<double> &Y){
            int n = Y.size();
            vector<double> k1(n), k2(n), k3(n), k4(n), Ytemp(n);
            vector<double> vals = func(Y);
            for (size_t i = 0; i < n; i++)
            {
                k1[i] = h*vals[i]; 
            }
            for (size_t i = 0; i < n; i++)
            {
                Ytemp[i] = Y[i] + (k1[i]/2); 
            }
            vals = func(Ytemp);
            for (size_t i = 0; i < n; i++)
            {
                k2[i] = h*vals[i];
            }
            for (size_t i = 0; i < n; i++)
            {
                Ytemp[i] = Y[i] + (k2[i]/2); 
            }
            vals = func(Ytemp);
            for (size_t i = 0; i < n; i++)
            {
                k3[i] = h*vals[i];
            }
            for (size_t i = 0; i < n; i++)
            {
                Ytemp[i] = Y[i] + k3[i]; 
            }
            vals = func(Ytemp);
            for (size_t i = 0; i < n; i++)
            {
                k4[i] = h*vals[i];
            }

            vector<double> Ynew(n);
            for (size_t i = 0; i < n; i++)
            {
                Ynew[i] = Y[i] + ((k1[i] + (2*k2[i]) + (2*k3[i]) + k4[i])/6);
            }
            
            return Ynew;
        }

        struct Result
        {
            vector<double> T;
            vector<vector<double>> Yt;
        };
        

        Result program(){
            double t = 0;
            vector<double> Y = Y0;
            Result A;
            while (t <= tfinal)
            {
                vector<double> X = RK4(Y);
                A.Yt.push_back(X);
                A.T.push_back(t);
                Y = X;
                t += h;
            }
            
            
            return A;
        }

    public:
        void plot(){
            try
            {
                ofstream file("documents/data.bin", ios::binary);
                if (file.is_open())
                {
                    Result Values = program();
                    for (size_t i = 0; i < Values.T.size(); i++)
                    {
                        file.write(reinterpret_cast<const char*>(&Values.T[i]), sizeof(double));
                        for (size_t j = 0; j < Values.Yt[i].size(); j++)
                        {
                            file.write(reinterpret_cast<const char*>(&Values.Yt[i][j]), sizeof(double));
                        }
                        
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
                ofstream gp("documents/plot.gp");
                if (gp.is_open())
                {
                    gp<<"set terminal pngcairo size 1920, 1080 enhanced font 'Times New Roman, 18'"<<endl;
                    gp<<"set output 'documents/graphs/Coupled Harmonic Oscillator.png'\n"<<endl;
                    gp<<"set title 'Coupled Harmonic Oscillator' font ', 30' tc rgb 'red'"<<endl;
                    gp<<"set xlabel 'time (s)' tc rgb 'black'"<<endl;
                    gp<<"set ylabel 'positions of masses (m)' tc rgb 'black'"<<endl;
                    gp<<"set grid lt 1 lw 0.5 lc rgb 'gray'"<<endl;
                    gp<<"set key top right\n"<<endl;
                    gp<<"plot\\"<<endl;
                    gp<<"'documents/data.bin' binary format='%double%double%double%double%double%double%double' u 1:2 w l lt 1 lw 2 lc rgb 'blue' t 'X1',\\"<<endl;
                    gp<<"'documents/data.bin' binary format='%double%double%double%double%double%double%double' u 1:3 w l lt 1 lw 2 lc rgb 'green' t 'X2',\\"<<endl;
                    gp<<"'documents/data.bin' binary format='%double%double%double%double%double%double%double' u 1:4 w l lt 1 lw 2 lc rgb 'orange' t 'X3'"<<endl;
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

        void FA(){
            Matrix3d A;
            A << (k[0]/M[0]), -(k[0]/M[0]), 0,
                 -(k[0]/M[1]), ((k[0] + k[1])/M[1]), -(k[1]/M[1]),
                 0, -(k[1]/M[2]), (k[1]/M[2]);
                
            SelfAdjointEigenSolver<Matrix3d> solver(A);
            VectorXd EV = solver.eigenvalues();
            MatrixXd EVe = solver.eigenvectors();

            cout<<"The Eigenvalues are:\n"<<EV<<endl;
            cout<<"The Eigenvectors are:\n"<<EVe<<endl;

            for (size_t i = 0; i < EV.size(); i++) {
                double lam = EV[i];
                if (lam < 1e-6) lam = 0.0;
                std::cout << "Frequency of particle " << i+1
                        << " is " << std::sqrt(lam) << " Hz." << std::endl;
            }

            MatrixXd invEVe = EVe.inverse();
            MatrixXd B(3, 1);
            B << Y0[0], Y0[1], Y0[2];
            MatrixXd amplitudes = invEVe*B;

            for (size_t i = 0; i < amplitudes.size(); i++)
            {
                cout<<"The amplitude of the particle "<<i + 1<<" is "<<amplitudes(i, 0)<<" m."<<endl;
            }
            
        }
};

int main(){
    cout<<"This program will calculate the frequencies and amplitude of a system of Coupled Harmonic Oscillators. And plot the graph of how the masses oscillate about their equilibrium."<<endl;
    if (!(fs::exists("documents/graphs")))
    {
        fs::create_directories("documents/graphs");
        cout<<"The directories are created successfully!"<<endl;
    }
    
    CO System;
    System.FA();
    System.plot();
    system("gnuplot documents/plot.gp");
    system("start \"\" \"documents\\graphs\\Coupled Harmonic Oscillator.png\"");
    return 0;
}