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
    uint8_t bufferR[250];

    if (xQueueReceive(*rxQueue, &bufferR, pdMS_TO_TICKS(0)) == pdTRUE)
    {
        // Check the first byte to determine the packet type
        char packetType = (char)bufferR[0];

        switch (packetType)
        {
        case 'T':
            // Send Telemetry trough Serial
            SerialCommWrite::write(bufferR, 250);
            break;
        case 'S':
            // Send Startup packet trough Serial
            SerialCommWrite::write(bufferR, 250);
            break;
        case 'C':
            // Send Acknowledgement packet trough Serial
            SerialCommWrite::write(bufferR, 250);
            break;

        default: // Unknown packet type
            break;
        }
    }
}
