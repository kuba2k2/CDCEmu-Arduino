#pragma once

extern "C" {
    #include <i2cmaster.h>
}

uint8_t pcf_read(uint8_t pin);
void pcf_write(uint8_t pin, uint8_t value);
void pcf_toggle(uint8_t pin);