#include "FsManager.h"

FsManager::FsManager(SysData::SysData &sysData) : sysData(&sysData)
{
}

void FsManager::begin(Commands::Commands &commands)
{
    Commands::Commands *commandsPtr = &commands;
    if (LittleFS.begin())
    {
        Serial.println("FsManager initialized successfully.");
        if (!loadCalibration())
        {
            Serial.println("Calibration is not Loaded!");
            Serial.println("Calibration is started!");
            commandsPtr->calibrateRanges();
            commandsPtr->calibrateCenters();
        }
        sysData->CommandsCalibration.calibrationDone = 1;
    }
    else
    {
        LittleFS.format();
        Serial.print("LittleFS is Formated!");
        if (LittleFS.begin())
        {
            Serial.println("FsManager initialized successfully.");
            if (!loadCalibration())
            {
                Serial.println("Calibration is not Loaded!");
                Serial.println("Calibration is started!");
                commandsPtr->calibrateRanges();
                commandsPtr->calibrateCenters();
            }
        }
        else
        {
            Serial.println("LittleFS failed!");
            Serial.println("Calibration is started!");
            commandsPtr->calibrateRanges();
            commandsPtr->calibrateCenters();
        }
    }
    sysData->CommandsCalibration.calibrationDone = 1;
}

bool FsManager::saveCalibration()
{
    if (!sysData)
    {
        Serial.println("SysData not initialized");
        return false;
    }

    File file = LittleFS.open(CALIBRATION_FILE, "w");
    if (!file)
    {
        Serial.println("Failed to open file for writing");
        return false;
    }
    file.write((uint8_t *)&sysData->CommandsCalibration, sizeof(SysData::s_CommandsCalibration));
    file.close();
    return true;
}

bool FsManager::loadCalibration()
{
    if (!sysData)
    {
        Serial.println("SysData not initialized");
        return false;
    }

    // Try opening the file in read mode
    File file = LittleFS.open(CALIBRATION_FILE, "r");

    if (!file)
    {
        Serial.println("Calibration file not found, creating a new one...");

        // Create and initialize the file if it doesn't exist
        file = LittleFS.open(CALIBRATION_FILE, "w"); // Open in write mode
        if (!file)
        {
            Serial.println("Failed to create calibration file");
            return false;
        }

        // Initialize with default values
        memset(&sysData->CommandsCalibration, 0, sizeof(SysData::s_CommandsCalibration));
        file.write((uint8_t *)&sysData->CommandsCalibration, sizeof(SysData::s_CommandsCalibration));
        file.close();

        Serial.println("New calibration file created successfully.");
        return false;
    }

    // If the file exists, read the data
    if (file.read((uint8_t *)&sysData->CommandsCalibration, sizeof(SysData::s_CommandsCalibration)) != sizeof(SysData::s_CommandsCalibration))
    {
        Serial.println("Failed to read calibration data");
        file.close();
        return false;
    }

    file.close();
    return true;
}
