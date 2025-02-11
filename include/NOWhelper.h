#ifndef NOWHELPER_H
#define NOWHELPER_H

#include <esp_now.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include "globals.h"

namespace Tasks
{
    class NOWhelper
    {
    public:
        static void printMacAdress();
        static bool initESPNOW();

    private:
    };
}
#endif
