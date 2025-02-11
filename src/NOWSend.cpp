#include "NOWSend.h"

void Tasks::NOWSend::sendDroneData()
{
    uint8_t bufferDroneSender[250];
    bufferDroneSender[0] = 'D';
    ESPNOWSendList::packDroneSender(bufferDroneSender, sysData);
    esp_now_send(RECEIVER_MAC, (uint8_t *)bufferDroneSender, sizeof(bufferDroneSender));
}
 
// void Tasks::NOWSend::sendStartupConfig(SysData::SysData &sysData)
// {
//     uint8_t bufferSetup[250];

//     bufferSetup[0] = 'S'; // First byte is packet type
//     bufferSetup[1] = 0;   // Second byte is packet number
//     ESPNOWSendList::packParameters(bufferSetup, sysData);
//     esp_now_send(RECEIVER_MAC, (uint8_t *)bufferSetup, sizeof(bufferSetup));
// }
// void Tasks::NOWSend::sendAcknowledgement(const uint8_t *buffer)
// {
//     esp_now_send(RECEIVER_MAC, (uint8_t *)buffer, sizeof(buffer));
// }

Tasks::NOWSend::NOWSend(SysData::SysData &Data) : sysData(Data) {}
