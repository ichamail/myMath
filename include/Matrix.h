#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <iostream>
#include <type_traits>
#include "core.h"
#include "Vector.h"

template<typename T, size_t R, size_t C>
class Matrix{

    static_assert(
        std::is_arithmetic<T>::value,
        "Matrix class can only store integral or floating point values"
    );

    static_assert(
        R >= 2, "Number of Matrix Rows R should be higher or equal to 2"
    );

    static_assert(
        C >= 2, "Number of Matrix Columns C should be higher or equal to 2"
    );


    friend std::ostream& operator<<(
        std::ostream& os, const Matrix& matrix    //const Vecotr<T, N>& vector
    ){
        for (size_t i{}; i < R; ++i){
            for (size_t j{}; j < C; ++j){
                os << matrix.element[i][j] << " ";
            }
            if (i != R-1) {os << std::endl;}
        }
        return os;
    }

    friend Matrix operator*(const T&& scalar, const Matrix& matrix){
        return matrix * scalar;
    }

    friend Matrix operator*(const T& scalar, const Matrix& matrix){
        return matrix * scalar;
    }


    private:

        T element[R][C];    // array to store matrix elements


        // template<typename CstyleArray>
        // void assignRow(size_t rowIndex, const CstyleArray& row) {
        //     for (size_t i = 0; i < C; ++i) {
        //         element[rowIndex][i] = row[i];
        //     }
        // }

        // template<typename CstyleArray, typename... CstyleArrays>
        // void assignRow(
        //     size_t rowIndex, const CstyleArray& row, const CstyleArrays&... rows
        // ) {
        //     assignRow(rowIndex, row);
        //     assignRow(rowIndex + 1, rows...);  
        // }

    public:

    /******** Constructors - Assignment Operators - Destructor ***************/

    // Default Constructor
    Matrix(): element{} {
        std::cout << "Matrix's default constructor called" << std::endl;
    }

    // Variadic Template Constructor
    template<size_t ... Cs>
    Matrix(const T (&...rows)[Cs]): Matrix{} {

        static_assert(
            sizeof...(Cs) == R,
            "Number of Rows must be equal to Matrix's Rows R"
        );
        
        static_assert(((Cs == C) && ...),
            "Each Row provided must have exactly C elements");

        std::cout << "Matrix's variadic constructor called" << std::endl;
        
        const T* ptrElement[R] {rows...};

        for (size_t i{}; i<R; ++i){
            for (size_t j{}; j<C; ++j){
                element[i][j] = ptrElement[i][j];
            }
        }

        // assignRow(0, rows...);

        // Fold expression with a lambda function
        // size_t i{};
        // (
        //     (
        //     [&]() {
        //         for (size_t j{}; j<C; ++j) {
        //             element[i][j] = rows[j];  // Copy each element of the row
        //         }
        //         ++i;  // Move to the next row
        //     }(), 0
        //     ), ... 
        // );
    }

    // Copy Constructor
    Matrix(const Matrix& source){

        std::cout << "Matrix's copy constructor called" << std::endl;

        for (size_t i{}; i<R; ++i){

            for (size_t j{}; j<C; ++j){
                element[i][j] = source.element[i][j];
            }

        }
    }
    
    // Move Constructor
    Matrix(const Matrix&& source){

        std::cout << "Matrix's move constructor called" << std::endl;

        for (size_t i{}; i<R; ++i){

            for (size_t j{}; j<C; ++j){

                element[i][j] = source.element[i][j];
            }

        }

    }

    // Copy Assignment Operator
    Matrix& operator=(const Matrix& rhs){

        std::cout << "Matrix's copy assignment operator called" << std::endl;

        if (this == &rhs){
            return *this;
        }

        for (size_t i{}; i<R; ++i){

            for (size_t j{}; j<C; ++j){
                element[i][j] = rhs.element[i][j];
            }

        }

        return *this;
    }

    // Move Assignment Operator
    Matrix& operator=(const Matrix&& rhs){

        std::cout << "Matrix's move assignment operator called" << std::endl;

        if (this == &rhs){
            return *this;
        }

        for (size_t i{}; i<R; ++i){

            for (size_t j{}; j<C; ++j){
                element[i][j] = rhs.element[i][j];
            }

        }

        return *this;
    }

    // Default destructor
    ~Matrix() = default;


    /****************** Methods - Overloaded Operators ********************/

    // Subscript or Array Index Operator (Const overload for read-only access)
    // typedef T oneDimTtypedArr [C];
    // const oneDimTtypedArr& operator[](size_t index) const{
    //     /*
    //         Matrix m;
    //         m[i]; returns reference of i-th row
    //         m[i][j]; returns the element of i-th row and j-th column    */

    //     return element[index];
    // }

