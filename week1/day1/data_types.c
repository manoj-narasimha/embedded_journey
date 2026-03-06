#include <stdio.h>
#include <stdint.h>

int main(void) {
    uint8_t  led_pin    = 13;
    uint16_t adc_value  = 4095;
    uint32_t frequency  = 168000000;  // 168 MHz — STM32F4 max clock!
    int8_t   temperature = -25;

    printf("LED Pin     : %u\n",   led_pin);
    printf("ADC Value   : %u\n",   adc_value);
    printf("CPU Freq    : %u Hz\n", frequency);
    printf("Temperature : %d C\n", temperature);

    // sizeof tells you memory size — critical in embedded
    printf("\n--- Memory sizes ---\n");
    printf("uint8_t  = %zu byte\n",  sizeof(uint8_t));
    printf("uint16_t = %zu bytes\n", sizeof(uint16_t));
    printf("uint32_t = %zu bytes\n", sizeof(uint32_t));
    printf("int   = %d byte\n",  sizeof(int));

    return 0;
}