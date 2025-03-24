#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

const float pi = 3.141592653589793;
void Nhap(double &x) /*Ham nhap x tu ban phim*/
{
    int select;
    cout << "Ban nhap x don vi: \n";
    cout << "1. radian \n";
    cout << "2. do \n";
    cout << "Ban chon: ";
    cin >> select;
    switch (select)
    {
    case 1:
        cout << "Nhap x(radian): "; cin >> x;
        break;
    case 2:
        cout << "Nhap x(do): "; cin >> x;
        x *= (pi/180);
        break;
    default:
        exit(0);
        break;
    }
}
double Sin(double x, double epsilon) /*Ham tinh Sin(x) voi do chinh xac la epsilon = 0.00001*/
{
    double term = x;
    double sum  = x;
    int n = 1;

    while(fabs(term) >= epsilon)
    {
        term *= -x * x/((2*n) * (2*n + 1));
        sum += term ;
        n++;
    }
    return sum; 
}

int main()
{
    double x;
    Nhap(x);
    double epsilon = 0.00001;
    double result =  Sin(x, epsilon);
    cout <<"Sin("<<x<<") = " << result;
}