#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <iostream>
#include <type_traits>
#include "core.h"


template<typename T, size_t N>
class Vector{

    static_assert(
        std::is_arithmetic<T>::value,
        "Vector class can only store integral or floating point values"
    );

    static_assert(
        N >= 2, "Vector dimension should be higher or equal to 2"
    );

    friend std::ostream& operator<<(
        std::ostream& os, const Vector& vector     //const Vecotr<T, N>& vector
    ){
        os << "[ ";
        for (size_t i = 0; i < N; ++i){
            os << vector.component[i] << " ";    // if friend funtion
            // os << vector[i] << " ";           // if not friend funtion
        }
        os << "]";
        return os;
    }

    friend Vector operator*(const T&& scalar, const Vector& vector){
        return vector * scalar;
    }

    friend Vector operator*(const T& scalar, const Vector& vector){
        return vector * scalar;
    }

private:

    static constexpr double epsilon = 0.000001;
    static constexpr size_t x=0, y=1, z=2;

    T component[N]; // Array to store vector components


public:

    /******** Constructors - Assignment Operators - Destructor ***************/

    // Default Constructor
    Vector(): component{} {
        std::cout << "Vector's default constructor called" << std::endl;
    }

    // Variadic Template Constructor
    template<typename... Args>
    Vector(Args... args) : component{static_cast<T>(args)...} {

        static_assert(sizeof...(Args) == N, "Number of arguments must be equal to the vector dimension N");

        std::cout << "Vector's Variadic template constructor called" << std::endl;
    }

    // Copy Constructor
    Vector(const Vector& source){

        std::cout << "Vector's copy constructor called" << std::endl;

        for (size_t i{}; i<N; ++i){
            component[i] = source.component[i];
        }
    }

    // Move Constructor
    Vector(const Vector&& source){
        
        std::cout << "Vector's move constructor called" << std::endl;

        for (size_t i{}; i<N; ++i){
            component[i] = source.component[i];
        }
        
    }

    // Copy Assignment Operator
    Vector& operator=(const Vector& rhs){

        std::cout << "Vector's copy assignment operator called" << std::endl;

        if (this == &rhs){
            return *this;
        }

        for (size_t i{}; i<N; ++i){
            component[i] = rhs.component[i];
        }

        return *this;

    }

    // Move Assignment Operator
    Vector& operator=(Vector&& rhs){

        std::cout << "Vector's move assignment operator called" << std::endl;


        if (this == &rhs){
            return *this;
        }

        for (size_t i{}; i<N; ++i){
            component[i] = rhs.component[i];
        }

        return *this;
    }

    // Default destructor
    ~Vector() = default; 


    /****************** Methods - Overloaded Operators ********************/

    // Subscript or Array Index Operator (Const overload for read-only access)
    const T& operator[](size_t index) const {
        if (index >= N) throw std::out_of_range("Index out of bounds");
        return component[index];
    }

    // Subscript or Array Index Operator (Non-const overload for read/write access)
    T& operator[](size_t index) {
        if (index >= N) throw std::out_of_range("Index out of bounds");
        return component[index];
    }


    // Equal-to Operator (==)
    bool operator==(const Vector& rhs) const {

        for (size_t i{}; i<N; ++i){

            if ( not isEqual(component[i], rhs[i]) ){
                return false;
            }

        }

        return true;
    }

    // Not-Equal-to Operator (!=)
    bool operator!=(const Vector& rhs) const {
        return !(*this == rhs);
    }

    // Addition Arithmetic Operator (+)
    Vector operator+(const Vector& rhs) const {
        
        Vector temp;
        for (size_t i{}; i<N; ++i){
            temp.component[i] = component[i] + rhs.component[i];
        }

        return temp;
    }

    // Subtraction Arithmetic Operator (-)
    Vector operator-(const Vector& rhs) const {

        Vector temp;
        for (size_t i{}; i<N; ++i){
            temp.component[i] = component[i] - rhs.component[i];
        }

        return temp;
    }

    // Compound Assignment Operator (+=)
    void operator+=(const Vector& rhs) {
        for (size_t i{}; i<N; ++i){
            component[i] += rhs.component[i];
        }
    }

    // Compound Assignment Operator (-=)
    void operator-=(const Vector& rhs) {
        for (size_t i{}; i<N; ++i){
            component[i] -= rhs.component[i];
        }
    }

    // scalar Multiplication Operator
    Vector operator*(const T& scalar) const {
        Vector scaledVector {*this};
        for (size_t i{}; i<N; ++i){
            scaledVector.component[i] *= scalar;
        }
        return scaledVector;
    }

    void operator *=(const T& scalar) {
        for (size_t i{}; i<N; ++i){
            component[i] *= scalar;
        }
    }

    // Dot Product Method
    T dot(const Vector& rhs) const {

        T dotProduct {};

        for (size_t i{}; i<N; ++i){
            dotProduct += component[i] * rhs.component[i];
        }

        return dotProduct;
    }

    T operator*(const Vector& rhs) const {
        return (*this).dot(rhs);
    }
    
    // Cross Product Method (3D)
    Vector<T, 3> cross(const Vector<T, 3>& rhs) const {

        static_assert(N == 3, "Vector dimension should be equal to 3");

        Vector<T, 3> crossProduct {};

        crossProduct.component[x] = (
            component[y] * rhs.component[z] - component[z] * rhs.component[y]
        );

        crossProduct.component[y] = (
            component[z] * rhs.component[x] - component[x] * rhs.component[z]
        );

        crosstProduct.component[z] = (
            component[x] * rhs.component[y] - component[y] * rhs.component[x]
        );

        return crossProduct;

    }

    // Cross Product Method (2D)
    T cross(const Vector<T, 2>& rhs) const {

        static_assert(N == 2, "Vector dimension should be equal to 2");

        return component[x] * rhs.component[y] - component[y] * rhs.component[x];

    }

};


// Deduction guide to infer N from the number of arguments
template<typename T, typename... Args>
Vector(T, Args...) -> Vector<T, sizeof...(Args) + 1>;

#endif
