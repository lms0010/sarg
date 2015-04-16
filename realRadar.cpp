#include "realRadar.h"
#include <pthread.h>

#include <iostream>
using namespace std;
#include <stdlib.h>
//#include <fftw3.h>********************************include file in the project
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


RealRadar::~RealRadar()
{  /* Last thing that main() should do */
    pthread_exit(NULL);
}

bool    RealRadar::update() { return true; }
char*   RealRadar::getLastError() { return 0; }
bool    RealRadar::uninitialize() { return true; }
bool    RealRadar::getNext(std::vector<double>*& vector) { vector = &obstacleDistances;
                                                 return true;}
int RS232_OpenComport(int, int, const char *);
int RS232_PollComport(int, unsigned char *, int);
int RS232_SendByte(int, unsigned char);
int RS232_SendBuf(int, unsigned char *, int);
void RS232_CloseComport(int);
void RS232_cputs(int, const char *);
int RS232_IsDCDEnabled(int);
int RS232_IsCTSEnabled(int);
int RS232_IsDSREnabled(int);
void RS232_enableDTR(int);
void RS232_disableDTR(int);
void RS232_enableRTS(int);
void RS232_disableRTS(int);

void *RealRadar::RadarClientThread(void *object)
{
    RealRadar* radar = (RealRadar*)object;

//    long c = 299999999;
//         long long kf = 20000000000;

//         int N = 1501;
//         double fs = 1501/0.075;

//         double fnyquist = fs/2.0;
//         double fax_hz[1501];
//         for (int l = 0; l < 1501; l++)
//            fax_hz[l] = l * (fs/N);
//         double fax_m[751];
//         for (int l = 0; l < 751; l++)
//            fax_m[l] = l/10.0;
//         double d[750];
//         for (int l = 1; l <= 751; l++)
//            d[l-1] = 75.0*exp((-1.0*l)/64.0) + 0.8;

//         //for (int l = 0; l < 1501; l++)
//        //	if (out[l][0] >= d[l])
//        //		cout << fax_m[l];


//        int comport = 0;
//        int charcount = 0;
//        int dataset[1501];
//        unsigned char buf[50];
//        unsigned char buf2[50];
//        unsigned char intbuf[6];
//        unsigned char msg1[5] = {'I', 'N', 'I', 'T', 13};
//        unsigned char msg2[17] = {'S', 'W', 'E', 'E', 'P', ':', 'M', 'E', 'A', 'S', 'U', 'R', 'E', ' ', 'O', 'N', 13};
//        unsigned char msg3[16] = {'S', 'W', 'E', 'E', 'P', ':', 'N', 'U', 'M', 'B', 'E', 'R', 'S', ' ', '1', 13};
//        unsigned char msg4[9] = {'T', 'R', 'I', 'G', ':', 'A', 'R', 'M', 13};
//        unsigned char msg5[13] = {'T', 'R', 'A', 'C', 'E', ':', 'D', 'A', 'T', 'A', ' ', '?', 13};

//         fftw_complex *in;
//         in = (fftw_complex*)fftw_malloc ( sizeof ( fftw_complex ) * 1501);

//         fftw_complex *out;
//         out = (fftw_complex*)fftw_malloc ( sizeof ( fftw_complex ) * 1501);

//         fftw_plan p;

//         if (RS232_OpenComport(comport, 115200, "8N1") == 1)
//        {
//            cout << "Can not open comport\n";
//          return(0);
//        }

//         int j;

//         cout << "opened port" << endl;
//         sleep(2);
//         do
//         {
//            j = RS232_PollComport(comport, buf, 50);
//         } while (j > 0);

//         int i;
//        i = RS232_SendBuf(comport, msg1, 5);
//        sleep(1);
//         j = RS232_PollComport(comport, buf, 50);
//        cout << "init " << j << " " << buf << endl;

//        i = RS232_SendBuf(comport, msg2, 17);
//        sleep(1);
//        j = RS232_PollComport(comport, buf, 50);
//        cout << "sweep measure " << j << " " << buf << endl;

//        i = RS232_SendBuf(comport, msg3, 16);
//        sleep(1);
//        j = RS232_PollComport(comport, buf, 50);
//        cout << "sweep num " << j << " " << buf << endl;

//        i = RS232_SendBuf(comport, msg4, 9);
//        sleep(1);
//        j = RS232_PollComport(comport, buf, 50);
//        cout << "trace " << j << " " << buf << endl;

//        i = RS232_SendBuf(comport, msg5, 13);
//        sleep(1);
//         cout << "trigger" << endl;

//        int k = 0;
//        while (k<1501)
//        {
//            // read data from serial port
//           j = RS232_PollComport(comport, intbuf, 6);
//             usleep(100);
//           charcount += j;
//           dataset[k] = atoi( ( char * ) intbuf );
//           in[k][0] = dataset[k];
//           //cout << dataset[k] << endl;
//           k++;
//        }
//        cout << "total: " << charcount << endl;
//        p = fftw_plan_dft_1d(1501, in, out, FFTW_FORWARD, FFTW_MEASURE);
//       fftw_execute (p);

//        double finalout[751];
//        for (int l = 0; l < 751; l++)
//            finalout[l] = fabs(out[l][0]/1501.0);
//        //for (int l = 0; l < 100; l++)
//        //	cout << finalout[l] << endl;

//        for (int l = 10; l < 751; l++)
//            if (finalout[l] >= d[l])
//                cout << fax_m[l] << endl;
//    }


//    int Cport[38],
//        error;

//    struct termios new_port_settings,
//           old_port_settings[38];

//    char comports[38][22]={"/dev/ttyUSB0","/dev/ttyS1","/dev/ttyS2","/dev/ttyS3","/dev/ttyS4","/dev/ttyS5",
//                           "/dev/ttyS6","/dev/ttyS7","/dev/ttyS8","/dev/ttyS9","/dev/ttyS10","/dev/ttyS11",
//                           "/dev/ttyS12","/dev/ttyS13","/dev/ttyS14","/dev/ttyS15","/dev/ttyS0",
//                           "/dev/ttyUSB1","/dev/ttyUSB2","/dev/ttyUSB3","/dev/ttyUSB4","/dev/ttyUSB5",
//                           "/dev/ttyAMA0","/dev/ttyAMA1","/dev/ttyACM0","/dev/ttyACM1",
//                           "/dev/rfcomm0","/dev/rfcomm1","/dev/ircomm0","/dev/ircomm1",
//                           "/dev/cuau0","/dev/cuau1","/dev/cuau2","/dev/cuau3",
//                           "/dev/cuaU0","/dev/cuaU1","/dev/cuaU2","/dev/cuaU3"};

//    int RS232_OpenComport(int comport_number, int baudrate, const char *mode)
//    {
//      int baudr,
//          status;

//      if((comport_number>37)||(comport_number<0))
//      {
//        printf("illegal comport number\n");
//        return(1);
//      }

//      switch(baudrate)
//      {
//        case      50 : baudr = B50;
//                       break;
//        case      75 : baudr = B75;
//                       break;
//        case     110 : baudr = B110;
//                       break;
//        case     134 : baudr = B134;
//                       break;
//        case     150 : baudr = B150;
//                       break;
//        case     200 : baudr = B200;
//                       break;
//        case     300 : baudr = B300;
//                       break;
//        case     600 : baudr = B600;
//                       break;
//        case    1200 : baudr = B1200;
//                       break;
//        case    1800 : baudr = B1800;
//                       break;
//        case    2400 : baudr = B2400;
//                       break;
//        case    4800 : baudr = B4800;
//                       break;
//        case    9600 : baudr = B9600;
//                       break;
//        case   19200 : baudr = B19200;
//                       break;
//        case   38400 : baudr = B38400;
//                       break;
//        case   57600 : baudr = B57600;
//                       break;
//        case  115200 : baudr = B115200;
//                       break;
//        case  230400 : baudr = B230400;
//                       break;
//        case  460800 : baudr = B460800;
//                       break;
//        case  500000 : baudr = B500000;
//                       break;
//        case  576000 : baudr = B576000;
//                       break;
//        case  921600 : baudr = B921600;
//                       break;
//        case 1000000 : baudr = B1000000;
//                       break;
//        case 1152000 : baudr = B1152000;
//                       break;
//        case 1500000 : baudr = B1500000;
//                       break;
//        case 2000000 : baudr = B2000000;
//                       break;
//        case 2500000 : baudr = B2500000;
//                       break;
//        case 3000000 : baudr = B3000000;
//                       break;
//        case 3500000 : baudr = B3500000;
//                       break;
//        case 4000000 : baudr = B4000000;
//                       break;
//        default      : printf("invalid baudrate\n");
//                       return(1);
//                       break;
//      }

//      int cbits=CS8,
//          cpar=0,
//          ipar=IGNPAR,
//          bstop=0;

//      if(strlen(mode) != 3)
//      {
//        printf("invalid mode \"%s\"\n", mode);
//        return(1);
//      }

//      switch(mode[0])
//      {
//        case '8': cbits = CS8;
//                  break;
//        case '7': cbits = CS7;
//                  break;
//        case '6': cbits = CS6;
//                  break;
//        case '5': cbits = CS5;
//                  break;
//        default : printf("invalid number of data-bits '%c'\n", mode[0]);
//                  return(1);
//                  break;
//      }

//      switch(mode[1])
//      {
//        case 'N':
//        case 'n': cpar = 0;
//                  ipar = IGNPAR;
//                  break;
//        case 'E':
//        case 'e': cpar = PARENB;
//                  ipar = INPCK;
//                  break;
//        case 'O':
//        case 'o': cpar = (PARENB | PARODD);
//                  ipar = INPCK;
//                  break;
//        default : printf("invalid parity '%c'\n", mode[1]);
//                  return(1);
//                  break;
//      }

//      switch(mode[2])
//      {
//        case '1': bstop = 0;
//                  break;
//        case '2': bstop = CSTOPB;
//                  break;
//        default : printf("invalid number of stop bits '%c'\n", mode[2]);
//                  return(1);
//                  break;
//      }

//    /*
//    http://pubs.opengroup.org/onlinepubs/7908799/xsh/termios.h.html

//    http://man7.org/linux/man-pages/man3/termios.3.html
//    */

//      Cport[comport_number] = open(comports[comport_number], O_RDWR | O_NOCTTY | O_NDELAY);
//      if(Cport[comport_number]==-1)
//      {
//        perror("unable to open comport ");
//        return(1);
//      }

//      error = tcgetattr(Cport[comport_number], old_port_settings + comport_number);
//      if(error==-1)
//      {
//        close(Cport[comport_number]);
//        perror("unable to read portsettings ");
//        return(1);
//      }
//      memset(&new_port_settings, 0, sizeof(new_port_settings));  /* clear the new struct */

//      new_port_settings.c_cflag = cbits | cpar | bstop | CLOCAL | CREAD;
//      new_port_settings.c_iflag = ipar;
//      new_port_settings.c_oflag = 0;
//      new_port_settings.c_lflag = 0;
//      new_port_settings.c_cc[VMIN] = 0;      /* block untill n bytes are received */
//      new_port_settings.c_cc[VTIME] = 0;     /* block untill a timer expires (n * 100 mSec.) */

//      cfsetispeed(&new_port_settings, baudr);
//      cfsetospeed(&new_port_settings, baudr);

//      error = tcsetattr(Cport[comport_number], TCSANOW, &new_port_settings);
//      if(error==-1)
//      {
//        close(Cport[comport_number]);
//        perror("unable to adjust portsettings ");
//        return(1);
//      }

//      if(ioctl(Cport[comport_number], TIOCMGET, &status) == -1)
//      {
//        perror("unable to get portstatus");
//        return(1);
//      }

//      status |= TIOCM_DTR;    /* turn on DTR */
//      status |= TIOCM_RTS;    /* turn on RTS */

//      if(ioctl(Cport[comport_number], TIOCMSET, &status) == -1)
//      {
//        perror("unable to set portstatus");
//        return(1);
//      }

//      return(0);
//    }


//    int RS232_PollComport(int comport_number, unsigned char *buf, int size)
//    {
//      int n;

//      n = read(Cport[comport_number], buf, size);

//      return(n);
//    }


//    int RS232_SendByte(int comport_number, unsigned char byte)
//    {
//      int n;

//      n = write(Cport[comport_number], &byte, 1);
//      if(n<0)  return(1);

//      return(0);
//    }


//    int RS232_SendBuf(int comport_number, unsigned char *buf, int size)
//    {
//      return(write(Cport[comport_number], buf, size));
//    }


//    void RS232_CloseComport(int comport_number)
//    {
//      int status;

//      if(ioctl(Cport[comport_number], TIOCMGET, &status) == -1)
//      {
//        perror("unable to get portstatus");
//      }

//      status &= ~TIOCM_DTR;    /* turn off DTR */
//      status &= ~TIOCM_RTS;    /* turn off RTS */

//      if(ioctl(Cport[comport_number], TIOCMSET, &status) == -1)
//      {
//        perror("unable to set portstatus");
//      }

//      tcsetattr(Cport[comport_number], TCSANOW, old_port_settings + comport_number);
//      close(Cport[comport_number]);
//    }

//    /*
//    Constant  Description
//    TIOCM_LE        DSR (data set ready/line enable)
//    TIOCM_DTR       DTR (data terminal ready)
//    TIOCM_RTS       RTS (request to send)
//    TIOCM_ST        Secondary TXD (transmit)
//    TIOCM_SR        Secondary RXD (receive)
//    TIOCM_CTS       CTS (clear to send)
//    TIOCM_CAR       DCD (data carrier detect)
//    TIOCM_CD        see TIOCM_CAR
//    TIOCM_RNG       RNG (ring)
//    TIOCM_RI        see TIOCM_RNG
//    TIOCM_DSR       DSR (data set ready)

//    http://man7.org/linux/man-pages/man4/tty_ioctl.4.html
//    */

//    int RS232_IsDCDEnabled(int comport_number)
//    {
//      int status;

//      ioctl(Cport[comport_number], TIOCMGET, &status);

//      if(status&TIOCM_CAR) return(1);
//      else return(0);
//    }

//    int RS232_IsCTSEnabled(int comport_number)
//    {
//      int status;

//      ioctl(Cport[comport_number], TIOCMGET, &status);

//      if(status&TIOCM_CTS) return(1);
//      else return(0);
//    }

//    int RS232_IsDSREnabled(int comport_number)
//    {
//      int status;

//      ioctl(Cport[comport_number], TIOCMGET, &status);

//      if(status&TIOCM_DSR) return(1);
//      else return(0);
//    }

//    void RS232_enableDTR(int comport_number)
//    {
//      int status;

//      if(ioctl(Cport[comport_number], TIOCMGET, &status) == -1)
//      {
//        perror("unable to get portstatus");
//      }

//      status |= TIOCM_DTR;    /* turn on DTR */

//      if(ioctl(Cport[comport_number], TIOCMSET, &status) == -1)
//      {
//        perror("unable to set portstatus");
//      }
//    }

//    void RS232_disableDTR(int comport_number)
//    {
//      int status;

//      if(ioctl(Cport[comport_number], TIOCMGET, &status) == -1)
//      {
//        perror("unable to get portstatus");
//      }

//      status &= ~TIOCM_DTR;    /* turn off DTR */

//      if(ioctl(Cport[comport_number], TIOCMSET, &status) == -1)
//      {
//        perror("unable to set portstatus");
//      }
//    }

//    void RS232_enableRTS(int comport_number)
//    {
//      int status;

//      if(ioctl(Cport[comport_number], TIOCMGET, &status) == -1)
//      {
//        perror("unable to get portstatus");
//      }

//      status |= TIOCM_RTS;    /* turn on RTS */

//      if(ioctl(Cport[comport_number], TIOCMSET, &status) == -1)
//      {
//        perror("unable to set portstatus");
//      }
//    }

//    void RS232_disableRTS(int comport_number)
//    {
//      int status;

//      if(ioctl(Cport[comport_number], TIOCMGET, &status) == -1)
//      {
//        perror("unable to get portstatus");
//      }

//      status &= ~TIOCM_RTS;    /* turn off RTS */

//      if(ioctl(Cport[comport_number], TIOCMSET, &status) == -1)
//      {
//        perror("unable to set portstatus");
//      }
//    }


    return 0;
}



bool RealRadar::initialize()
{
#if 0
    //return true if the thread was created successfully
    int rc;

       printf("In main: creating radar thread %ld\n");
       rc = pthread_create(&thread, NULL, &RadarClientThread, this);
       if (rc){
          printf("ERROR in radar thread; return code from pthread_create() is %d\n", rc);
          errorFlag=true;
         // exit(-1);
       }
   return rc;
#endif
}


