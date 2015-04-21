TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

DEFINES += SOFTWARE_MODULES #simulated, delete to enable real

SOURCES += main.cpp \
    simulatedRadar.cpp \
    realRadar.cpp \
    simulatedADSB.cpp \
    realADSB.cpp \
    vehicleModule.cpp \
    realAutopilot.cpp \
    simulatedAutopilot.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    module.h \
    vehicleModule.h \
    radarModule.h \
    adsbModule.h \
    simulatedRadar.h \
    realRadar.h \
    simulatedADSB.h \
    realADSB.h \
    vehicleModule.h \
    autopilotModule.h \
    realAutopilot.h \
    simulatedAutopilot.h

