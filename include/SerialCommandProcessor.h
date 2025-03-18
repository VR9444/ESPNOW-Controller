#ifndef SERIALCOMMANDPROCESSOR_H
#define SERIALCOMMANDPROCESSOR_H

#include <Arduino.h>
#include "sysdata.h"
#include "Commands.h"
#include "FsManager.h"
#include <vector>
#include "SerialCommWrite.h"
#include "NOWSend.h"

class SerialCommandProcessor
{
public:
    SerialCommandProcessor(Commands::Commands &commands, FsManager &FsManager, SysData::SysData &sysData) : commands(&commands), fsManager(&FsManager), sysData(&sysData), nowSender(sysData) {};
    void processIncomingBytes(std::vector<uint8_t> &buffer);
    void processBuffer(std::vector<uint8_t> &buffer);

private:
    Commands::Commands *commands;
    FsManager *fsManager;
    SysData::SysData *sysData;
    Tasks::NOWSend nowSender;

    bool handleCommand(uint8_t command);
    void actionK();
};

#endif // SERIALCOMMANDPROCESSOR_H
