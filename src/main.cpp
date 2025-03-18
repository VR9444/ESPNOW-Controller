#include <Arduino.h>
#include "Commands.h"
#include "SerialCommandProcessor.h"
#include "FsManager.h"
#include "globals.h"
#include "NOWmain.h"
#include "sysdata.h"

#include <vector>

std::vector<uint8_t> bufferIncomingBytesSerial;

// Create system data object
SysData::SysData sysData;

// Create FsManager instance
FsManager fsManager(sysData);

// Create CommandsCalibrate instance
Commands::Commands commands(sysData, fsManager);

SerialCommandProcessor serialComandProcessor(commands, fsManager, sysData);

void taskCore0(void *pvParameters);
void taskCore1(void *pvParameters);

void setup()
{
    Serial.begin(115200);

    // Create task on Core 0
    xTaskCreatePinnedToCore(
        taskCore0,
        "TaskCore0",
        4096,
        NULL,
        1,
        NULL,
        0);

    xTaskCreatePinnedToCore(
        taskCore1,
        "TaskCore1",
        4096,
        NULL,
        1,
        NULL,
        1);

    fsManager.begin(commands);
}

void loop()
{
}

void taskCore0(void *pvParameters)
{

    for (;;)
    {
        serialComandProcessor.processIncomingBytes(bufferIncomingBytesSerial);

        serialComandProcessor.processBuffer(bufferIncomingBytesSerial);

        if (sysData.CommandsCalibration.calibrationDone == 1)
        {
            commands.readSticks();
        }

        vTaskDelay(pdMS_TO_TICKS(20));
    }
}

void taskCore1(void *pvParameters)
{
    Tasks::NOWMain ESPnow(sysData);

    while (1)
    {
        if (sysData.CommandsCalibration.calibrationDone == 0)
        {
            vTaskDelay(pdMS_TO_TICKS(100));
        }
        else
        {
            ESPnow.run();
        }

        vTaskDelay(pdMS_TO_TICKS(20));
    }
}
