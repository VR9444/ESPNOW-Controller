#ifndef SYSDATA_H
#define SYSDATA_H

#include <Arduino.h>

namespace SysData
{

#pragma pack(push, 4)

    struct s_Commands
    {
        int roll_RAW{0};
        int pitch_RAW{0};
        int yaw_RAW{0};
        int throttle_RAW{0};

        int roll_sanitized{0};
        int pitch_sanitized{0};
        int yaw_sanitized{0};
        int throttle_sanitized{0};
    };

    struct s_CommandsCalibration
    {
        int calibrationDone{0};

        int roll_center{0};
        int pitch_center{0};
        int yaw_center{0};
        int throttle_center{0};

        int roll_min{0};
        int pitch_min{0};
        int yaw_min{0};
        int throttle_min{0};

        int roll_max{0};
        int pitch_max{0};
        int yaw_max{0};
        int throttle_max{0};
    };

    struct SysData
    {
        s_Commands Commands;
        s_CommandsCalibration CommandsCalibration;
    };

#pragma pack(pop)

}

#endif