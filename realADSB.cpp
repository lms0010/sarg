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

void error(const char *msg)
{
    perror(msg);
    exit(0);
}


RealADSB::~RealADSB()
{/* Last thing that main() should do */
    pthread_exit(NULL);
}

bool    RealADSB::update() { return true; }
char*   RealADSB::getLastError() { return 0; }
bool    RealADSB::uninitialize() { return true; }


bool    RealADSB::getHexIdent(char** hexIdent) { return true; }
bool    RealADSB::getFlightID(int& flightID) { return true; }
bool    RealADSB::getAltitude(float& altitude) { return true; }
bool    RealADSB::getGroundSpeed(int& groundSpeed) { return true; }
bool    RealADSB::getLatitude(float& lat) { return true; }
bool    RealADSB::getLongitude(float& lon) { return true; }
bool    RealADSB::getTrack(int& track) { return true; }
bool    RealADSB::getDeltaTime(int& deltaTime) { return true; }

void *ADSBClientThread(void *threadid)
{
   long tid;
   tid = (long)threadid;
   printf("ADS-B thread #%ld!\n", tid);
   pthread_exit(NULL);



   int sockfd, portno, n;
   struct sockaddr_in serv_addr;
   struct hostent *server;

   char buffer[256];
   if (argc < 3) {
      fprintf(stderr,"usage %s hostname port\n", argv[0]);
      exit(0);
   }
   portno = atoi(argv[2]);
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if (sockfd < 0)
       error("ERROR opening socket");
   server = gethostbyname(argv[1]);
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
       error("ERROR connecting");
   printf("Please enter the message: ");
   bzero(buffer,256);
   fgets(buffer,255,stdin);
   n = write(sockfd,buffer,strlen(buffer));
   if (n < 0)
        error("ERROR writing to socket");
   bzero(buffer,256);
   n = read(sockfd,buffer,255);
   if (n < 0)
        error("ERROR reading from socket");
   printf("%s\n",buffer);


   char * token;
   token = strtok (str, ",");
   int count = 0;
   bool flag = false;
   int currentIndex = -1;





   while(token !=NULL)
   {

       switch(count){

       case MSG_TYPE:
           if(strcmp(token, "MSG")!= 0)
               flag = true;
            break;
       case TRANSMISSION_TYPE:
              if(strcmp(token, "3")!= 0)
                  flag = true;
            break;
       case SESSION_ID:
            break;
       case AIRCRAFT_ID:
           break;
       case HEX_IDENT:
           int emptyIndex = -1;
           for (int i; i<500; i++)
           {
               if(strcmp(token, positionArray[i].hex_ident)==0)
               {
                   currentIndex = i; //found in array
               }
               if(!positionArray[i].inUse) emptyIndex = i;
           }
           if(currentIndex == -1) { //wasn't found in the array
               if(empty != -1) {
                   inUse=true;
                   currentIndex = emptyIndex;
                   strcpy(positionArray[currentIndex], token); //insert new identifier
               } else {
                   printf("ERROR, OUT OF EMPTY OBJECTS!!!!");
               }
           }
           break;
       case FLIGHT_ID:
           break;
       case DATE_GEN:
           break;
       case TIME_GEN:
           break;
       case DATE_LOG:
           break;
       case TIME_LOG:
           break;
       case CALLSIGN:
           break;
       case ALTITUDE:
          positionArray[currentIndex].altitude = atoi(token);
           break;
       case GROUND_SPEED:
           break;
       case TRACK:
           break;
       case LATITUDE:
             positionArray[currentIndex].latitude = atoi(token);
           break;
       case LONGITUDE:
             positionArray[currentIndex].longitude = atoi(token);
           break;
       case VERTICAL_RATE:
           break;
       case SQUAWK:
           break;
       case ALERT:
           break;
       case EMERGENCY:
           break;
       case SPI:
           break;
       case IS_ON_GROUND:
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
       rc = pthread_create(&thread, NULL, PrintHello, NULL);
       if (rc){
          printf("ERROR; return code from pthread_create() is %d\n", rc);
          exit(-1);
       }


   return rc;
}
