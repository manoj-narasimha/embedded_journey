#include <stdio.h>
#include <stdint.h>

int main(void) {
    uint8_t button_pressed = 1;
    uint8_t system_Ready = 1;
    uint8_t error_flag = 0;

    // Logical AND — both must be true
    if (button_pressed && system_Ready && !error_flag) {
        printf("✅ System armed — all conditions met\n");
    }

    // Simulate error
    error_flag = 1;
    if (button_pressed && system_Ready && !error_flag) {
        printf("Armed\n");
    } else {
        printf("❌ Cannot arm — error flag is set\n");
    }

    // Logical OR — any one true
    uint8_t temp_high    = 0;
    uint8_t voltage_low  = 1;
    uint8_t comm_timeout = 0;

    if (temp_high || voltage_low || comm_timeout) {
        printf("⚠️  Fault detected — triggering safe shutdown\n");
    }

    return 0;
}