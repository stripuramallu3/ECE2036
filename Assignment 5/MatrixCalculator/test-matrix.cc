// Test program for ECE3090 Matrix assignmnet
// George F. Riley, Georgia Tech, Spring 2012

#include <iostream>
#include "matrix.h"

using namespace std;

int m1Expected[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
int m2Expected[12] = {10,20,30,40,50,  60, 70, 80,100,200,300,400};
int m3Expected[12] = {20,40,60,80,100,120,140,160,200,400,600,800};
int m4Expected[36] = {150,180,230,80,110,140,310,380,490,200,270,340,
                      470,580,750,320,430,540,630,780,1010,440,590,740,
                      1500,1800,2300,800,1100,1400,3100,3800,4900,2000,
                      2700,3400};

  
bool TestIt(const Matrix& m, int nRows, int nCols, int* expected)
{
  // verify correct contents
  int expectedInd = 0;
  bool passed = true;
  for (int r = 0; r < nRows; ++r)
    { // For each row
      for (int c = 0; c < nCols; ++c)
        { // For each col
          int v = m.At(r,c);  // Value in row r col c
          int e = expected[expectedInd++];
          if (v != e)
            {
              cout << "Oops, row " << r << " col " << c
                   << " expected " << e
                   << " found " << v << endl;
              passed = false;
            }
        }
    }
  // m should NOT be NaM
  if (m.IsNaM())
    {
      cout << "Oops, not a matrix" << endl;
      passed = false;
    }
  return passed;
}

int main()
{
  static int failedCount = 0;
  Matrix a("(1,2,3),(4,5,6),(7,8,9)");
  a.Print();
  if (!TestIt(a, 3, 3, m1Expected))
    {
      cout << "Test 1 failed" << endl;
      failedCount++;
    }
  // Check non-square matrix
  Matrix b("(10,20),(30,40),(50,60),(70,80),(100,200),(300,400)");
  b.Print();
  if (!TestIt(b, 6, 2, m2Expected))
    {
      failedCount++;
      cout << "Test 2 failed" << endl;
    }
  // Check copy constructor and addition
  Matrix c(b);
  Matrix d = b + c;
  d.Print();
  if (!TestIt(d, 6, 2, m3Expected))
    {
      failedCount++;
      cout << "Test 3 failed" << endl;
    }
  // Check self-assignmennt
  d = d;
  d.Print();
  if (!TestIt(d, 6, 2, m3Expected))
    {
      failedCount++;
      cout << "Test 4 failed" << endl;
    }
  // a + b shold fail, not same dimensions
  c = a + b;
  if (!c.IsNaM())
    {
      failedCount++;
      cout << "test 5 failed" << endl;
    }
  
  // Check non-square multiplication
  Matrix e("(1,2,3,4,5,6),(7,8,10,2,3,4)");
  Matrix f = b * e;
  f.Print();
  if (!TestIt(f, 6, 6, m4Expected))
    {
      failedCount++;
      cout << "Test 6 failed" << endl;
    }
  
  Matrix g = e * a; // Should be NaM
  if (!g.IsNaM())
    {
      failedCount++;
      cout << "Test 7 failed" << endl;
    }
  // Check assignment operator
  a = b;
  a.Print();
  if (!TestIt(a, 6, 2, m2Expected))
    {
      failedCount++;
      cout << "Test 8 failed" << endl;
    }
  if (failedCount == 0)
    {
      cout << "All tests passed!" << endl;
    }
  else
    {
      cout << failedCount << " tests failed" << endl;
    }
}


