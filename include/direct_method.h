#ifndef DIRECT_METHOD_H
#define DIRECT_METHOD_H

#include <cstdio>
#include <vector>
#include <functional>

#include <direct.h>

using namespace std;

class direct_method {
private:
    direct_objective_func f;
    void *f_data;
    vector<double> A, B;

    int n, max_feval, max_iter;
    double magic_eps;
    double volume_reltol, sigma_reltol;

    FILE *logfile;
    direct_algorithm algorithm;

public:
    direct_method(direct_objective_func _f = nullptr, void *_f_data = nullptr, int _n = 2, vector<double> _A = vector<double>{}, 
                  vector<double> _B = vector<double>{}, int _max_feval = 1000, int _max_iter = 1000, double _magic_eps = 0.0, 
                  double _volume_reltol = 0.0, double _sigma_reltol = -1.0, FILE *_logfile = nullptr, 
                  direct_algorithm _algorithm = DIRECT_ORIGINAL) : f(_f), f_data(_f_data), n(_n), A(_A), B(_B), 
                  max_feval(_max_feval), max_iter(_max_iter), magic_eps(_magic_eps), volume_reltol(_volume_reltol), 
                  sigma_reltol(_sigma_reltol), logfile(_logfile), algorithm(_algorithm) {};

    void setF(direct_objective_func _f) { f = _f; };
    void setFData(void* _f_data) { f_data = _f_data; };
    void setN(int _n) { n = _n; };
    void setA(const vector<double> &_A) { A = _A; };
    void setB(const vector<double> &_B) { B = _B; };
    void setAB(const vector<double> &_A, const vector<double> &_B) { A = _A; B = _B; };

    void setMaxFeval(int _max_feval) { max_feval = _max_feval; };
    void setMaxIter(int _max_iter) { max_iter = _max_iter; };
    void setMagicEps(double _magic_eps) { magic_eps = _magic_eps; };
    void setVolumeReltol(int _volume_reltol) { volume_reltol = _volume_reltol; };
    void setSigmaReltol(int _sigma_reltol) { sigma_reltol = _sigma_reltol; };

    void setLogfile(FILE *_logfile) { logfile = _logfile; };
    void setAlghorithm(direct_algorithm _algorithm) { algorithm = _algorithm; };

    int solve(vector<double> &X, double &minf);
};

#endif // DIRECT_METHOD_H
