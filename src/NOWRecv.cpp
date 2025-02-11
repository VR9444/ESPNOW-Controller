#include "NOWRecv.h"
#include "EEPROM.h"

using namespace Tasks;

// Constructor: initialize with a queue
NOWRecv::NOWRecv(QueueHandle_t *queue, SysData::SysData &Data) : rxQueue(queue), sysData(Data)
{
    ESPNOWSendList::populateMemoryLocations(sysData, memoryLocations);
}

// Process received data
void NOWRecv::processReceivedData()
{
    uint8_t bufferR[256];

    if (xQueueReceive(*rxQueue, &bufferR, pdMS_TO_TICKS(0)) == pdTRUE)
    {
        // // Check the first byte to determine the packet type
        // char packetType = (char)bufferR[0];

        // switch (packetType)
        // {
        // case 'S':                       // Send configuration variables
        //     handleRecvStartup(bufferR); // No need to pass buffer for this
        //     break;

        // case 'E':                      // Save data to EEPROM
        //     handleRecvEEPROM(bufferR); // Pass pointer to payload
        //     break;

        // case 'C':                      // Change configuration
        //     handleRecvConfig(bufferR); // Pass pointer to payload
        //     break;

        // default: // Unknown packet type
        //     break;
        // }
    }
}

// void Tasks::NOWRecv::handleRecvStartup(const uint8_t *buffer)
// {
//     if (buffer[1] == '\n') // Check if the second byte is '\n'
//     {
//         Tasks::NOWSend::sendStartupConfig(sysData);
//     }
// }

// void Tasks::NOWRecv::handleRecvEEPROM(const uint8_t *buffer)
// {
// }

// void Tasks::NOWRecv::handleRecvConfig(const uint8_t *buffer)
// {
//     // Extract packet type
//     char packetType = (char)buffer[0]; // 1 byte

//     // Extract ID (2 bytes)
//     uint16_t id = (buffer[1] << 8) | buffer[2]; // 2 bytes, combining high and low byte
//     int iid = (int)id;
//     void *memoryLocation = memoryLocations[iid - 100];

//     // Extract Type (1 byte)
//     char type = buffer[3]; // 1 byte

//     if ((char)buffer[8] == '\n')
//     {
//         switch (type)
//         {
//         case 'i': // Integer
//         {
//             int value = ESPNOWSendList::bytesToInt(&buffer[4]);
//             ESPNOWSendList::saveValueToMemory(memoryLocation, value);
//             break;
//         }
//         case 'u': // Unsigned Integer
//         {
//             unsigned int value = ESPNOWSendList::bytesToUInt(&buffer[4]);
//             ESPNOWSendList::saveValueToMemory(memoryLocation, value);
//             break;
//         }
//         case 'f': // Float
//         {
//             float value = ESPNOWSendList::bytesToFloat(&buffer[4]);
//             ESPNOWSendList::saveValueToMemory(memoryLocation, value);
//             break;
//         }
//         default:
//             break;
//         }

//         NOWSend::sendAcknowledgement(buffer);
//     }
// }
