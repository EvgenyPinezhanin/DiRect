#include <direct_method.h>

#include <cmath>

direct_return_code direct_method::solve(vector<double> &X, double &minf) {
    direct_return_code ret_code;
    double start = 0.0, maxtime = 0.0;
    double magic_eps_abs = 0.0;
    int force_stop = 0;
    double fglobal = DIRECT_UNKNOWN_FGLOBAL;
    double fglobal_reltol = DIRECT_UNKNOWN_FGLOBAL_RELTOL;

    X.resize(n);

    ret_code = direct_optimize(f, f_data, n, A.data(), B.data(), X.data(), &minf, max_feval, max_iter, 
                               start, maxtime, magic_eps, magic_eps_abs, volume_reltol, sigma_reltol,
                               &force_stop, fglobal, fglobal_reltol, logfile, algorithm);
    
    return ret_code;
}

direct_return_code direct_method::solve_test() {
    vector<double> X(n);
    double minf;

    return solve(X, minf);
}