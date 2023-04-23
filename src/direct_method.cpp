#include <direct_method.h>

#include <cmath>

direct_return_code DirectMethod::solve(vector<double> &X, double &minF) {
    direct_return_code returnCode;
    double start = 0.0, maxtime = 0.0;
    double magicEpsAbs = 0.0;
    int forceStop = 0;
    double fglobal = DIRECT_UNKNOWN_FGLOBAL;
    double fglobalReltol = DIRECT_UNKNOWN_FGLOBAL_RELTOL;

    X.resize(n);

    returnCode = direct_optimize(f, fData, n, A.data(), B.data(), X.data(), &minF, maxFevals, maxIters, 
                                 start, maxtime, magicEps, magicEpsAbs, volumeReltol, sigmaReltol,
                                 &forceStop, fglobal, fglobalReltol, logfile, algorithm);
    
    return returnCode;
}

direct_return_code DirectMethod::solveTest() {
    vector<double> X(n);
    double minF;

    return solve(X, minF);
}
