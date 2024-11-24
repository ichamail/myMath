#include "core.h"
#include <cmath>
static constexpr double epsilon = 0.000001;

bool isEqual(double x, double y){
    return std::abs(x-y) < epsilon;
}

bool isEqual(int x, int y){
    return std::abs(x-y) < epsilon;
}
