//
// ECE2036 Program 2 - Matrix Class decaration
// (your name here)
//

// Class declaration for Matrix class
// ECE2036 Lab 5

#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <math.h>
#include <iostream>
#include <iomanip>

typedef int          Element_t; // Type for each matrix eleemnt
typedef unsigned int Index_t;   // Type for row/col sizes

class Matrix {
public:
  //Constructors and destructor
    Matrix(const std::string& matrix);
    Matrix(unsigned int numRows, unsigned int numCols);
    Matrix();
    Matrix(const Matrix &obj);
    ~Matrix();
  // Define overloaded operators here, including assignment operator
  // Required member functions here
    Element_t& At(Index_t row, Index_t col) const;
    bool IsNaM() const;
  // Data Members
    Element_t* elements;
    Index_t numRows;
    Index_t numCols;
    bool NaM;
  // You will probably want more here
public:
  // Insert members here
    Matrix& operator=(const Matrix& rhs);
    Matrix operator+(const Matrix& rhs) const;
    Matrix operator-(const Matrix& rhs) const;
    Matrix operator*(const Matrix& rhs) const;
    void Print(); 

};

#endif
