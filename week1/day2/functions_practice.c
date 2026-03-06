#include <stdio.h>
#include <stdint.h>

// Function declarations (prototypes) at top — always do this
uint32_t    fahrenheit_to_celsius(uint32_t f);
uint8_t     is_valid_adc(uint16_t value);
uint16_t    map_value(uint16_t in, uint16_t in_min,
                      uint16_t in_max, uint16_t out_min, uint16_t out_max);
void        print_bar(uint8_t percent);

int main(void) {
    // Temperature conversion
    printf("=== Temperature Converter ===\n");
    for (uint32_t f = 32; f <= 212; f += 20) {
        printf("%3lu°F = %2lu°C\n", f, fahrenheit_to_celsius(f));
    }

    // ADC validation
    printf("\n=== ADC Validator ===\n");
    uint16_t readings[] = {0, 512, 2048, 4095, 4096, 9999};
    for (int i = 0; i < 6; i++) {
        printf("ADC %4u: %s\n", readings[i],
               is_valid_adc(readings[i]) ? "VALID" : "INVALID");
    }

    // Value mapping — potentiometer to PWM duty cycle
    printf("\n=== Pot -> PWM Duty Cycle ===\n");
    for (uint16_t pot = 0; pot <= 4095; pot += 512) {
        uint16_t duty = map_value(pot, 0, 4095, 0, 100);
        printf("Pot: %4u -> Duty: %3u%%  ", pot, duty);
        print_bar(duty);
        printf("\n");
    }

    return 0;
}

uint32_t fahrenheit_to_celsius(uint32_t f) {
    return (f - 32) * 5 / 9;
}

uint8_t is_valid_adc(uint16_t value) {
    return (value <= 4095) ? 1 : 0;  // 12-bit ADC max = 4095
}

uint16_t map_value(uint16_t in, uint16_t in_min, uint16_t in_max,
                   uint16_t out_min, uint16_t out_max) {
    return (uint16_t)((uint32_t)(in - in_min) *
           (out_max - out_min) / (in_max - in_min) + out_min);
}

void print_bar(uint8_t percent) {
    uint8_t filled = percent / 5;  // 20 chars = 100%
    printf("[");
    for (uint8_t i = 0; i < 20; i++) {
        printf(i < filled ? "█" : "░");
    }
    printf("]");
}