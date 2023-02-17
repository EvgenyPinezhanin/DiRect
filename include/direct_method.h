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
    direct_algorithm algorithm;
    FILE *logfile;

public:
    direct_method(direct_objective_func _f, void *_f_data, int _n, vector<double> _A, vector<double> _B, 
                  int _max_feval, int _max_iter, direct_algorithm _algorithm, FILE *_logfile) : f(_f), 
                  f_data(_f_data), n(_n), A(_A), B(_B), max_feval(_max_feval), max_iter(_max_iter), 
                  algorithm(_algorithm), logfile(_logfile) {};

    void setF(direct_objective_func _f) { f = _f; };
    void setFData(void* _f_data) { f_data = _f_data; };
    void setN(int _n) { n = _n; };
    void setA(const vector<double> &_A) { A = _A; };
    void setB(const vector<double> &_B) { B = _B; };
    void setAB(const vector<double> &_A, const vector<double> &_B) { A = _A; B = _B; };
    void setMaxFeval(int _max_feval) { max_feval = _max_feval; };
    void setMaxIter(int _max_iter) { max_iter = _max_iter; };
    void setAlghorithm(direct_algorithm _algorithm) { algorithm = _algorithm; };

    int solve(vector<double> &X, double &minf);
};

#endif // DIRECT_METHOD_H
