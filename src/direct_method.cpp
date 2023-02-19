#include <direct_method.h>

#include <cmath>

int direct_method::solve(vector<double> &X, double &minf) {
    direct_return_code ret_code;
    double magic_eps_abs = abs(magic_eps);
    double start = 0.0, maxtime = 0.0;
    int force_stop = 0;
    double fglobal_reltol = 0.0;

    X.resize(n);

    ret_code = direct_optimize(f, f_data, n, A.data(), B.data(), X.data(), &minf, max_feval, max_iter, 
                               start, maxtime, magic_eps, magic_eps_abs, volume_reltol, sigma_reltol,
                               &force_stop, DIRECT_UNKNOWN_FGLOBAL, fglobal_reltol, logfile, algorithm);
    
    return ret_code;
}