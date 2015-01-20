#include <iostream>

using namespace std;
#include "uavModule.h"

int main()
{

    UAVModule uav;
    uav.initialize();

    uav.update();

    uav.uninitialize();

    cout << "Hello World!" << endl;
    return 0;
}

