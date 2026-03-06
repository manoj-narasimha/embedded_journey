#include <stdio.h>
#include <stdint.h>

int main(void) {
    // Dangerous implicit cast
    uint16_t big = 300;
    uint8_t  small = (uint8_t)big;  // explicit cast — 300 doesn't fit in 8 bits!
    printf("300 cast to uint8_t: %u\n", small);  // 300 - 256 = 44

    // Safe pattern — always cast to larger type BEFORE multiplying
    uint16_t adc  = 4000;
    uint16_t vref = 3300;

    // WRONG — intermediate result overflows uint16_t
    uint16_t wrong = adc * vref / 4095;  // adc * vref = 13,200,000 → overflows!

    // CORRECT — cast to uint32_t first
    uint32_t correct = (uint32_t)adc * vref / 4095;

    printf("\nWrong  result: %u\n", wrong);
    printf("Correct result: %u mV\n", (uint16_t)correct);

    return 0;
}