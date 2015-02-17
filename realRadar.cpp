#include "realRadar.h"
#include <pthread.h>
#include <stdio.h>
#include <iostream>
using namespace std;
# include <stdlib.h>


RealRadar::~RealRadar()
{  /* Last thing that main() should do */
    pthread_exit(NULL);
}

bool    RealRadar::update() { return true; }
char*   RealRadar::getLastError() { return 0; }
bool    RealRadar::uninitialize() { return true; }
bool    RealRadar::getNextBody(Body& body) { return true; }


void *PrintHello2(void *threadid)
{
   long tid;
   tid = (long)threadid;
   printf("Radar thread #%ld!\n", tid);
   pthread_exit(NULL);
}

bool RealRadar::initialize()
{
    //return true if the thread was created successfully
    int rc;






       printf("In main: creating thread %ld\n");
       rc = pthread_create(&thread, NULL, PrintHello2, NULL);
       if (rc){
          printf("ERROR; return code from pthread_create() is %d\n", rc);
          exit(-1);
       }



   return rc;
}


