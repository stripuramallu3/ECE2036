//
// ECE2036 Program 5 - Matrix Class implementation
// Sreeramamurthy Tripuramallu 
//

#include <iostream>
#include <vector>

#include "matrix.h"
#include "string-parse.h"

using namespace std;

// Constructors here
Matrix::Matrix(const std::string& matrix) {
    // Variable Initialization
    StringVec_t rows;
    StringVec_t rowElements;
    CharVec_t delims;
    NaM = false;
    // Make commas consistent across rows.
    // Find dimensions.
    numRows = StringParse(matrix, ",", rows, delims);
    std::string temp = RemoveParens(rows[0]);
    numCols = StringParse(temp, ",", rowElements, delims);
    // Initialize element array
    if (numCols == 0) {
        NaM = true; 
    }
    elements = new Element_t[numRows * numCols];
    // Loop through rows.
    Index_t count = 0;
    std::string row;
    for (Index_t i = 0; i < numRows; i++) {
        row = RemoveParens(rows[i]);
        StringParse(row, ",", rowElements, delims);
        for (Index_t j = 0; j < numCols; j++) {
            elements[count] = ToElement(rowElements[j]);
            count++;
        }
    }
}
// Other constructors for Matrix
Matrix::Matrix(unsigned int r, unsigned int c) {
    NaM = false;
    elements = new Element_t[r * c];
    numRows = r;
    numCols = c;
    for (Index_t i = 0; i < numRows * numCols; i++) {
        elements[i] = 0;
    }
}

Matrix::Matrix() {
    NaM = true;
    elements = new Element_t[0];
    numRows = 0;
    numCols = 0;
}

Matrix::Matrix(const Matrix& rhs) {
    if (this != &rhs) {
        numRows = rhs.numRows;
        numCols = rhs.numCols;
        NaM = rhs.NaM;
        elements = new Element_t[numRows * numCols];
        for (Index_t i = 0; i < numRows * numCols; i++) {
            elements[i] = rhs.elements[i];
        }
    }
}
// Destructors here
Matrix::~Matrix(void) {
    delete [] elements;
}

Element_t& Matrix::At(Index_t row, Index_t col) const {
    return elements[row*numCols + col];
}

bool Matrix::IsNaM() const {
    return NaM;
}
// Operators here (Matrix addition, subtraction, multiplication)
Matrix& Matrix::operator=(const Matrix& rhs) {
    if (this != &rhs) {
        numRows = rhs.numRows;
        numCols = rhs.numCols;
        NaM = rhs.NaM;
        elements = new Element_t[numRows * numCols];
        for (Index_t i = 0; i < numRows * numCols; i++) {
            elements[i] = rhs.elements[i];
        }
    }
    return *this;

}
Matrix Matrix::operator+(const Matrix& rhs) const {
    if (numRows == rhs.numRows && numCols == rhs.numCols && !IsNaM() && !rhs.IsNaM()) {
        Matrix other(numRows, numCols);
        for (Index_t i = 0; i < numCols * numRows; i++) {
            other.elements[i] = elements[i] + rhs.elements[i];
        }
        return other;
    } else {
        Matrix other;
        return other;
    }
}

Matrix Matrix::operator-(const Matrix& rhs) const {
    if (numRows == rhs.numRows && numCols == rhs.numCols && !IsNaM() && !rhs.IsNaM()) {
        Matrix temp(numRows, numCols);
        for (Index_t i = 0; i < numCols * numRows; i++) {
            temp.elements[i] = elements[i] - rhs.elements[i];
        }
        return temp;
    } else {
        Matrix temp;
        return temp;
    }
}

Matrix Matrix::operator*(const Matrix& rhs) const {
    if (numCols == rhs.numRows && !IsNaM() && !rhs.IsNaM()) {
        Matrix temp(numRows, rhs.numCols);
        for (Index_t i = 0; i < numRows; i++) {
            for (Index_t j = 0; j < rhs.numCols; j++) {
                for (Index_t k = 0; k < numCols; k++) {
                    temp.At(i, j) += At(i, k) * rhs.At(k, j);
                }
            }
        }
        return temp;
    } else {
        Matrix temp;
        return temp;
    }  
}
// Other member functions here
void Matrix::Print() {
    if (!IsNaM()) {
        for (Index_t i = 0; i < numRows; i++) {
            for (Index_t j = 0; j < numCols; j++) {
                cout << setfill(' ') << setw(5) << At(i, j);
            }
            cout << endl;
        }
    } else {
        cout << "NaM" << endl;
    }
  cout << endl;
}

