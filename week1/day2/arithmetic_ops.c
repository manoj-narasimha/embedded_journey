#include <stdio.h>
#include <stdint.h>

int main(void) {
    uint8_t buffer_size = 8;
    uint8_t index = 0;
    // Note: a % b => remainder of a/b. if a < b, then a % b = a; else if a == b, then a % b = 0;

    printf("=== Circular Buffer Index (modulo magic) ===\n");
    for (uint8_t i = 0; i < 20; i++) {
        printf("Step %2u -> index = %u\n", i, index);
        printf("%u %% %u  = %d  (remainder)\n",(index+1), buffer_size, (index + 1) % buffer_size);
        index = (index + 1) % buffer_size;  // wraps 0→1→...→7→0→1...

    }

    // Integer division truncates — important to know
    printf("\n=== Integer Division ===\n");
    printf("7 / 2   = %d  (not 3.5!)\n", 7 / 2);
    printf("7 %% 2  = %d  (remainder)\n", 7 % 2);

    // ADC conversion example — you'll do this on STM32
    uint16_t adc_raw    = 2048;   // 12-bit ADC, 0–4095
    uint16_t adc_max    = 4095;
    uint16_t voltage_mv = (uint16_t)((uint32_t)adc_raw * 3300 / adc_max);
    printf("\n=== ADC to Voltage ===\n");
    printf("ADC raw: %u -> Voltage: %u mV\n", adc_raw, voltage_mv);

    return 0;
}