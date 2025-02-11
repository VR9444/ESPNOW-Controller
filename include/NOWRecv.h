#ifndef NOWRECV_H
#define NOWRECV_H

#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <Arduino.h>
#include "NOWSend.h"
#include "sendlist.h"

namespace Tasks
{
    class NOWRecv
    {
    private:
        SysData::SysData &sysData;
        QueueHandle_t *rxQueue;
        void *memoryLocations[100];

        // void handleRecvConfig(const uint8_t *buffer);
        // void handleRecvStartup(const uint8_t *buffer);
        // void handleRecvEEPROM(const uint8_t *buffer);

    public:
        explicit NOWRecv(QueueHandle_t *queue, SysData::SysData &Data);
        void processReceivedData();
    };
}

#endif // NOWRECV_H
