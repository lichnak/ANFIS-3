//
// Created by marin on 08.01.16..
//

#ifndef ANFIS_PARAMS_H
#define ANFIS_PARAMS_H

#include "ostream"
#include "vector"

struct Params {
    double* alpha;
    double* beta;
    double* pi;
    double* pi_norm;
    double* z;
    double* f;
    double sum;
    Params(double*alpha, double*beta, double*pi,
           double*pi_norm, double*z, double*f, double sum)
            :alpha(alpha), beta(beta), pi(pi), pi_norm(pi_norm), z(z), f(f), sum(sum){};
};


#endif //ANFIS_PARAMS_H
