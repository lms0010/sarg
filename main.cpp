#include <iostream>

using namespace std;
#include "vehicleModule.h"

int main()
{

    vehicleModule vehicle;
    vehicle.initialize();

    while(1)
    vehicle.update();

    vehicle.uninitialize();

    cout << "Hello World! Main initialize test" << endl;
    return 0;
}

