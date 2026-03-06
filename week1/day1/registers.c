#include <stdio.h>
#include <stdint.h>

// In real embedded code, registers are just memory addresses.
// Today we simulate this with variables.

// Imagine this is a GPIO Output Data Register
uint32_t GPIO_ODR = 0x00000000;  // All 16 pins OFF at start

void pin_set(uint8_t pin) {
    GPIO_ODR |= (1U << pin);     // Set bit at position 'pin'
}

void pin_clear(uint8_t pin) {
    GPIO_ODR &= ~(1U << pin);    // Clear bit at position 'pin'
}

void pin_toggle(uint8_t pin) {
    GPIO_ODR ^= (1U << pin);     // Toggle bit at position 'pin'
}

uint8_t pin_read(uint8_t pin) {
    return (GPIO_ODR >> pin) & 1U;  // Read single bit
}

void print_register(void) {
    printf("GPIO_ODR = 0x%08X  (binary: ", GPIO_ODR);
    for (int i = 15; i >= 0; i--) {
        printf("%u", (GPIO_ODR >> i) & 1U);
        if (i % 4 == 0 && i != 0) printf("_");
    }
    printf(")\n");
}

int main(void) {
    printf("=== GPIO Register Simulator ===\n\n");

    print_register();

    printf("\nSetting pin 0 (LED on PA0)...\n");
    pin_set(0);
    print_register();

    printf("\nSetting pin 5 (LED on PA5)...\n");
    pin_set(5);
    print_register();

    printf("\nReading pin 5: %u\n", pin_read(5));
    printf("Reading pin 0: %u\n", pin_read(0));

    printf("\nToggling pin 0...\n");
    pin_toggle(0);
    print_register();

    printf("\nClearing pin 5...\n");
    pin_clear(5);
    print_register();

    return 0;
}