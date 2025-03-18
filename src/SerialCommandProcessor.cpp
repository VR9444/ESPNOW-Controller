#include "SerialCommandProcessor.h"

void SerialCommandProcessor::processIncomingBytes(std::vector<uint8_t> &buffer)
{
    if (Serial.available())
    {
        while (Serial.available() > 0)
        {
            uint8_t receivedChar = Serial.read();
            buffer.push_back(receivedChar);
        }
    }
}

void SerialCommandProcessor::processBuffer(std::vector<uint8_t> &buffer)
{

    //
    //
    //
    // Experimental code for testing DRONE
    //
    //
    //
    //
    //  if (!buffer.empty() && buffer.size() >= 259)
    //  {

    //     while (buffer.size() >= 259)
    //     {
    //         if (std::equal(buffer.begin(), buffer.begin() + 4,
    //                        std::vector<uint8_t>{START_BYTE, START_BYTE, START_BYTE, START_BYTE}.begin()))
    //         {
    //             uint8_t data[250];
    //             std::copy(buffer.begin() + 4, buffer.begin() + 254, data);
    //             if (SerialCommWrite::calculate_checksum(data, 250) == buffer[254] &&
    //                 std::all_of(buffer.begin() + 255, buffer.begin() + 259, [](uint8_t byte)
    //                             { return byte == 0xFE; }))
    //             {
    //                 if (SerialCommandProcessor::handleCommand(data[0]))
    //                 {
    //                     nowSender.sendDroneDataFromSerial(data);
    //                 }
    //             }
    //             buffer.erase(buffer.begin(), buffer.begin() + 259);
    //             break;
    //         }
    //         else
    //         {
    //             buffer.erase(buffer.begin(), buffer.begin() + 1);
    //         }
    //     }
    // }

    while (!buffer.empty())
    {
        uint8_t command = buffer.front();
        handleCommand(command);
        buffer.erase(buffer.begin());
    }
}

bool SerialCommandProcessor::handleCommand(uint8_t command)
{
    char cmdChar = static_cast<char>(command);
    switch (cmdChar)
    {
    case 'K':
        actionK();
        return false;
    default:
        return true;
    }
}

void SerialCommandProcessor::actionK()
{
    sysData->CommandsCalibration.calibrationDone = 0;
    commands->calibrateRanges();
    commands->calibrateCenters();
    commands->finilizeCalibration();
    Serial.println("Calibration done!");
    sysData->CommandsCalibration.calibrationDone = 1;
}
