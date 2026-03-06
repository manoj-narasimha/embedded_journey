#include <stdio.h>
#include <stdint.h>

// Hardware constants — always use these patterns in embedded
#define LED_PIN         (5U)
#define MAX_BUFFER_SIZE (64U)
#define CPU_FREQ_HZ     (168000000UL)   // UL = unsigned long
#define VREF_MV         (3300U)

// Prefer const over #define when possible (type-safe)
const uint8_t  MAX_RETRIES   = 3;
const uint16_t TIMEOUT_MS    = 1000;

// Compute constants at compile time — zero runtime cost
#define MS_TO_TICKS(ms)   ((ms) * (CPU_FREQ_HZ / 1000UL))

int main(void) {
    printf("LED Pin        : %u\n",  LED_PIN);
    printf("Buffer Size    : %u\n",  MAX_BUFFER_SIZE);
    printf("CPU Frequency  : %lu Hz\n", CPU_FREQ_HZ);
    printf("Max Retries    : %u\n",  MAX_RETRIES);
    printf("Timeout        : %u ms\n", TIMEOUT_MS);
    printf("1ms in ticks   : %lu\n", MS_TO_TICKS(1));
    printf("500ms in ticks : %lu\n", MS_TO_TICKS(500));

    return 0;
}