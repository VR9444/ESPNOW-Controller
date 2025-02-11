#include "NOWisrHandlers.h"

void Tasks::NOWisrHandlers::staticOnSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
    if (status != ESP_NOW_SEND_SUCCESS)
    {
        // Serial.println("Message send failed.");
    }
}
