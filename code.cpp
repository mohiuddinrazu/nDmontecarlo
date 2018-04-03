/*
This program evaluates a multi dimension integration using the Monte Carlo method.
Integration of a function f(x1, x2, ... xn) in (a[i],b[i]), i=[1,n] limits.
*/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

double f(double[], int);
double int_mcnd(double(*)(double[],int), double[], double[], int, int);

int main()
{
    const int n = 2;       /* define how many integrals */
    double a[n] = {0.0, 0.0}; /* left end-points */
    double b[n] = {1.0, 1.0}; /* right end-points */
    double result;
    int i, m;
    int ntimes;

    cout.precision(6); /* Precision of the output result */

    time_t seconds_i;
    seconds_i = time (NULL);

    m = 10;                // initial number of intervals
    ntimes = 10;

    // Number of interval doublings with nmax=2^ntimes.
    // This is to show that higher number of intervals
    // gives a higher precision, most of the time. 
    // You will see in the result!
    cout << setw(12) << n <<"D Integration" << endl;
    for (i=0; i <= ntimes; i=++i)
    {
        result = int_mcnd(f, a, b, n, m);
        cout << setw(10)  << m << setw(12) << result <<endl;
        m = m*2;
    }

// cout << " " << n <<"D Integral = " << result << endl;

// current time in seconds (end of calculations)
    time_t seconds_f;
    seconds_f = time (NULL);
    cout << endl << "Total elapsed time : " << seconds_f - seconds_i << " seconds" << endl << endl;

    return 0;
}

// Declare the function with n variables. Here, x[0]=x, x[1]=y ...

double f(double x[], int n)
{
    return x[0] * x[1]* exp (-x[0] * x[0] * x[1]);
}


// Following is the code for numerical evaluation of integration of any function.
double int_mcnd(double(*fn)(double[],int),double a[], double b[], int n, int m)

{
    double r, x[n], p;
    int i, j;

    srand(time(NULL));  /* initial seed value (uses system time) */

    r = 0.0;
    p = 1.0;

// step 1: calculate the common factor p
    for (j = 0; j < n; j = j+1)
      {
         p = p*(b[j]-a[j]);
      }

// step 2: integration
    for (i = 1; i <= m; i=i+1)
    {
// calculate random x[] points
        for (j = 0; j < n; j = j+1)
        {
            x[j] = a[j] + (b[j]-a[j])*rand()/(RAND_MAX+1);
        }
        r = r + fn (x,n);
    }
    r = r*p/m;
    return r;
}
