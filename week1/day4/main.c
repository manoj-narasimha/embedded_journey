#include <stdio.h>
#include <stdint.h>

#include "gpio_driver.h"
#include "uart_driver.h"
#include "sensor.h"

// ── Pin Definitions (named constants — never use magic numbers) ─
#define PIN_LED_STATUS   (5U)
#define PIN_LED_ERROR    (6U)
#define PIN_BUTTON       (0U)

// ── Error handler ──────────────────────────────────────────────
static void system_error(const char *msg) {
    printf("\n[SYSTEM] ❌ FATAL ERROR: %s\n", msg);
    gpio_set(PIN_LED_ERROR);    // turn on error LED
    while (1) { }               // halt — real firmware would reset here
}

// ── System init ────────────────────────────────────────────────
static void system_init(void) {
    printf("╔══════════════════════════════════════╗\n");
    printf("║   Embedded Firmware Simulator v1.0   ║\n");
    printf("╚══════════════════════════════════════╝\n\n");

    // Init GPIO
    if (gpio_init(PIN_LED_STATUS, GPIO_MODE_OUTPUT) != GPIO_OK) {
        system_error("GPIO init failed");
    }
    if (gpio_init(PIN_LED_ERROR, GPIO_MODE_OUTPUT) != GPIO_OK) {
        system_error("GPIO init failed");
    }
    if (gpio_init(PIN_BUTTON, GPIO_MODE_INPUT) != GPIO_OK) {
        system_error("GPIO init failed");
    }

    // Init UART
    UartConfig_t uart_cfg = {
        .baud_rate = UART_BAUD_115200,
        .data_bits = 8U,
        .stop_bits = 1U,
        .parity    = 0U
    };
    if (uart_init(&uart_cfg) != UART_OK) {
        system_error("UART init failed");
    }

    // Init Sensor
    if (sensor_init(SENSOR_I2C_ADDR) != SENSOR_OK) {
        system_error("Sensor init failed");
    }

    printf("\n[SYSTEM] ✅ All peripherals initialized\n\n");
}

// ── Main loop ──────────────────────────────────────────────────
int main(void) {
    system_init();

    // Simulate 5 sensor read cycles
    SensorData_t reading = {0};

    printf("[SYSTEM] Starting main loop...\n\n");

    for (uint8_t cycle = 0; cycle < 5; cycle++) {
        printf("── Cycle %u ───────────────────────────────\n", cycle + 1U);

        // Blink status LED
        gpio_toggle(PIN_LED_STATUS);

        // Read sensor
        if (sensor_read(&reading) == SENSOR_OK) {
            sensor_print(&reading);

            // Send data over UART
            uart_send_string("SENSOR_DATA_OK");

            // Alert if temperature too high
            if (reading.temperature_x100 > 3000U) {
                printf("[SYSTEM] ⚠️  High temp alert!\n");
                gpio_set(PIN_LED_ERROR);
            } else {
                gpio_clear(PIN_LED_ERROR);
            }
        } else {
            printf("[SYSTEM] Sensor read failed!\n");
            gpio_set(PIN_LED_ERROR);
        }

        printf("\n");
    }

    // Final state dump
    gpio_dump();

    printf("[SYSTEM] Main loop complete.\n");
    return 0;
}