#ifndef CONFIG_H
#define CONFIG_H

#define DEBUG           0

#define MCP_CS_DDR      DDRB
#define MCP_CS_PORT     PORTB
#define MCP_CS_PIN      3
#define MCP_CLOCK       MCP_8MHZ
#define MCP_SPEED       MCP_125KBPS

#define SCL_PORT        PORTB
#define SCL_PIN         3
#define SDA_PORT        PORTB
#define SDA_PIN         1

#define PU_RX           B,4
#define PU_TX           B,4
#define PU_BAUD_RATE    115200L

#define PCF_ADDR        0x22

#endif