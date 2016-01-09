//
// Created by marin on 08.01.16..
//

#ifndef ANFIS_ANFIS_H
#define ANFIS_ANFIS_H

#include "ostream"
#include "vector"
#include "Pair.h"
#include "Params.h"
#include "Derivatives.h"

class ANFIS {
public:
    ANFIS(int m);
    static double mu(const double x, const double a, const double b);
    static double get_z(const double x, const double y, const double p, const double q, const double r);
    static double random_number(const double fMin, const double fMax);
    double predict(const double x, const double y);
    std::vector<double> predict(std::vector<Pair> &dataset);
    Params propagate(const double x, const double y);
    double get_error(const std::vector<Pair> &dataset);
    void fit(const std::vector<Pair> &dataset, const double eta, const int n_iter, bool batch);
    void update_params(Derivatives &d, double eta);
    friend inline std::ostream& operator<<(std::ostream & Str, ANFIS const & v){
        for(int i=0; i<v.m; i++){
            Str << v.a[i] << " "<< v.b[i] << " "<< v.c[i] << " "<< v.d[i]
            << " "<< v.p[i] << " "<< v.q[i] << " "<< v.r[i] << " "<<std::endl;
        }
        return Str;
    }
protected:
    int m;
    std::vector<double> a;
    std::vector<double> b;
    std::vector<double> c;
    std::vector<double> d;
    std::vector<double> p;
    std::vector<double> q;
    std::vector<double> r;
};


#endif //ANFIS_ANFIS_H
