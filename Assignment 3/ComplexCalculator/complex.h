//
// ECE20360 Program 2 - Complex Number Class decaration
// Sreeramamurthy Tripuramallu 
//

// Class declaration for Complex number class
// ECE3090 Lab 1

#include <iostream>
#include <string>

class Complex {
public: 
  // Define your constructors here
  // Constructors
  Complex(); 
  Complex(double r, double i);
  //String Parsing Constructor 
  Complex(const std::string& str); 
  // Define the other required member functions here
  // Member Functions
  double calcMag(); 	//Calculates the magnitude of two complex numbers
  double calcAngle();   //Calculates the angle between two complex numbers
  Complex calcConj(); 	//Calculates the conjugate of a complex number 
  void Print();			//Prints the complex number

  // Define your operator overloads here if using member function overloads
  Complex operator+(Complex rhs); 
  Complex operator-(Complex rhs); 
  // Define your Data Members here
  // Data Members
public:
	double real; 
	double imag; 
	bool notANumber; 
};

// Define your operator overloads here if using non-member function
// operator overloads.
Complex operator*(Complex lhs, Complex rhs);
Complex operator/(Complex lhs, Complex rhs);





