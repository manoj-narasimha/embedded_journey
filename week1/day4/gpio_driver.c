#include "gpio_driver.h"
#include <stdio.h>

// ── Private (static) data — not visible outside this file ─────
static uint8_t s_pin_mode [GPIO_MAX_PINS] = {0};  // 0=input, 1=output
static uint8_t s_pin_state[GPIO_MAX_PINS] = {0};  // 0=low,   1=high

// ── Private helper ─────────────────────────────────────────────
static uint8_t is_valid_pin(uint8_t pin) {
    return (pin < GPIO_MAX_PINS) ? 1U : 0U;
}

// ── Public functions ───────────────────────────────────────────
GpioStatus_t gpio_init(uint8_t pin, GpioMode_t mode) {
    if (!is_valid_pin(pin)) {
        printf("[GPIO] ERROR: invalid pin %u\n", pin);
        return GPIO_ERROR;
    }
    s_pin_mode[pin]  = (uint8_t)mode;
    s_pin_state[pin] = 0U;
    printf("[GPIO] Pin %2u initialized as %s\n",
           pin, mode == GPIO_MODE_OUTPUT ? "OUTPUT" : "INPUT");
    return GPIO_OK;
}

GpioStatus_t gpio_set(uint8_t pin) {
    if (!is_valid_pin(pin))          return GPIO_ERROR;
    if (s_pin_mode[pin] != GPIO_MODE_OUTPUT) {
        printf("[GPIO] ERROR: pin %u is not OUTPUT\n", pin);
        return GPIO_ERROR;
    }
    s_pin_state[pin] = 1U;
    printf("[GPIO] Pin %2u → HIGH\n", pin);
    return GPIO_OK;
}

GpioStatus_t gpio_clear(uint8_t pin) {
    if (!is_valid_pin(pin))          return GPIO_ERROR;
    if (s_pin_mode[pin] != GPIO_MODE_OUTPUT) {
        printf("[GPIO] ERROR: pin %u is not OUTPUT\n", pin);
        return GPIO_ERROR;
    }
    s_pin_state[pin] = 0U;
    printf("[GPIO] Pin %2u → LOW\n", pin);
    return GPIO_OK;
}

GpioStatus_t gpio_toggle(uint8_t pin) {
    if (!is_valid_pin(pin))          return GPIO_ERROR;
    if (s_pin_mode[pin] != GPIO_MODE_OUTPUT) return GPIO_ERROR;
    s_pin_state[pin] ^= 1U;
    printf("[GPIO] Pin %2u → TOGGLE → %s\n",
           pin, s_pin_state[pin] ? "HIGH" : "LOW");
    return GPIO_OK;
}

uint8_t gpio_read(uint8_t pin) {
    if (!is_valid_pin(pin)) return 0U;
    return s_pin_state[pin];
}

void gpio_dump(void) {
    printf("\n[GPIO] ── Pin State Dump ──────────────────\n");
    printf("[GPIO] Pin | Mode   | State\n");
    printf("[GPIO] ----+--------+------\n");
    for (uint8_t i = 0; i < GPIO_MAX_PINS; i++) {
        if (s_pin_mode[i] != 0 || s_pin_state[i] != 0) {
            printf("[GPIO]  %2u | %-6s | %s\n",
                   i,
                   s_pin_mode[i] == GPIO_MODE_OUTPUT ? "OUTPUT" : "INPUT",
                   s_pin_state[i] ? "HIGH" : "LOW");
        }
    }
    printf("[GPIO] ───────────────────────────────────\n\n");
}