
#ifndef _ARDUINO_ZLIB_
#define _ARDUINO_ZLIB_
#include <Arduino.h>
#include "zlib.h"
#include "zconf.h"

class ArduinoZlib {

public:
    ArduinoZlib();
    static int32_t libmpq__decompress_zlib(uint8_t *in_buf, uint32_t in_size, uint8_t *out_buf, uint32_t out_size, uint32_t &outprintsize);
};

#endif