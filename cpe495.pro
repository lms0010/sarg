TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    uavModule.cpp \
    simulatedRadar.cpp \
    realRadar.cpp \
    simulatedGPS.cpp \
    realGPS.cpp \
    simulatedDrive.cpp \
    realDrive.cpp \
    simulatedADSB.cpp \
    realADSB.cpp \
    simulatedWaypoints.cpp \
    realWaypoints.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    module.h \
    types.h \
    uavModule.h \
    radarModule.h \
    gpsModule.h \
    driveModule.h \
    adsbModule.h \
    waypointModule.h \
    simulatedRadar.h \
    realRadar.h \
    simulatedGPS.h \
    realGPS.h \
    simulatedDrive.h \
    realDrive.h \
    simulatedADSB.h \
    realADSB.h \
    simulatedWaypoints.h \
    realWaypoints.h

