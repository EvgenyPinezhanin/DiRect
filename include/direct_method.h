#ifndef DIRECT_METHOD_H
#define DIRECT_METHOD_H

#include <cstdio>
#include <vector>
#include <functional>

#include <direct.h>

using namespace std;

class DirectMethod {
private:
    direct_objective_func f;
    void *fData;
    vector<double> A, B;

    int n, maxFevals, maxIters;
    double magicEps;
    double volumeReltol, sigmaReltol;

    double eps;

    FILE *logfile;
    direct_algorithm algorithm;

public:
    DirectMethod(direct_objective_func _f = nullptr, void *_fData = nullptr, int _n = 2, vector<double> _A = vector<double>{}, 
                  vector<double> _B = vector<double>{}, int _maxFevals = 1000, int _maxIters = 1000, double _magicEps = 0.0,
                  double _volumeReltol = 0.0, double _sigmaReltol = -1.0, FILE *_logfile = nullptr, 
                  direct_algorithm _algorithm = DIRECT_ORIGINAL) : f(_f), fData(_fData), n(_n), A(_A), B(_B), 
                  maxFevals(_maxFevals), maxIters(_maxIters), magicEps(_magicEps), volumeReltol(_volumeReltol),
                  sigmaReltol(_sigmaReltol), logfile(_logfile), algorithm(_algorithm) {};

    void setF(direct_objective_func _f) { f = _f; };
    void setFData(void* _fData) { fData = _fData; };
    void setN(int _n) { n = _n; };
    void setA(const vector<double> &_A) { A = _A; };
    void setB(const vector<double> &_B) { B = _B; };
    void setAB(const vector<double> &_A, const vector<double> &_B) { A = _A; B = _B; };

    void setMaxFevals(int _maxFevals) { maxFevals = _maxFevals; };
    void setMaxIters(int _maxIters) { maxIters = _maxIters; };
    void setMagicEps(double _magicEps) { magicEps = _magicEps; };
    void setVolumeReltol(double _volumeReltol) { volumeReltol = _volumeReltol; };
    void setSigmaReltol(double _sigmaReltol) { sigmaReltol = _sigmaReltol; };

    void setLogfile(FILE *_logfile) { logfile = _logfile; };
    void setAlghorithm(direct_algorithm _algorithm) { algorithm = _algorithm; };

    direct_return_code solve(vector<double> &X, double &minf);
    direct_return_code solveTest();
};

#endif // DIRECT_METHOD_H
