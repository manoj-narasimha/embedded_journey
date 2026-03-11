#include <stdio.h>
#include <stdint.h>

int main(void) {
    printf("=== Pointer Basics ===\n\n");

    uint8_t temperature = 25U;
    uint16_t adc_value = 4095U;
    uint32_t frequency = 168000000UL;

    // declare pointers
    uint8_t *p_temp = &temperature;
    uint16_t *p_adc = &adc_value;
    uint32_t *p_freq = &frequency;

    // print values and addresses
    printf("---Print values and Addresses---\n");
    printf("Temperature: %u\n", temperature);
    printf("ADC_Value: %u\n", adc_value);
    printf("Frequency: %lu\n", (unsigned long)frequency);

    printf("\n--- Addresses (via & operator) ---\n");
    printf("&temperature = %p\n",  (void*)&temperature);
    printf("&adc_value   = %p\n",  (void*)&adc_value);
    printf("&frequency   = %p\n",  (void*)&frequency);
    printf("\n--- Pointer values (addresses they store) ---\n");
    printf("p_temp = %p\n",  (void*)p_temp);
    printf("p_adc  = %p\n",  (void*)p_adc);
    printf("p_freq = %p\n",  (void*)p_freq);

    printf("\n--- Dereferenced values (values AT those addresses) ---\n");
    printf("*p_temp = %u\n", *p_temp);
    printf("*p_adc = %u\n", *p_adc);
    printf("*p_freq = %lu\n", (unsigned long)*p_freq);

    // Modify through pointer
    printf("\n--- Modify through pointer ---\n");
    printf("Before: Temperature = %u\n", temperature);
    *p_temp = 99U;
    printf("After: Temperature = %u\n", temperature);

    // Pointer sizes
    printf("\n--- Pointer sizes ---\n");
    printf("sizeof(uint8_t *) = %zu bytes \n", sizeof(uint8_t *));
    printf("sizeof(uint16_t *) = %zu bytes\n", sizeof(uint16_t *));
    printf("sizeof(uint32_t *) = %zu bytes\n", sizeof(uint32_t *));
    printf("sizeof(void     *) = %zu bytes\n", sizeof(void     *));
    printf("(All the same — just an address)\n");

    return 0;
}