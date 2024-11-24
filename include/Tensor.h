#ifndef _TENSOR_H_
#define _TENSOR_H_

#include <iostream>
#include <type_traits>
#include "Vector.h"

template<typename T, size_t R, size_t C>
class Tensor{

    static_assert(
        std::is_arithmetic<T>::value,
        "Tensor class can only store integral or floating point values"
    );

    static_assert(
        R >= 2, "Number of Tensor Rows R should be higher or equal to 2"
    );

    static_assert(
        C >= 2, "Number of Matrix Columns C should be higher or equal to 2"
    );

    friend std::ostream& operator<<(
        std::ostream& os, const Tensor& tensor    //const Vecotr<T, N>& vector
    ){
        for (size_t i{}; i < R; ++i){
            for (size_t j{}; j < C; ++j){
                os << tensor.rowVec[i][j] << " ";
            }
            if (i != R-1) {os << std::endl;}
        }
        return os;
    }

    friend Tensor operator*(const T&& scalar, const Tensor& tensor){
        return tensor * scalar;
    }

    friend Tensor operator*(const T& scalar, const Tensor& tensor){
        return tensor * scalar;
    }

    private:

        
        Vector<T, C> rowVec[R]; // array to store matrix elements

        Vector<T, C> createVector(const T (&row)[C]){
            Vector<T, C> vector{};
            for (size_t i{}; i<C; ++i){
                vector[i] = row[i];
            }
            return vector;
        }

    public:

    /******** Constructors - Assignment Operators - Destructor ***************/

    // Default Constructor
    Tensor(): rowVec{} {
        std::cout << "Tensor's default constructor called" << std::endl;
    }

    
    template<size_t ... Cs>
    Tensor(const T (&...arr)[Cs]): rowVec{createVector(arr)...} {

        static_assert(
            sizeof...(Cs) == R,
            "Number of Rows must be equal to Tensor's Rows R"
        );
        
        // Assert each row size matches C
        static_assert(((Cs == C) && ...),
            "Each Row provided must have exactly C elements");

        std::cout << "Tensor's variadic constructor called" << std::endl;

    }

    // Copy Constructor
    Tensor(const Tensor& source){

        std::cout << "Tensor's copy constructor called" << std::endl;

        for (size_t i{}; i<R; ++i){

            rowVec[i] = source.rowVec[i];

        }
    }
    
    // Move Constructor
    Tensor(const Tensor&& source){

        std::cout << "Tensor's move constructor called" << std::endl;

        for (size_t i{}; i<R; ++i){

            rowVec[i] = source.rowVec[i];

        }

    }

    // Copy Assignment Operator
    Tensor& operator=(const Tensor& rhs){

        std::cout << "Tensor's copy assignment operator called" << std::endl;

        if (this == &rhs){
            return *this;
        }

        for (size_t i{}; i<R; ++i){

            rowVec[i] = rhs.rowVec[i];

        }

        return *this;
    }

    // Move Assignment Operator
    Tensor& operator=(const Tensor&& rhs){

        std::cout << "Tensor's move assignment operator called" << std::endl;

        if (this == &rhs){
            return *this;
        }

        for (size_t i{}; i<R; ++i){

            rowVec[i] = rhs.rowVec[i];

        }

        return *this;
    }

    // Default destructor
    ~Tensor() = default;


    /****************** Methods - Overloaded Operators ********************/

    // Subscript or Array Index Operator (Const overload for read-only access)
    
    const Vector<T, C>& operator[](size_t index) const{
        /*
            Matrix m;
            m[i]; returns reference of i-th row
            m[i][j]; returns the element of i-th row and j-th column    */

        if (index >= R) throw std::out_of_range("Index out of bounds");

        return rowVec[index];
    }

    

    // Subscript or Array Index Operator (Non-const overload for read/write access)
    Vector<T, C>& operator[](size_t index) {
        /*
            Matrix m;
            m[i]; returns reference of i-th row
            m[i][j]; returns the element of i-th row and j-th column    */

        if (index >= R) throw std::out_of_range("Index out of bounds");

        return rowVec[index];
    }

    
    // Subscript or Array Index Operator (Const overload for read-only access)
    const T&  operator[](size_t rowIndex, size_t columnIndex) const {
        /*
            Matrix m;
            m[i, j]; returns the element of i-th row and j-th column    */

        if (rowIndex >= R or columnIndex >= C) throw std::out_of_range("Index out of bounds");

        return (rowVec[rowIndex])[columnIndex];
    }

    // Subscript or Array Index Operator (Non-const overload for read/write access)
    T&  operator[](size_t rowIndex, size_t columnIndex) {
        /*
            Matrix m;
            m[i, j]; returns the element of i-th row and j-th column    */
        
        if (rowIndex >= R or columnIndex >= C) throw std::out_of_range("Index out of bounds");
        
        return (rowVec[rowIndex])[columnIndex];  
    }
   

    // Equal-to Operator (==)
    bool operator==(const Tensor& rhs) const {

        for (size_t i{}; i<R; ++i){

            if( not (rowVec[i] == rhs.rowVec[i]) ){
                return false; 
            }
            
        }

        return true;
    }

    // Not-Equal-to Operator (!=)
    bool operator!=(const Tensor& rhs) const {
        return !(*this == rhs);
    }

    // Addition Arithmetic Operator (+)
    Tensor operator+(const Tensor& rhs) const {
        
        Tensor temp{};

        for (size_t i{}; i<R; ++i){

            temp.rowVec[i] = rowVec[i] + rhs.rowVec[i];
        
        }

        return temp;
    }

    // Subtraction Arithmetic Operator (+)
    Tensor operator-(const Tensor& rhs) const {
        
        Tensor temp{};

        for (size_t i{}; i<R; ++i){

            temp.rowVec[i] = rowVec[i] - rhs.rowVec[i];
        
        }

        return temp;
    }

    // Compound Assignment Operator (+=)
    void operator+=(const Tensor& rhs) {

        for (size_t i{}; i<R; ++i){

            rowVec[i] += rhs.rowVec[i];
        
        }
    }

    // Compound Assignment Operator (-=)
    void operator-=(const Tensor& rhs) {
        
        for (size_t i{}; i<R; ++i){

            rowVec[i] -= rhs.rowVec[i];
        
        }
    }

    // scalar Multiplication Operator
    Tensor operator*(const T& scalar) const {
        Tensor scaledTensor {*this};

        for (size_t i{}; i<R; ++i){

            scaledTensor.rowVec[i] *= scalar;
        
        }

        return scaledTensor;
    }

    
    Vector<T, R> operator*(const Vector<T, C>& rhsVector) const {

        Vector<T, R> lhsVector{};

        for (size_t i{}; i<R; ++i){
            
            lhsVector[i] += rowVec[i].dot(rhsVector);

        }

        return lhsVector;

    }

};


template<typename T, size_t ... Cs>
Tensor(const T (&...arr)[Cs]) -> Tensor<T, sizeof...(arr), (Cs + ... + 0)/sizeof...(Cs)>;

#endif
