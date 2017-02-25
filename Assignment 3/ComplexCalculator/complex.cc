//
// ECE2036 Program 2 - Complex Number Class implementation
// Sreeramamurthy Tripuramallu
//

#include <iostream>
#include <string>

#include <math.h>

#include "complex.h"
#include "string-parse.h"

using namespace std;

// Implement your constructors here
// Constructors

Complex::Complex()
:real(0),imag(0),notANumber(true) {}

Complex::Complex(double r, double i)
:real(r), imag(i), notANumber(true) {}

Complex::Complex(const string& str) {
	string temp = str;
	if (str[0] == '(') {
		temp = RemoveParens(str);
	}
	StringArray_t operators;
	CharArray_t delims;
	StringParse(temp, ",>", operators, delims);
	if (delims[0] == ',') {
		real = ToDouble(operators[0]);
		imag = ToDouble(operators[1]);
	} else if (delims[0] == '>') {
		real = ToDouble(operators[0]) * cos(ToDouble(operators[1]) * (M_PI/180));
		imag = ToDouble(operators[0]) * sin(ToDouble(operators[1]) * (M_PI/180));
	} else if (delims[0] == '0') {
		real = ToDouble(operators[0]);
		imag = 0;
	} else {
		cout << "Error in String Conversion" << endl;
	}
	notANumber = true; 
}

// Implement your other member functions here
// Member functions
double Complex::calcMag() {
	return sqrt(pow(real,2) + pow(imag, 2));
}

double Complex::calcAngle() {
	return atan2(imag, real) * (180/M_PI);
}
Complex Complex::calcConj() {
	return Complex(real, -1*imag);
}
void Complex::Print() {
	if (notANumber) {
		if (imag == 0) {
			cout << " = " << real << endl;
		} else {
			cout << " = (" << real << "," << imag << ")" << endl;
		}
	} else {
		cout << " = NaN" << endl;
	}
}

// Implement your operators here
// Operators
Complex Complex::operator+(Complex rhs) {
	if (notANumber && rhs.notANumber) {
		Complex result(real + rhs.real, imag + rhs.imag); 
		return result; 
	} else {
		rhs.notANumber = false; 
		return rhs; 
	}
} 

Complex Complex::operator-(Complex rhs) {
	if (notANumber && rhs.notANumber) {
		Complex result(real - rhs.real, imag-rhs.imag); 
		return result; 
	} else {
		rhs.notANumber = false; 
		return rhs; 
	}
}

Complex operator*(Complex lhs, Complex rhs) {
	if (lhs.notANumber && rhs.notANumber) {
		double tempReal = lhs.real*rhs.real - lhs.imag*rhs.imag; 
  		double tempImag = lhs.imag*rhs.real + rhs.imag*lhs.real; 
    	Complex result(tempReal, tempImag); 
    	return result; 
	} else {
		lhs.notANumber = false; 
		return lhs; 
	}
}

Complex operator/(Complex lhs, Complex rhs) {
	if (lhs.notANumber && rhs.notANumber) {
		if (rhs.calcMag() == 0) {
			lhs.notANumber = false;  
			return lhs; 
		}
		Complex temp = lhs*rhs.calcConj();
		double mag = rhs.calcMag()*rhs.calcMag(); 
		Complex result((temp.real)/mag, (temp.imag)/mag); 
		return result;  
	} else {
		lhs.notANumber = false; 
		return lhs; 
	}
}
