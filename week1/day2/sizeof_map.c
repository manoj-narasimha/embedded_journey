#include <stdio.h>
#include <stdint.h>

int main(void) {
    printf("=== Memory Size Map ===\n");
    printf("char      : %zu byte(s)\n", sizeof(char));
    printf("int       : %zu byte(s)\n", sizeof(int));
    printf("long      : %zu byte(s)\n", sizeof(long));
    printf("float     : %zu byte(s)\n", sizeof(float));
    printf("double    : %zu byte(s)\n", sizeof(double));

    printf("\n=== Embedded-Safe Types ===\n");
    printf("uint8_t   : %zu byte(s)  → range: 0 to 255\n",        sizeof(uint8_t));
    printf("int8_t    : %zu byte(s)  → range: -128 to 127\n",     sizeof(int8_t));
    printf("uint16_t  : %zu byte(s)  → range: 0 to 65535\n",      sizeof(uint16_t));
    printf("int16_t   : %zu byte(s)  → range: -32768 to 32767\n", sizeof(int16_t));
    printf("uint32_t  : %zu byte(s)  → range: 0 to 4294967295\n", sizeof(uint32_t));
    printf("int32_t   : %zu byte(s)\n",                            sizeof(int32_t));

    // Struct sizing — memory alignment matters in embedded!
    struct PackedSensors {
        uint8_t  temperature;   // 1 byte
        uint16_t pressure;      // 2 bytes
        uint32_t timestamp;     // 4 bytes
    };

    printf("\n=== Struct Size ===\n");
    printf("struct PackedSensors: %zu bytes\n", sizeof(struct PackedSensors));
    printf("(you might expect 7, but compiler may add padding!)\n");

    return 0;
}