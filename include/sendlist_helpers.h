#ifndef ESP_NOW_SENDLIST_HELPERS_H
#define ESP_NOW_SENDLIST_HELPERS_H

#include <Arduino.h>

namespace ESPNOWSendList
{
    static void saveValueToMemory(void *memoryLocation, int value)
    {
        *(int *)memoryLocation = value;
    }

    static void saveValueToMemory(void *memoryLocation, unsigned int value)
    {
        *(unsigned int *)memoryLocation = value;
    }

    static void saveValueToMemory(void *memoryLocation, float value)
    {
        *(float *)memoryLocation = value;
    }

    // Conversion to bytes

    static inline void floatToBytes(const float value, uint8_t *byteArray, int &index)
    {

        uint8_t *valuePtr = (uint8_t *)&value;

        for (int i = 0; i < 4; i++)
        {
            byteArray[index++] = valuePtr[i];
        }
    }

    static inline void intToBytes(const int value, uint8_t *byteArray, int &index)
    {

        uint8_t *valuePtr = (uint8_t *)&value;

        for (int i = 0; i < 4; i++)
        {
            byteArray[index++] = valuePtr[i];
        }
    }

    static inline void uintToBytes(const unsigned int value, uint8_t *byteArray, int &index)
    {

        uint8_t *valuePtr = (uint8_t *)&value;

        for (int i = 0; i < 4; i++)
        {
            byteArray[index++] = valuePtr[i];
        }
    }

    // Conversion from bytes

    static inline const float bytesToFloat(const uint8_t *byteArray)
    {
        float value;
        uint8_t *valuePtr = (uint8_t *)&value;

        for (int i = 0; i < 4; i++)
        {
            valuePtr[i] = byteArray[i];
        }

        return value;
    }

    static inline const int bytesToInt(const uint8_t *byteArray)
    {
        int value;
        uint8_t *valuePtr = (uint8_t *)&value;

        for (int i = 0; i < 4; i++)
        {
            valuePtr[i] = byteArray[i];
        }

        return value;
    }

    static inline const unsigned int bytesToUInt(const uint8_t *byteArray)
    {
        unsigned int value;
        uint8_t *valuePtr = (uint8_t *)&value;

        for (int i = 0; i < 4; i++)
        {
            valuePtr[i] = byteArray[i];
        }

        return value;
    }

}

#endif