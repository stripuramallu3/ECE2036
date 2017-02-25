#include <iostream>
#include "gthread.h"

using namespace std;


gthread_mutex_t m;
unsigned int    globalCount = 0;
int loopPerThread = 100000;
int nThreads = 10;
int pass = 0;

void TestG(int myid)
{
  for (int i = 0; i < loopPerThread; ++i)
    {
      LockMutex(m);
      globalCount++;
      UnlockMutex(m);
      if (myid == 0 && (i % 1000) == 0) cout << "pass " << pass << " id 0 " << " i " << i << endl;
    }
  EndThread();
}

int main()
{
  for (pass = 0; pass < 10; ++pass)
    {
      globalCount = 0;
      for (int i = 0; i < nThreads; ++i)
        {
          CreateThread(TestG, i);
        }
      WaitAllThreads();
      cout << "Count is " << globalCount << endl;
      if (globalCount == loopPerThread * nThreads)
        {
          cout << "Correct!" << endl;
        }
      else
        {
          cout << "Mismatch!" << endl;
        }
    }
}



  
