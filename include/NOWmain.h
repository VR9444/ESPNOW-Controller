#ifndef NOW_MAIN_H
#define NOW_MAIN_H

#include "NOWisrHandlers.h"
#include "NOWhelper.h"
#include "NOWSend.h"
#include "NOWRecv.h"

namespace Tasks
{
    class NOWMain
    {
    private:
        NOWisrHandlers handler;
        NOWSend nowSend;
        NOWRecv nowRecv;

    public:
        NOWMain(SysData::SysData &Data);
        void init();
        void run();
    };
}

#endif // NOW_MAIN_H
