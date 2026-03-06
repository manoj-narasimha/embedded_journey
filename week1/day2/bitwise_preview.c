#include <stdio.h>
#include <stdint.h>

int main(void) {
    uint8_t reg = 0b00000000;  // All bits off

    // Set bit 3 using OR
    reg = reg | 0b00001000;
    printf("After setting bit 3 : 0x%02X (%u)\n", reg, reg);

    // Clear bit 3 using AND + NOT
    reg = reg & ~(0b00001000);
    printf("After clearing bit 3: 0x%02X (%u)\n", reg, reg);

    // Left shift — multiply by 2
    uint8_t val = 1;
    printf("\nLeft shifts of 1:\n");
    for (int i = 0; i < 8; i++) {
        printf("1 << %d = %3u (0x%02X)\n", i, val, val);
        val = val << 1;
    }

    return 0;
}