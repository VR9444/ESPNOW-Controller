#include "NOWSend.h"

void Tasks::NOWSend::sendDroneData()
{
    uint8_t bufferDroneSender[250];
    bufferDroneSender[0] = 'D';
    ESPNOWSendList::packDroneSender(bufferDroneSender, sysData);
    esp_now_send(RECEIVER_MAC, (uint8_t *)bufferDroneSender, sizeof(bufferDroneSender));
}

void Tasks::NOWSend::sendDroneDataFromSerial(uint8_t *buffer)
{
    esp_now_send(RECEIVER_MAC, (uint8_t *)buffer, sizeof(buffer));
}

Tasks::NOWSend::NOWSend(SysData::SysData &Data) : sysData(Data) {}
