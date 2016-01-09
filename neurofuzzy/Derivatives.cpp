//
// Created by marin on 08.01.16..
//

#include <stdlib.h>
#include "Derivatives.h"

void Derivatives::reset_derivatives(int m) {
    for(int i=0; i<m; i++){
        d_a[i] = 0.0;
        d_b[i] = 0.0;
        d_c[i] = 0.0;
        d_d[i] = 0.0;
        d_p[i] = 0.0;
        d_q[i] = 0.0;
        d_r[i] = 0.0;
    }
}

Derivatives::Derivatives(int m) {
    d_a = (double*) malloc (m * sizeof(double));
    d_b = (double*) malloc (m * sizeof(double));
    d_c = (double*) malloc (m * sizeof(double));
    d_d = (double*) malloc (m * sizeof(double));
    d_p = (double*) malloc (m * sizeof(double));
    d_q = (double*) malloc (m * sizeof(double));
    d_r = (double*) malloc (m * sizeof(double));
    reset_derivatives(m);
}
