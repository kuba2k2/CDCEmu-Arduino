#ifndef RADIO_H
#define RADIO_H

#include <stdint.h>

void radio_enabled(bool radio_enabled);
void radio_playing(bool radio_playing);
void radio_tick();
void radio_next(uint8_t num = 0);
void radio_previous(uint8_t num = 0);
void radio_to_start();
void radio_disk(uint8_t num);
void radio_track(uint8_t num);

#endif
