#include "realADSB.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <cstring>
#include <iostream>
using namespace std;

RealADSB::RealADSB(): ADSBModule(), errorFlag(false) {}

RealADSB::~RealADSB()
{/* Last thing that main() should do */
    pthread_exit(NULL);
}

bool    RealADSB::update() { return true; }
char*   RealADSB::getLastError() { return 0; }
bool    RealADSB::uninitialize() { return true; }

bool RealADSB::getObjectCount(int& numObjects){
     numObjects=visibleAircraft.size();
     return true;
}

bool    RealADSB::getHexIdent(int index, char** hexIdent) {
        *hexIdent = visibleAircraft[index].hex_ident;
        return true;
}
bool    RealADSB::getAltitude(int index, float& altitude) {
        altitude =  visibleAircraft[index].altitude;
        return true;
}
bool    RealADSB::getGroundSpeed(int index, float& groundSpeed) {
        groundSpeed = visibleAircraft[index].groundSpeed;
        return true;
}
bool    RealADSB::getLatitude(int index, float& latitude) {
        latitude = visibleAircraft[index].latitude;
        return true;
}
bool    RealADSB::getLongitude(int index, float& longitude) {
        longitude = visibleAircraft[index].longitude;
        return true;
}
bool    RealADSB::getTrack(int index, float& track) {
        track = visibleAircraft[index].track;
        return true;
}
bool    RealADSB::getCallSign(int index, char** callSign){
        *callSign = visibleAircraft[index].callSign;
        return true;
}

bool    RealADSB::getTimeStamp(int index, int& timeStamp)  { return true; }

void *RealADSB::ADSBClientThread(void *object)
{
 //  pthread_exit(NULL);
   RealADSB* adsb = (RealADSB*)object;



   int sockfd, portno, n;
   struct sockaddr_in serv_addr;
   struct hostent *server;
	positionMSG newMsg;

   char buffer[256];
   portno = atoi(ADSB_PORTNUMBER);
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if (sockfd < 0)
        fprintf(stderr,"ERROR opening socket\n");
   server = gethostbyname(ADSB_HOSTNAME);
   if (server == NULL) {
       fprintf(stderr,"ERROR, no such host\n");
       exit(0);
   }
   bzero((char *) &serv_addr, sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
   bcopy((char *)server->h_addr,
        (char *)&serv_addr.sin_addr.s_addr,
        server->h_length);
   serv_addr.sin_port = htons(portno);
   if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
       fprintf(stderr,"ERROR connecting\n");



while(true) {

   bzero(buffer,256);
   n = read(sockfd,buffer,255);
   if (n < 0)
        fprintf(stderr,"ERROR reading from socket\n");
  // printf("%s\n",buffer);

	char* buffPtr = buffer;
   char * token;
   token = strsep (&buffPtr, ",");
   int count = 0;
   bool flag = false;
   int currentIndex = -1;
   int transmission_type;
   int emptyIndex = -1;






   while(count < 22)
   {
		if(token) {
       switch(count){

       case ADSBModule::MSG_TYPE:
           if(strcmp(token, "MSG")!= 0)
               flag = true;
            break;
       case ADSBModule::TRANSMISSION_TYPE:
              if (strcmp(token, "3")==0){
                  transmission_type = 3;
              }
              else if (strcmp(token, "4")==0){
                  transmission_type = 4;
              } else if(strcmp(token, "1") == 0) {
						transmission_type = 1;
					} else if(strcmp(token, "6") == 0) {
						transmission_type = 6; 
					} else { 
						flag = true;
					}
            break;
       case ADSBModule::SESSION_ID:
            break;
       case ADSBModule::AIRCRAFT_ID:
				printf("Aircraft ID - %s\n",  token);
           break;
       case ADSBModule::HEX_IDENT:
           for (int i=0; i<adsb->visibleAircraft.size(); i++){
               if(strcmp(token, adsb->visibleAircraft[i].hex_ident)==0){
                   currentIndex = i; //found in array
							break;
               }
           }
           if(currentIndex == -1) { //wasn't found in the array
                  strcpy( newMsg.hex_ident, token); //insert new identifier
						adsb->visibleAircraft.push_back(newMsg);
						currentIndex = adsb->visibleAircraft.size()-1;
           }
           break;
       case ADSBModule::FLIGHT_ID:
				printf("Flight ID - %s\n", token);
           break;
       case ADSBModule::DATE_GEN:
           break;
       case ADSBModule::TIME_GEN:
           break;
       case ADSBModule::DATE_LOG:
           break;
       case ADSBModule::TIME_LOG:
           break;
       case ADSBModule::CALLSIGN:
           strcpy(adsb->visibleAircraft[currentIndex].callSign, token);
           break;
       case ADSBModule::ALTITUDE:
           if(transmission_type==3)
                 adsb->visibleAircraft[currentIndex].altitude = atof(token);
           break;
       case ADSBModule::GROUND_SPEED:
           if(transmission_type==4)
                 adsb->visibleAircraft[currentIndex].groundSpeed = atof(token);
           break;
       case ADSBModule::TRACK:
            if(transmission_type==4)
                  adsb->visibleAircraft[currentIndex].track = atof(token);
           break;
       case ADSBModule::LATITUDE:
           if(transmission_type==3)
              adsb->visibleAircraft[currentIndex].latitude = atof(token);
           break;
       case ADSBModule::LONGITUDE:
           if(transmission_type==3) 
              adsb->visibleAircraft[currentIndex].longitude = atof(token);
           break;
       case ADSBModule::VERTICAL_RATE:
           break;
       case ADSBModule::SQUAWK:
           break;
       case ADSBModule::ALERT:
           break;
       case ADSBModule::EMERGENCY:
           break;
       case ADSBModule::SPI:
           break;
       case ADSBModule::IS_ON_GROUND:
           break;
       default:
           break;

       }

		//printf("TOKEN - %s\n",token);
}

       count++;
       token=strsep(&buffPtr, ",");
			

        if(flag) break;
   }

if(currentIndex != -1 && !flag) {
	printf("AIRCRAFT #%d\n", currentIndex);
           printf("\tHEXIDENT = %s\n", adsb->visibleAircraft[currentIndex].hex_ident);
				//printf("\tFLIGHTID = %d\n", adsb->visibleAircraft[currentIndex].flightId);
           printf("\tCALL SIGN = %s\n", adsb->visibleAircraft[currentIndex].callSign);
           printf("\tLATITUDE = %f\n", adsb->visibleAircraft[currentIndex].latitude);
           printf("\tLONGITUDE = %f\n", adsb->visibleAircraft[currentIndex].longitude);
           printf("\tALTITUDE = %f\n", adsb->visibleAircraft[currentIndex].altitude);
           printf("\tGROUND_SPEED = %f\n", adsb->visibleAircraft[currentIndex].groundSpeed);
           printf("\tTRACK = %f\n", adsb->visibleAircraft[currentIndex].track);
}
}

  close(sockfd);
   return 0;
}

bool RealADSB::initialize()
{
    //return true if the thread was created successfully
    int rc;

       printf("In main: creating adsb message thread %ld\n");
       rc = pthread_create(&thread, NULL, &ADSBClientThread, this);
       if (rc){
          printf("ERROR in adsb message thread; return code from pthread_create() is %d\n", rc);
          errorFlag=true;
         // exit(-1);
       }


   return rc;
}
