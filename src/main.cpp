#include <iostream>
#include "Vector.h"
#include "Matrix.h"
#include "Tensor.h"


int main(){

    Vector v{1, 2, 3};
    Matrix m{{1, 2, 3}, {4, 5, 6}};

    std::cout << v << std::endl;
    std::cout << m << std::endl;

    std::cout << 2 * Vector{1, 2, 3} * 10 << std::endl;
    std::cout << Vector{1, 0, 0} * Vector{0, 1, 0} << std::endl;
    std::cout << ( Vector {1, 0, 0} ).cross( Vector {0, 1, 0} ) << std::endl;
    std::cout << Matrix{{0, -1, 0}, {1, 0, 0}, {0, 0, 1}} * Vector{1, 0, 0} << std::endl;
    std::cout << Matrix{{1, 2, 3}, {4, 5, 6}} * Matrix{{1, 2}, {3, 4}, {4, 5}} <<std::endl;

    return 0;
}
