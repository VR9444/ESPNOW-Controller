#ifndef NOWISRHANDLERS_H
#define NOWISRHANDLERS_H

#include <esp_now.h>
#include <WiFi.h>

namespace Tasks
{
    class NOWisrHandlers
    {
    public:
        static void staticOnSent(const uint8_t *mac_addr, esp_now_send_status_t status);

    private:
    };
}
#endif // NOWISRHANDLERS_H
