#include <stdio.h>
#include <stdint.h>

int main(void) {
    uint8_t sensor_val = 254;
    printf("Sensor value: %u\n", sensor_val);
    sensor_val += 1; // This will cause an overflow
    printf("Sensor value after increment: %u\n", sensor_val);
    sensor_val += 1; // This will cause another overflow
    printf("Sensor value after second increment: %u\n", sensor_val);
    sensor_val += 1; // This will cause yet another overflow
    printf("Sensor value after third increment: %u\n", sensor_val);

    int8_t signed_val = 126;
    printf("Signed value: %d\n", signed_val);
    signed_val += 1; // This will cause an overflow
    printf("Signed value after increment: %d\n", signed_val);
    signed_val += 1; // This will cause another overflow
    printf("Signed value after second increment: %d\n", signed_val);

    return 0;
}