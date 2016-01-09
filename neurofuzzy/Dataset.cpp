//
// Created by marin on 08.01.16..
//

#include <iosfwd>
#include <ostream>
#include "Dataset.h"
#include "math.h"
#include "vector"
#include <algorithm>

double f1(double x, double y) {
    return (pow((x-1), 2) + pow((y+2), 2) - 5*x*y +3) * pow(cos( x / 5.0), 2);
}

std::vector<Pair> get_dataset(int lower, int upper) {
    std::vector<Pair> dataset = std::vector<Pair>();
    for(int i=lower; i<=upper; i++){
        for(int j=lower; j<=upper; j++){
            dataset.push_back(Pair(i,j,f1(i,j)));
        }
    }
//    std::random_shuffle ( dataset.begin(), dataset.end() );
    return dataset;
}
