#ifndef UART_DRIVER_H
#define UART_DRIVER_H

#include <stdint.h>

// ── Constants ─────────────────────────────────────────────────
#define UART_BUFFER_SIZE  (64U)
#define UART_BAUD_9600    (9600UL)
#define UART_BAUD_115200  (115200UL)

// ── Types ─────────────────────────────────────────────────────
typedef enum {
    UART_OK      = 0,
    UART_ERROR   = 1,
    UART_BUSY    = 2,
    UART_TIMEOUT = 3
} UartStatus_t;

typedef struct {
    uint32_t baud_rate;
    uint8_t  data_bits;    // 8
    uint8_t  stop_bits;    // 1
    uint8_t  parity;       // 0 = none
} UartConfig_t;

// ── Function Declarations ─────────────────────────────────────
UartStatus_t uart_init        (const UartConfig_t *config);
UartStatus_t uart_send_byte   (uint8_t data);
UartStatus_t uart_send_string (const char *str);
UartStatus_t uart_send_buffer (const uint8_t *buf, uint8_t len);
UartStatus_t uart_receive     (uint8_t *out_byte);
void         uart_print_config(void);

#endif // UART_DRIVER_H