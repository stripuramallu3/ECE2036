// Parallel Numerical Integration
// ECE2893 Assignment 7, Spring 2011
// Sreeramamurthy Tripuramallu

#include <stdio.h>
#include <math.h>
#include "gthread.h"

// The typedef below defines whether we are using 32-bit float
// or 64-bit double for all of the floating point values.  Your program
// should use this type (MyFloat_t) for all variables that use floating
// point.
typedef MYFLOAT  MyFloat_t;
MyFloat_t totalArea;
gthread_mutex_t m;

MyFloat_t getValue(MyFloat_t x) {
  return (23.864*x*x*x) + (5.7*x*x) - (173.1*x) + 10.523; 
}
void riemannSum(MyFloat_t start, MyFloat_t length, MyFloat_t deltaX) {
  MyFloat_t sumArea = 0;
  MyFloat_t loop = length/deltaX;
  MyFloat_t current = start; 
  for (int k = 0; k < loop; k++) {
    current = start + k*deltaX; 
    sumArea += (((getValue(current)/2.0) + (getValue(current + deltaX)/2.0)) * deltaX);
  }
  LockMutex(m);
  totalArea += sumArea;
  UnlockMutex(m);
  EndThread();
}

// The below is the "correct" value, determined by evaluating the
// integral and computing the area.  This is used when computing
// the "error" for the numerical integration calculations.
// Also, this is the only place in the program where the type "double"
// is to be used.  Everywhere else, you should use type MyFloat_t.
double correct = 5.9763555230000e+08;

// The below global variable is used by the threads to update the
// total area of the integral.  You will need mutex protection before
// updating this variable.

int main()
{
  // Print out whether using float or double
  if (sizeof(MyFloat_t) == 4)
    {
      printf("Using float\n");
    }
  else
    {
      printf("Using double\n");
    }
  // Your code here.  You need to loop 7 times with 7 different
  // deltaX values, as described in the assignment.  For each of
  // the 7 iterations, create 10 threads and compute the integral
  // numerically using the Riemann sum metthod.  After all 10 threads
  // have completed, print out the deltaX value, the computed integral
  // and the error.
  totalArea = 0;
  MyFloat_t deltaX = 10;
  MyFloat_t start = 0.0;
  MyFloat_t end = 100.0;
  MyFloat_t length = (end - start) / deltaX;
  for (int i = 0; i < 7; i++) {
    deltaX = deltaX/10;
    for (int j = 0; j < 10; j++) {
      CreateThread(riemannSum, start, length, deltaX);
      start += length;
    }
    WaitAllThreads();
    MyFloat_t error = fabs(totalArea - correct);
    MyFloat_t relError = error/correct; 
    printf("DeltaX: %3.6f, Area: %15.13e, Error: %15.13e, Rel.Error: %15.13e\n", deltaX, totalArea, error, relError);
    totalArea = 0;
    start = 0;
  }
}




