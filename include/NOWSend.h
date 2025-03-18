#ifndef NOWSend_H
#define NOWSend_H

#include <esp_now.h>
#include "sendlist.h"
#include "globals.h"
#include "sysdata.h"

namespace Tasks
{
    class NOWSend
    {
    public:
        void sendDroneData();
        void sendDroneDataFromSerial(uint8_t *buffer);
        NOWSend(SysData::SysData &Data);

    private:
        SysData::SysData &sysData;
    };
}
#endif // NOWSend_H
