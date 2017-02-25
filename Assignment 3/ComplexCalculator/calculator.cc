//
// EC20360 Program 2 - Complex Number Calculator
// Sreeramamurthy Tripuramallu
//

#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "complex.h"
#include "string-parse.h"

using namespace std;

int main()
{
  // Add any variables you might need here
  Complex old; 

  while(true)
    {
      string st = GetStringFromKeyboard(); // Get the  next input line
      // The types StringArray_t and CharArray_t are defined in string-parse.h
      // They are fixed length arrays of 2 elements.
      // The StringParse function returns an integer indicating how many
      // of the two are actually used.
      StringArray_t operands; // array of operands
      CharArray_t   delims;   // array of delimiters
      int count = StringParse(st, "+-*/", operands, delims);
      if (count == 0) break; // All done

      // Now perform the calculation
      Complex c1, c2, cNew; 
      const std::string& A = operands[0]; 
      const std::string& B = operands[1]; 
      char op = delims[0]; 
      if (count == 1) {
          cNew = Complex(A); 
      } else {
          if (A.length() == 0) {
            c1 = old;  
          } else {
            c1 = Complex(A); 
          }
          c2 = Complex(B); 
          switch(op) {
            case '+':
              cNew = c1 + c2; 
              break; 
            case '-':
              cNew = c1 - c2; 
              break;  
            case '*':
              cNew = c1 * c2; 
              break; 
            case '/': 
              cNew = c1/c2; 
              break; 
            default :
              cNew = Complex(); 
              break; 
          }
        }
      cNew.Print(); 
      old = cNew; 
    }
  return 0;  // Successful completion of main()
}

