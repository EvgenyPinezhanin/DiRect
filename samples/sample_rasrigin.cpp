#include <iostream>
#include <cstdio>
#if defined( _MSC_VER )
    #define _USE_MATH_DEFINES
    #include <math.h>
#else
    #include <cmath>
#endif

#include <direct_method.h>

using namespace std;

double f_rastrigin(int n, const double *X, int *undefined_flag, void *data) {
    int *count = static_cast<int*>(data); (*count)++;
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += X[i] * X[i] - 10.0 * cos(2.0 * M_PI * X[i]);
    }
    return 10.0 * n + sum;
}

int main(int argc, char **argv) {
    vector<double> X, A{-0.5, -0.5}, B{1.0, 1.0};
    int n = 2, max_feval = 500, max_iter = 500;
    int info, force_stop = 0, count;
    double minf;

    direct_method direct(f_rastrigin, &count, n, A, B, max_feval, max_iter, DIRECT_ORIGINAL, stdout);

    info = direct.solve(X, minf);

    cout << "min f = " << minf << ", at (" << X[0] << "," << X[1] << ") after " << count << " evals, return value " << info << endl;

#if defined(_MSC_VER)
    cin.get();
#endif

    return 0;
}
