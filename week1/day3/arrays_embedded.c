#include <stdio.h>
#include <stdint.h>

#define ADC_SAMPLES     (8U)
#define LOOKUP_SIZE     (8U)

// Global buffer — goes in BSS (correct for embedded)
uint16_t adc_buffer[ADC_SAMPLES];
// Lookup table in flash (const = stored in flash on MCU, saves RAM)
const uint8_t sine_lookup[LOOKUP_SIZE] = {0, 71, 128, 178, 200, 178, 128, 71};

uint16_t average(uint16_t *buf, uint8_t len) {
    uint32_t sum = 0;
    for (uint8_t i = 0; i < len; i++) {
        sum += buf[i];
    }
    return (uint16_t)(sum / len);
}

uint16_t max_value(uint16_t *buf, uint8_t len) {
    uint16_t max = buf[0];
    for (uint8_t i = 0; i < len; i++) {
        if (buf[i] > max)
            max = buf[i];
    }
    return max;
}

int main(void) {
    // Simulate ADC readings
    uint16_t raw_readings[ADC_SAMPLES] = {
        2010, 2048, 2035, 2100, 1998, 2055, 2040, 2022
    };

    // Copy to global buffer
    for (uint8_t i = 0; i < ADC_SAMPLES; i++) {
        adc_buffer[i] = raw_readings[i];
    }

    printf("=== ADC Sample Buffer ===\n");
    for (uint8_t i = 0; i < ADC_SAMPLES; i++) {
        printf("Sample[%u] = %u\n", i, adc_buffer[i]);
    }

    printf("\nAverage : %u\n", average(adc_buffer, ADC_SAMPLES));
    printf("Maximum : %u\n",   max_value(adc_buffer, ADC_SAMPLES));

    // Array length — always use this formula
    uint8_t lookup_len = sizeof(sine_lookup) / sizeof(sine_lookup[0]);
    printf("\n=== Sine Lookup Table ===\n");
    for (uint8_t i = 0; i < lookup_len; i++) {
        printf("sine[%u] = %3u  ", i, sine_lookup[i]);
        // Visual bar
        for (uint8_t b = 0; b < sine_lookup[i] / 10; b++) printf("█");
        printf("\n");
    }

    return 0;
} 