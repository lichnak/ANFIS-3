//
// Created by marin on 08.01.16..
//

#include "ANFIS.h"
#include "random"
#include "math.h"
#include "iostream"
#include "Derivatives.h"
#include "ctime"
#define RAND_L -1.0
#define RAND_U +1.0
#define eps 1e-2

ANFIS::ANFIS(int m) {
    this->m = m;
    this->a = std::vector<double>();
    this->b = std::vector<double>();
    this->c = std::vector<double>();
    this->d = std::vector<double>();
    this->p = std::vector<double>();
    this->q = std::vector<double>();
    this->r = std::vector<double>();
    for(int i=0; i< this->m; i++){
        a.push_back(random_number(RAND_L, RAND_U));
        b.push_back(random_number(RAND_L, RAND_U));
        c.push_back(random_number(RAND_L, RAND_U));
        d.push_back(random_number(RAND_L, RAND_U));
        p.push_back(random_number(RAND_L, RAND_U));
        q.push_back(random_number(RAND_L, RAND_U));
        r.push_back(random_number(RAND_L, RAND_U));
    }
}

double ANFIS::random_number(const double fMin, const double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

double ANFIS::mu(const double x, const double a, const double b) {
    return 1.0 / (1.0 + exp(b * (x - a)));
}

double ANFIS::get_z(const double x, const double y, const double p, const double q, const double r) {
    return p * x + q * y + r;
}

Params ANFIS::propagate(const double x, const double y) {
    double alpha[m];
    double beta[m];
    double pi[m];
    double pi_norm[m];
    double z[m];
    double f[m];
    double sum = 0.0;
    //layer 1
    for(int i=0; i< this->m ; i++){
        alpha[i] = this->mu(x, this->a[i], this->b[i]);
        beta[i] = this->mu(y, this->c[i], this->d[i]);
    }
    //layer 2
    for(int i=0; i< this->m ; i++) {
        pi[i] = alpha[i] * beta[i];
    }
    //layer 3
    for(int i=0; i< this->m ; i++) {
        sum+=pi[i];
    }
    for(int i=0; i< this->m ; i++) {
        pi_norm[i] = pi[i] / sum;
    }
    //layer 4
    for(int i=0; i< this->m ; i++) {
        z[i] = this->get_z(x, y, this->p[i], this->q[i], this->r[i]);
    }
    for(int i=0; i< this->m ; i++) {
        f[i] = z[i] * pi_norm[i];
    }
    //layer 5
    sum = 0.0;
    for(int i=0; i< this->m ; i++) {
        sum += f[i];
    }
    return Params(alpha, beta, pi, pi_norm, z, f, sum);
}



double ANFIS::get_error(const std::vector<Pair> &dataset) {
    double sum = 0.0;
    for(int i=0; i<dataset.size(); i++){
        double o = this->predict(dataset[i].x, dataset[i].y);
        sum += pow(dataset[i].fx - o, 2);
    }
    return sum / (double)dataset.size();
}

void ANFIS::fit(const std::vector<Pair> &dataset, const double eta, const int n_iter, bool batch) {
    double err, sum_pi_sq;
    Derivatives der(m);
    int e =0;
    clock_t begin = clock();
    for(e; e<n_iter; e++){
        for(int k=0; k<dataset.size(); k++){
            Params p = this->propagate(dataset[k].x, dataset[k].y);
            double sum_pi = 0.0;
            for(int j =0; j <this->m; j++){
                sum_pi += p.pi[j];
            }
            sum_pi_sq = sum_pi * sum_pi;
            err = dataset[k].fx - p.sum;
            for(int i=0; i<this->m; i++){
                double pi_z = 0.0;
                for(int j=0; j<m; j++){
                    pi_z += p.pi[j] * (p.z[i] - p.z[j]);
                }
                double tmp = (err * pi_z * p.beta[i] * p.alpha[i]) / sum_pi_sq;
                double tmp_ab = tmp * (1.0 - p.alpha[i]);
                double tmp_cd = tmp * (1.0 - p.beta[i]);
                double tmp_pqr = (err * p.pi[i]) / sum_pi;
                der.d_a[i] -= (tmp_ab * b[i]);
                der.d_b[i] += (tmp_ab * (dataset[k].x - a[i]));
                der.d_c[i] -= (tmp_cd * d[i]);
                der.d_d[i] += (tmp_cd * (dataset[k].y - c[i]));
                der.d_p[i] -= (tmp_pqr * dataset[k].x);
                der.d_q[i] -= (tmp_pqr * dataset[k].y);
                der.d_r[i] -= (tmp_pqr);
            }
            if (!batch) this->update_params(der, eta);
        }
        if (batch) this->update_params(der, eta);
//        double error = this->get_error(dataset);
//        std::cout << error << std::endl;
    }
    double error = this->get_error(dataset);
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << "t:" <<elapsed_secs << std::endl;
    std::cout << "e:" << error << std::endl;
    std::cout << "i:" << e << std::endl;
}

double ANFIS::predict(const double x, const double y) {
    Params p = this->propagate(x,y);
    return p.sum;
}

std::vector<double> ANFIS::predict(std::vector<Pair> &dataset) {
    std::vector<double> results = std::vector<double>();
    for(int i=0; i<dataset.size(); i++){
        results.push_back(this->predict(dataset[i].x, dataset[i].y));
    }
    return results;
}

void ANFIS::update_params(Derivatives &d, double eta) {
    for(int i=0; i<this->m; i++){
        this->a [i] -= eta * d.d_a[i];
        this->b [i] -= eta * d.d_b[i];
        this->c [i] -= eta * d.d_c[i];
        this->d [i] -= eta * d.d_d[i];
        this->p [i] -= eta * d.d_p[i];
        this->q [i] -= eta * d.d_q[i];
        this->r [i] -= eta * d.d_r[i];
    }
    d.reset_derivatives(this->m);
}
