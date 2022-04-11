#include "main.h"
#include <avr/io.h>
#include <util/delay.h>

#include <mcp2515.h>
#include <pcf8574.h>
#include <uart.h>

#include "can.h"
#include "data.h"
#include "gpio.h"
#include "radio.h"
#include "timers.h"

uint8_t uart_rx_count = 0;

#define IO_SPI 1
#define IO_I2C 2

uint8_t io_mode = 0;

void ensure_spi() {
	if (io_mode != IO_SPI) {
		mcp_init();
		spi_begin();
		io_mode = IO_SPI;
	}
}

void ensure_i2c() {
	if (io_mode != IO_I2C) {
		spi_end();
		i2c_init();
		io_mode = IO_I2C;
	}
}

void enter_sleep() {
	led_update_all(true);

	// ensure_spi();
	// mcp_sleep_wait();
	while (!data[DATA_IGNITION]) {
		can_receive_all();
		_delay_ms(100);
	}

	led_update_all(true);
}

int main() {
	uart_enable();
	uart_puts_P("CDCEmu v" VERSION_STR "\n");
	timer_start();
	can_init();

	while (1) {
		can_receive_all();
		can_send_all();

		radio_tick();

		led_update_all();

		uint8_t readable = uart_readable();

		if (readable >= 2) {
			char command[3];
			uart_gets(command, 2);
			command[2] = 0;
			if (!strcmp_P(command, PSTR("MA"))) {
				uart_puts_P("bt paused");
			} else if (!strcmp_P(command, PSTR("MB"))) {
				uart_puts_P("bt playing");
			}
		}

		// discard any newline characters
		if (uart_peek() == '\r' || uart_peek() == '\n')
			uart_getc();

		// flush any leftover bytes
		if (timer_check(TIMER_BUFFER_FLUSH, T_MS(1000))) {
			if (readable && uart_rx_count) {
				uart_rx_flush();
				readable = 0;
			}
			uart_rx_count = readable;
		}

		_delay_ms(1);
	}
	return 0;
}
