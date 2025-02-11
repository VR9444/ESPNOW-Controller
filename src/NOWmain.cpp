#include "NOWmain.h"
#include "sendlist.h"

using namespace Tasks;

QueueHandle_t rxQueue;

void onReceive(const uint8_t *mac_addr, const uint8_t *data, int len)
{
    uint8_t buffer[256];
    memcpy(buffer, data, len);

    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xQueueSendFromISR(rxQueue, &buffer, &xHigherPriorityTaskWoken);
}

Tasks::NOWMain::NOWMain(SysData::SysData &Data) : nowSend(Data), nowRecv(&rxQueue, Data)
{
    NOWMain::init();
}

void NOWMain::init()
{
    rxQueue = xQueueCreate(10, sizeof(uint8_t[256]));

    NOWhelper::printMacAdress();

    if (NOWhelper::initESPNOW() != true)
    {
        NOWhelper::initESPNOW();
    }
    esp_now_register_recv_cb(onReceive);
    esp_now_register_send_cb(NOWisrHandlers::staticOnSent);
}

void NOWMain::run()
{
    nowSend.sendDroneData();
    nowRecv.processReceivedData();
}
