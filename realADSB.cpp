#include "realADSB.h"
#include <pthread.h>
#include <stdio.h>
# include <stdlib.h>

RealADSB::~RealADSB()
{/* Last thing that main() should do */
    pthread_exit(NULL);
}

bool    RealADSB::update() { return true; }
char*   RealADSB::getLastError() { return 0; }
bool    RealADSB::uninitialize() { return true; }

bool    RealADSB::getMessageType(char** messageType) { return true; }
bool    RealADSB::getTransmissionType(int& transType) { return true; }
bool    RealADSB::getHexIdent(char** hexIdent) { return true; }
bool    RealADSB::getFlightID(int& flightID) { return true; }
bool    RealADSB::getAltitude(int& altitude) { return true; }
bool    RealADSB::getGroundSpeed(int& groundSpeed) { return true; }
bool    RealADSB::getLatitude(float& lat) { return true; }
bool    RealADSB::getLongitude(float& lon) { return true; }
bool    RealADSB::getTrack(int& track) { return true; }
bool    RealADSB::getDeltaTime(int& deltaTime) { return true; }

void *PrintHello(void *threadid)
{
   long tid;
   tid = (long)threadid;
   printf("ADS-B thread #%ld!\n", tid);
   pthread_exit(NULL);
}

bool RealADSB::initialize()
{
    //return true if the thread was created successfully
    int rc;

       printf("In main: creating thread %ld\n");
       rc = pthread_create(&thread, NULL, PrintHello, NULL);
       if (rc){
          printf("ERROR; return code from pthread_create() is %d\n", rc);
          exit(-1);
       }


   return rc;
}
