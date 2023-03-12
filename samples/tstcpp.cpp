#include <iostream>
#include <cstdio>

#include <direct_method.h>

using namespace std;

static int cnt = 0;
double tst_obj(int n, const double *xy, int *undefined_flag, void *unused) {
    double x = xy[0], y = xy[1];
    double f = x * x * (4.0 - 2.1 * x * x + (x * x * x * x) / 3.0) + x * y + y * y * (-4.0 + 4.0 * y * y);
    printf("feval:, %d, %g, %g, %g\n", ++cnt, x, y, f);
    return f;
}

int main(int argc, char **argv) {
    vector<double> X(2), A{-3.0, -3.0}, B{3.0, 3.0};
    int n = 2, max_feval = 500, max_iter = 500;
    double magic_eps = 0.0, magic_eps_abs = 0.0;
    double volume_reltol = 0.0, sigma_reltol = -1.0;
    int info, force_stop = 0;
    double minf;

    direct_method direct(tst_obj, nullptr, n, A, B, max_feval, max_iter, magic_eps, magic_eps_abs, volume_reltol, sigma_reltol, stdout, DIRECT_ORIGINAL);

    info = direct.solve(X, minf);

    cout << "min f = " << minf << ", at (" << X[0] << "," << X[1] << ") after " << cnt << " evals, return value " << info << endl;

#if defined( _MSC_VER )
    cin.get();
#endif

    return 0;
}
