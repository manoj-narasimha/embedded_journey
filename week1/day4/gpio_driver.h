#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

#include <stdint.h>

// ── Constants ────────────────────────────────────────────────
#define GPIO_MAX_PINS   (16U)
#define GPIO_PIN_SET    (1U)
#define GPIO_PIN_RESET  (0U)

// ── Types ────────────────────────────────────────────────────
typedef enum {
    GPIO_MODE_INPUT  = 0,
    GPIO_MODE_OUTPUT = 1
} GpioMode_t;

typedef enum {
    GPIO_OK    = 0,
    GPIO_ERROR = 1
} GpioStatus_t;

// ── Function Declarations ─────────────────────────────────────
GpioStatus_t gpio_init  (uint8_t pin, GpioMode_t mode);
GpioStatus_t gpio_set   (uint8_t pin);
GpioStatus_t gpio_clear (uint8_t pin);
GpioStatus_t gpio_toggle(uint8_t pin);
uint8_t      gpio_read  (uint8_t pin);
void         gpio_dump  (void);        // print all pin states

#endif // GPIO_DRIVER_H