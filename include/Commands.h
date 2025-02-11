#ifndef COMMANDS_H
#define COMMANDS_H

#include <Arduino.h>
#include "globals.h"
#include "SysData.h"
// #include "FsManager.h"

class FsManager;

namespace Commands
{
    class Commands
    {
    private:
        FsManager *fsManager;
        SysData::SysData *sysData;

        static int processInput(int raw_value, int min_value, int max_value, int center, int inverted);
        void readRawValues();
        void sanitizeValues();
        int static invertValueMap(int raw_value, int min_value, int max_value);

    public:
        // Constructor
        Commands(SysData::SysData &sysData, FsManager &fsManager);

        void readSticks();
        void finilizeCalibration();
        bool calibrateCenters();
        bool calibrateRanges();
    };
}

#endif // COMMANDS_H
