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
bool    RealADSB::getTimeStamp(int index, int& timeStamp)  { return true; }

void *RealADSB::ADSBClientThread(void *object)
{
 //  pthread_exit(NULL);
   RealADSB* adsb = (RealADSB*)object;



   int sockfd, portno, n;
   struct sockaddr_in serv_addr;
   struct hostent *server;

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
   printf("Please enter the message: ");
   bzero(buffer,256);
   fgets(buffer,255,stdin);
   n = write(sockfd,buffer,strlen(buffer));
   if (n < 0)
        fprintf(stderr,"ERROR writing to socket\n");
   bzero(buffer,256);
   n = read(sockfd,buffer,255);
   if (n < 0)
        fprintf(stderr,"ERROR reading from socket\n");
   printf("%s\n",buffer);


   char * token;
   token = strtok (buffer, ",");
   int count = 0;
   bool flag = false;
   int currentIndex = -1;
   int transmission_type;
   int emptyIndex = -1;





   while(token !=NULL)
   {
       switch(count){

       case ADSBModule::MSG_TYPE:
           if(strcmp(token, "MSG")!= 0)
               flag = true;
            break;
       case ADSBModule::TRANSMISSION_TYPE:
              if((strcmp(token, "3")!= 0)&&(strcmp(token, "4")!=0)){
                flag = true;
              }
              else if (strcmp(token, "3")==0){
                  transmission_type = 3;
              }
              else if (strcmp(token, "4")==0){
                  transmission_type = 4;
              }
            break;
       case ADSBModule::SESSION_ID:
            break;
       case ADSBModule::AIRCRAFT_ID:
           break;
       case ADSBModule::HEX_IDENT:
           for (int i=0; i<adsb->visibleAircraft.size(); i++){
               if(strcmp(token, adsb->visibleAircraft[i].hex_ident)==0){
                   currentIndex = i; //found in array
               }
               if(! adsb->visibleAircraft[i].inUse) emptyIndex = i;
           }
           if(currentIndex == -1) { //wasn't found in the array
               if(emptyIndex != -1) {
                   adsb->visibleAircraft[currentIndex].inUse=true;
                   currentIndex = emptyIndex;
                   strcpy( adsb->visibleAircraft[currentIndex].hex_ident, token); //insert new identifier
               } else {
                   printf("ERROR, OUT OF EMPTY OBJECTS!!!!");
               }
           }
           break;
       case ADSBModule::FLIGHT_ID:
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
           break;
       case ADSBModule::ALTITUDE:
           if(transmission_type==3)
                 adsb->visibleAircraft[currentIndex].altitude = atoi(token);
           break;
       case ADSBModule::GROUND_SPEED:
           if(transmission_type==4)
                 adsb->visibleAircraft[currentIndex].groundSpeed = atoi(token);
           break;
       case ADSBModule::TRACK:
            if(transmission_type==4)
                  adsb->visibleAircraft[currentIndex].track = atoi(token);
           break;
       case ADSBModule::LATITUDE:
           if(transmission_type==3)
              adsb->visibleAircraft[currentIndex].latitude = atoi(token);
           break;
       case ADSBModule::LONGITUDE:
           if(transmission_type==3)
              adsb->visibleAircraft[currentIndex].longitude = atoi(token);
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

       count++;
       printf("%s\n",token);
       token=strtok(NULL, ",");
        if(flag) break;
   }

  close(sockfd);
   return 0;
}

bool RealADSB::initialize()
{
    //return true if the thread was created successfully
    int rc;

       printf("In main: creating thread %ld\n");
       rc = pthread_create(&thread, NULL, &ADSBClientThread, this);
       if (rc){
          printf("ERROR; return code from pthread_create() is %d\n", rc);
          errorFlag=true;
         // exit(-1);
       }


   return rc;
}