    // Subscript or Array Index Operator (Const overload for read-only access)
    const T ( & operator[](size_t index) const  )[C] {
        // just a fancy definition of the above operator overload
        /*
            Matrix m;
            m[i]; returns reference of i-th row
            m[i][j]; returns the element of i-th row and j-th column    */

        if (index >= R) throw std::out_of_range("Index out of bounds");

        return element[index];
    }

    // Subscript or Array Index Operator (Non-const overload for read/write access)
    // oneDimTtypedArr& operator[](size_t index) {
    //     /*
    //         Matrix m;
    //         m[i]; returns reference of i-th row
    //         m[i][j]; returns the element of i-th row and j-th column    */

    //     return element[index];
    // }

    // Subscript or Array Index Operator, (Non-const overload for read/write access)
    T ( & operator[](size_t index) )[C] {
        // just a fancy definition of the above operator overload

        /*
            Matrix m;
            m[i]; returns reference of i-th row
            m[i][j]; returns the element of i-th row and j-th column    */

        if (index >= R) throw std::out_of_range("Index out of bounds");

        return element[index];
    }

    // Subscript or Array Index Operator (Const overload for read-only access)
    const T&  operator[](size_t rowIndex, size_t columnIndex) const {
        /*
            Matrix m;
            m[i, j]; returns the element of i-th row and j-th column    */

        if (rowIndex >= R or columnIndex >= C) throw std::out_of_range("Index out of bounds");

        return element[rowIndex][columnIndex];
    }

    // Subscript or Array Index Operator (Non-const overload for read/write access)
    T&  operator[](size_t rowIndex, size_t columnIndex) {
        /*
            Matrix m;
            m[i, j]; returns the element of i-th row and j-th column    */
        
        if (rowIndex >= R or columnIndex >= C) throw std::out_of_range("Index out of bounds");

        return element[rowIndex][columnIndex];  
    }
   

    // Equal-to Operator (==)
    bool operator==(const Matrix& rhs) const {

        for (size_t i{}; i<R; ++i){

            for (size_t j{}; j<C; ++j){

                if ( not isEqual(element[i][j], rhs.element[i][j]) ){
                    return false;
                }

            }

        }

        return true;
    }

    // Not-Equal-to Operator (!=)
    bool operator!=(const Matrix& rhs) const {
        return !(*this == rhs);
    }

    // Addition Arithmetic Operator (+)
    Matrix operator+(const Matrix& rhs) const {
        
        Matrix temp{};

        for (size_t i{}; i<R; ++i){

            for (size_t j{}; j<C; ++j){

                temp.element[i][j] = element[i][j] + rhs.element[i][j];

            }
        
        }

        return temp;
    }

    // Subtraction Arithmetic Operator (+)
    Matrix operator-(const Matrix& rhs) const {
        
        Matrix temp{};

        for (size_t i{}; i<R; ++i){

            for (size_t j{}; j<C; ++j){

                temp.element[i][j] = element[i][j] - rhs.element[i][j];

            }
        
        }

        return temp;
    }

    // Compound Assignment Operator (+=)
    void operator+=(const Matrix& rhs) {

        for (size_t i{}; i<R; ++i){

            for (size_t j{}; j<C; ++j){

                element[i][j] += rhs.element[i][j];

            }
        
        }
    }

    // Compound Assignment Operator (-=)
    void operator-=(const Matrix& rhs) {
        
        for (size_t i{}; i<R; ++i){

            for (size_t j{}; j<C; ++j){

                element[i][j] -= rhs.element[i][j];

            }
        
        }
    }

    // scalar Multiplication Operator
    Matrix operator*(const T& scalar) const {
        Matrix scaledMatrix {*this};

        for (size_t i{}; i<R; ++i){

            for (size_t j{}; j<C; ++j){

                scaledMatrix.element[i][j] *= scalar;

            }
        
        }

        return scaledMatrix;
    }

    template<size_t C_rhs>
    Matrix<T, R, C_rhs> operator*(const Matrix<T, C, C_rhs>& rhs) const {
        
        Matrix<T, R, C_rhs> resMat {};
        
        for (size_t i{}; i<R; ++i){

            for (size_t j{}; j<C_rhs; ++j){

                for (size_t k{}; k<C; ++k){

                    resMat[i][j] += element[i][k] * rhs[k][j];

                    //or
                    // resMat[i, j] += element[i][k] * rhs[k, j];

                }

            }

        }

        return resMat;

    }

    Vector<T, R> operator*(const Vector<T, C>& rhsVector) const {

        Vector<T, R> lhsVector{};

        for (size_t i{}; i<R; ++i){
            
            for (size_t j{}; j<C; ++j){

                lhsVector[i] += element[i][j] * rhsVector[j];

            }
        }

        return lhsVector;

    }

};

template<typename T, size_t ... Cs>
Matrix(const T (&...arr)[Cs]) -> Matrix<T, sizeof...(arr), (Cs + ... + 0)/sizeof...(Cs)>;

#endif
