#include "SerialCommWrite.h"

bool SerialCommWrite::write(const uint8_t *data, size_t length)
{
    uint8_t packet[250 + 9];
    packet[0] = START_BYTE;
    packet[1] = START_BYTE;
    packet[2] = START_BYTE;
    packet[3] = START_BYTE;

    for (int i = 0; i < 250; i++)
    {
        packet[i + 4] = data[i];
    }

    uint8_t checksum = SerialCommWrite::calculate_checksum(data, 250);
    packet[254] = checksum;
    packet[255] = END_BYTE;
    packet[256] = END_BYTE;
    packet[257] = END_BYTE;
    packet[258] = END_BYTE;

    for (int i = 0; i < 259; i++)
    {
        Serial.write(packet[i]);
        Serial.flush();
    }
}

uint8_t SerialCommWrite::calculate_checksum(const uint8_t *data, size_t len)
{
    uint8_t checksum = 0;
    for (size_t i = 0; i < len; i++)
    {
        checksum ^= data[i];
    }
    return checksum;
}
