//
// Created by marin on 08.01.16..
//

#ifndef ANFIS_DERIVATIVES_H
#define ANFIS_DERIVATIVES_H

struct Derivatives {
    Derivatives(double* d_a, double* d_b, double* d_c, double* d_d, double* d_p, double* d_q, double* d_r):
            d_a(d_a), d_b(d_b), d_c(d_c), d_d(d_d), d_p(d_p), d_q(d_q), d_r(d_r) {};
    Derivatives(int m);
    double* d_a;
    double* d_b;
    double* d_c;
    double* d_d;
    double* d_p;
    double* d_q;
    double* d_r;
    void reset_derivatives(int m);
};


#endif //ANFIS_DERIVATIVES_H
