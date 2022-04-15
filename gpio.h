#pragma once

#include <stdint.h>

#define LED_NORMAL		0
#define LED_INVERTED	1
#define LED_NO_DEFAULT	0
#define LED_DEFAULT_OFF 1
#define LED_DEFAULT_ON	2

#define LED_DEF(pin, inverted, t_on, t_off, flag, flag_inverted, led_default)                                          \
	T_MS(t_on), (pin << 5) | (T_MS(t_off) * 20 / T_MS(t_on)),                                                          \
		(flag << 4) | (flag_inverted << 3) | (inverted << 2) | (led_default)

#define PIN_ANALOG_PWR 0
#define PIN_AUDIO_DET  1
#define PIN_BTN1	   3
#define PIN_LED_MIN	   4
#define PIN_LED_RED	   4
#define PIN_LED_GREEN  5
#define PIN_LED_YELLOW 6
#define PIN_BTN2	   7

void led_update_all(bool force = false);
void analog_enable(bool enable);
