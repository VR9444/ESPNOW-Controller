#ifndef SERIALCOMMANDPROCESSOR_H
#define SERIALCOMMANDPROCESSOR_H

#include <Arduino.h>
#include "sysdata.h"
#include "Commands.h"
#include "FsManager.h"

class SerialCommandProcessor
{
public:
    SerialCommandProcessor(Commands::Commands &commands, FsManager &FsManager, SysData::SysData &sysData) : commands(&commands), fsManager(&FsManager), sysData(&sysData) {};
    void processCommands();

private:
    Commands::Commands *commands;
    FsManager *fsManager;
    SysData::SysData *sysData;

    void handleCommand(char command);
    void actionA();
    void actionB();
    void actionC();
};

#endif // SERIALCOMMANDPROCESSOR_H
