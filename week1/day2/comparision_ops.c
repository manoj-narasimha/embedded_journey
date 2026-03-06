#include <stdio.h>
#include <stdint.h>

int main(void) {
    uint8_t sensor_value = 200;
    int8_t  threshold    = -10;

    // This looks like it should print "sensor > threshold"
    // but signed/unsigned comparison causes BUGS
    printf("threshold: %u", (uint8_t)threshold);
    if (sensor_value > (uint8_t)threshold) {
        printf("sensor_value > threshold (correct)\n");
    }

    // Safe comparisons
    uint8_t a = 100, b = 200;
    printf("\na = %u, b = %u\n", a, b);
    printf("a == b  : %d\n", a == b);
    printf("a != b  : %d\n", a != b);
    printf("a <  b  : %d\n", a <  b);
    printf("a >  b  : %d\n", a >  b);

    // Ternary operator — very common in embedded
    uint8_t led_state = (sensor_value > 100) ? 1 : 0;
    printf("\nLED state (sensor > 100 -> ON): %u\n", led_state);

    return 0;
}