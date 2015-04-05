#include <iostream>

using namespace std;
#include "vehicleModule.h"

int main()
{

    vehicleModule vehicle;
    vehicle.initialize();

    vehicle.update();

    vehicle.uninitialize();

    cout << "Hello World! Main initialize test" << endl;
    return 0;
}

