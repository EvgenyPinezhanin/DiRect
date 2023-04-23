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

double fRastrigin(int n, const double *X, int *undefinedFlag, void *data) {
    int *count = static_cast<int*>(data); (*count)++;
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += X[i] * X[i] - 10.0 * cos(2.0 * M_PI * X[i]);
    }
    return 10.0 * n + sum;
}

int main(int argc, char **argv) {
    vector<double> X, A{ -0.5, -0.5 }, B{ 1.0, 1.0 };
    int n = 2, maxFevals = 500, maxIters = 500;
    double magicEps = 0.0;
    double volumeReltol = 0.0, sigmaReltol = -1.0;
    int info, forceStop = 0, numberFevals;
    double minF;

    DirectMethod direct(fRastrigin, &numberFevals, n, A, B, maxFevals, maxIters, magicEps, volumeReltol, sigmaReltol, stdout, DIRECT_ORIGINAL);

    info = direct.solve(X, minF);

    cout << "min f = " << minF << ", at (" << X[0] << "," << X[1] << ") after " << numberFevals << " evals, return value " << info << endl;

#if defined(_MSC_VER)
    cin.get();
#endif

    return 0;
}
