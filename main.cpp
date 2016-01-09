#include <iostream>
#include "neurofuzzy/Dataset.h"
#include "vector"
#include "random"
#include "neurofuzzy/ANFIS.h"

using namespace std;

int main(int argc, char** argv) {
    srand(5);
    double eta; int n_iter; int m; bool batch;
    if (argc < 2){
        eta = 1e-4;
        n_iter = 1000;
        batch = true;
        m = 8;
    }
    else{
        eta = atof(argv[1]);
        n_iter = atoi(argv[2]);
        batch = (bool)atoi(argv[3]);
        m = atoi(argv[4]);
    }
    vector<Pair> dataset = get_dataset(-4,4);
    for(int mi=1; mi<= 20; mi++){
        ANFIS a(mi);
        a.fit(dataset, eta, n_iter, batch);
    }
    return 0;
}