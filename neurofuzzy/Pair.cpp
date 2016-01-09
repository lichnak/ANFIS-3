//
// Created by marin on 08.01.16..
//

#include <ostream>
#include "Pair.h"

Pair create_pair(int x, int y, double fx){
    Pair a(x,y,fx);
    a.x = x;
    a.y = y;
    a.fx = fx;
    return a;
}
std::ostream & operator<<(std::ostream & Str, Pair const & v) {
    Str << v.x << " " << v.y << " " << v.fx;
    return Str;
}