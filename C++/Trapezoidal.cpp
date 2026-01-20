#include<iostream>
#include<cmath>
#include<vector>
using namespace std;

double equation(double x){
    return (1 / (1 + x));
}

int main(){
    double lower_limit, upper_limit, h = pow(10, (-6)), sum = 0, y;
    vector<double> values;
    cout<<"This Program will find the integration of Sin(X) over a limit.\nSo, enter the lower limit:- ";
    cin>>lower_limit;
    cout<<"Enter the upper limit:- ";
    cin>>upper_limit;

    y = lower_limit;
    while (y <= upper_limit)
    {
        values.push_back(equation(y));
        y += h; 
    }
    
    for (size_t i = 0; i < (values.size() - 1); i++)
    {
        sum += ((values[i] + values[i + 1])/2)*h;
    }
    
    cout<<"The integration of Sin(X) over the limits "<<lower_limit<<" to "<<upper_limit<<" is "<<sum<<endl;
    return 0;
}