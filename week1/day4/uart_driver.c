#include "uart_driver.h"
#include <stdio.h>
#include <string.h>

// ── Private state ──────────────────────────────────────────────
static UartConfig_t s_config     = {0};
static uint8_t      s_initialized = 0U;

// Simulated RX buffer (in real STM32, hardware fills this via interrupt)
static uint8_t  s_rx_buffer[UART_BUFFER_SIZE] = "HELLO_FROM_SENSOR\0";
static uint8_t  s_rx_index = 0U;

// ── Public functions ───────────────────────────────────────────
UartStatus_t uart_init(const UartConfig_t *config) {
    if (config == NULL) return UART_ERROR;

    s_config      = *config;
    s_initialized = 1U;

    printf("[UART] Initialized — Baud: %lu | %u%s%u\n",
           (unsigned long)s_config.baud_rate,
           s_config.data_bits,
           s_config.parity == 0 ? "N" : "P",
           s_config.stop_bits);
    return UART_OK;
}

UartStatus_t uart_send_byte(uint8_t data) {
    if (!s_initialized) return UART_ERROR;
    printf("[UART] TX: 0x%02X ('%c')\n", data, (data >= 32) ? data : '.');
    return UART_OK;
}

UartStatus_t uart_send_string(const char *str) {
    if (!s_initialized || str == NULL) return UART_ERROR;
    printf("[UART] TX String: \"%s\"\n", str);
    return UART_OK;
}

UartStatus_t uart_send_buffer(const uint8_t *buf, uint8_t len) {
    if (!s_initialized || buf == NULL) return UART_ERROR;
    printf("[UART] TX Buffer (%u bytes): ", len);
    for (uint8_t i = 0; i < len; i++) {
        printf("0x%02X ", buf[i]);
    }
    printf("\n");
    return UART_OK;
}

UartStatus_t uart_receive(uint8_t *out_byte) {
    if (!s_initialized || out_byte == NULL) return UART_ERROR;
    if (s_rx_buffer[s_rx_index] == '\0') return UART_TIMEOUT;

    *out_byte = s_rx_buffer[s_rx_index++];
    return UART_OK;
}

void uart_print_config(void) {
    printf("[UART] Config: Baud=%lu DataBits=%u Parity=%u StopBits=%u\n",
           (unsigned long)s_config.baud_rate,
           s_config.data_bits,
           s_config.parity,
           s_config.stop_bits);
}