#include "SerialCommandProcessor.h"

void SerialCommandProcessor::processCommands()
{
    if (Serial.available())
    {
        char command = Serial.read();
        handleCommand(command);
    }
}

void SerialCommandProcessor::handleCommand(char command)
{
    switch (command)
    {
    case 'A':
        actionA();
        break;
    case 'B':
        actionB();
        break;
    case 'C':
        actionC();
        break;
    default:
        Serial.println("Unknown Command");
        break;
    }
}

void SerialCommandProcessor::actionA()
{
    Serial.println("Action A executed!");
}

void SerialCommandProcessor::actionB()
{
    Serial.println("Action B executed!");
}

void SerialCommandProcessor::actionC()
{
    sysData->CommandsCalibration.calibrationDone = 0;
    commands->calibrateRanges();
    commands->calibrateCenters();
    commands->finilizeCalibration();
    Serial.println("Calibration done!");
    sysData->CommandsCalibration.calibrationDone = 1;
}
