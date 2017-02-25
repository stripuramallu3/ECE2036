//
// ECE2036 Program 2 - Matrix Calculator
// Sreeramamurthy Tripuramallu 
//

#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "matrix.h"
#include "string-parse.h"

using namespace std;

int main()
{
  Matrix first;
  Matrix second;
 // Your declarations here
    while(true)
    {
        StringVec_t    operands;
        CharVec_t      delim;
        string         line;
        line = GetStringFromKeyboard(); // Read input line
        int count = StringParse(line, "+-*", operands, delim);
        if (!count) break; // All done
        // Now perform the calculation
        if (count == 2 && operands[0] != "") {
            first = Matrix(operands[0]);
            second = Matrix(operands[1]);
        } else if (count == 2) {
            second = Matrix(operands[1]);
        } else {
            first = Matrix(operands[0]);
        }

        if (delim[0] == '\0') {
            first.Print();
        } else if (delim[0] == '+') {
            first = first + second;
            first.Print();
        } else if (delim[0] == '-') {
            first = first - second;
            first.Print();
        } else if (delim[0] == '*') {
            first = first * second;
            first.Print();
        }

        // Your code here
        first = first; // !! Leave this here to test proper self-assignment
        }
return 0;  /* Successful completion of main() */
}
