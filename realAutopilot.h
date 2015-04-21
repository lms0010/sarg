#ifndef REALAUTOPILOT_H
#define REALAUTOPILOT_H

#include "autopilotModule.h"

class RealAutopilot: public AutopilotModule {
 public:
    virtual         ~RealAutopilot();
    virtual bool    update();
    virtual char*   getLastError();
    virtual bool    initialize();
    virtual bool    uninitialize();
    virtual bool getDriveCommand(char** driveCommand);
    virtual bool getWaypoints(char** waypointsCommand);
    virtual bool getVehicleLatitude(float& vehicleLat);
    virtual bool getVehicleLongitude(float& vehicleLon);
    virtual bool getVehicleAltitude(float& vehicleAltitude);
    virtual bool getVehicleTrack(float& vehicleTrack);
    virtual bool getSimulatedWaypoints(std::vector<std::vector<SimulatedWaypoints> >*& paths);



private:
    bool            errorFlag;
    pthread_t       thread;
    static void*    ADSBClientThread(void* threadid);

    };

#endif // REALAUTOPILOT_H
