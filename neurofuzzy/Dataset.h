//
// Created by marin on 08.01.16..
//

#ifndef ANFIS_DATASET_H
#define ANFIS_DATASET_H

#include "vector"
#include "Pair.h"

double f1(double x, double y);
std::vector<Pair> get_dataset(int lower, int upper);

#endif //ANFIS_DATASET_H
