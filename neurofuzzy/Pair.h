//
// Created by marin on 08.01.16..
//

#ifndef ANFIS_PAIR_H
#define ANFIS_PAIR_H

#include "ostream"

struct Pair{
    Pair(int x, int y,  double fx): x(x), y(y), fx(fx){}
    int x;
    int y;
    double fx;
};
std::ostream & operator<<(std::ostream & Str, Pair const & v);

#endif //ANFIS_PAIR_H