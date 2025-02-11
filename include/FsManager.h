#ifndef FSMANAGER_H
#define FSMANAGER_H

#include <Arduino.h>
#include <LittleFS.h>
#include "SysData.h"
#include "Commands.h"

#define CALIBRATION_FILE "/ControlsCalibration"
#define NUM_VARIABLES 12

class FsManager
{

private:
    SysData::SysData *sysData;

public:
    FsManager(SysData::SysData &sysData);
    void begin(Commands::Commands &commands);
    bool saveCalibration();
    bool loadCalibration();
};

#endif // FSMANAGER_H