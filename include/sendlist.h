#ifndef ESP_NOW_SENDLIST_H
#define ESP_NOW_SENDLIST_H

#include <sysdata.h>
#include <sendlist_helpers.h>

namespace ESPNOWSendList
{

    static inline const int packDroneSender(uint8_t *buffer, const SysData::SysData &Data)
    {
        int index = 1;
        intToBytes(Data.Commands.throttle_sanitized, buffer, index);
        intToBytes(Data.Commands.yaw_sanitized, buffer, index);
        intToBytes(Data.Commands.pitch_sanitized, buffer, index);
        intToBytes(Data.Commands.roll_sanitized, buffer, index);
        return index;
    }

    static void populateMemoryLocations(SysData::SysData &sysData, void **memoryLocations)
    {
        int idx = 0;

        memoryLocations[idx++] = &sysData.Commands.throttle_sanitized;
    }

}
#endif
