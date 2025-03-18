#ifndef SERIALCOMMWRITE_H
#define SERIALCOMMWRITE_H

#include <Arduino.h>
#include "globals.h"

class SerialCommWrite
{
public:
    static bool write(const uint8_t *data, size_t length);

    static uint8_t calculate_checksum(const uint8_t *data, size_t len);
};

#endif
