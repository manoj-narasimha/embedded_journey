#include <stdio.h>
#include <stdint.h>

int main(void) {
    printf("Embedded journey starts now.\n");
    char c = 'A';
    printf("The character is: %c\n", c);
    int x = 42;
    printf("The integer is: %d\n", x);
    float f = 12.45f; // This will cause a warning due to implicit conversion from float to int
    printf("The float value is: %f\n", f);
    double d = 3.14159; // This will also cause a warning due to implicit conversion from double to int
    printf("The double value is: %lf\n", d);

    // Embedded systems often require careful management of resources, so it's important to be mindful of data types and memory usage.
    uint8_t u8 = 255; // Maximum value for uint8_t (0 to 255)
    printf("The uint8_t value is: %u\n", u8);
    int8_t i8 = -128; // Minimum value for int8_t (-128 to 127)
    printf("The int8_t value is: %d\n", i8);
    uint16_t u16 = 65535; // Maximum value for uint16_t (0 to 65535)
    printf("The uint16_t value is: %u\n", u16);
    int16_t i16 = -32768; // Minimum value for int16_t (-32768 to 32767)
    printf("The int16_t value is: %d\n", i16);
    uint32_t u32 = 4294967295; // Maximum value for uint32_t (0 to 4294967295)
    printf("The uint32_t value is: %u\n", u32);
    int32_t i32 = -2147483648; // Minimum value for int32_t (-2147483648 to 2147483647)
    printf("The int32_t value is: %d\n", i32);
    uint64_t u64 = 18446744073709551615U; // Maximum value for uint64_t (0 to 18446744073709551615)
    printf("The uint64_t value is: %u\n", u64);
    // int64_t i64 = -9223372036854775808LL; // Minimum value for int64_t
    // printf("The int64_t value is: %lld\n", i64);
    return 0;
}