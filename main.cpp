#include <iostream>

using namespace std;
#include "vehicleModule.h"

int main()
{

    vehicleModule vehicle;
    vehicle.initialize();

    vehicle.update();

    vehicle.uninitialize();

    cout << "Hello World!" << endl;
    return 0;
}

