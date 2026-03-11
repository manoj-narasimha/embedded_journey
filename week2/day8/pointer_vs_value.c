#include <stdio.h>
#include <stdint.h>

// pass by value
void double_value_wrong(uint32_t x) {
    x = x * 2U;
    printf("  Inside wrong: x = %lu\n", (unsigned long)x);
}

// pass by pointer - original value changed
void double_value_correct(uint32_t *x) {
    *x = *x * 2U;
    printf("  Inside correct: *x = %lu\n", (unsigned long)*x);
}

// Real embedded pattern
typedef struct {
    uint16_t voltage_mv;
    uint16_t current_ma;
    uint8_t fault_flag;
} PowerReading_t;

void read_power_sensor(PowerReading_t *out) {
    if (out == NULL)
        return;
    // SIMULATE HARDWARE READ
    out->voltage_mv = 3300U;
    out->current_ma = 150U;
    out->fault_flag = 0U;
}

int main(void) {
    printf("=== Pass by Value vs Pointer ===\n\n");

    uint32_t counter = 100UL;

    printf("Before: counter = %lu\n", (unsigned long)counter);
    double_value_wrong(counter);
    printf("After wrong: counter = %lu  (unchanged!)\n\n",
           (unsigned long)counter);

    printf("Before: counter = %lu\n", (unsigned long)counter);
    double_value_correct(&counter);
    printf("After correct: counter = %lu  (changed!)\n\n",
           (unsigned long)counter);
    
    // Multiple return values via pointer
    printf("--- Multiple return values ---\n");
    PowerReading_t pwr = {0};
    read_power_sensor(&pwr);
    printf("Voltage : %u mV\n", pwr.voltage_mv);
    printf("Current : %u mA\n", pwr.current_ma);
    printf("Fault   : %u\n",    pwr.fault_flag);

    return 0;
}