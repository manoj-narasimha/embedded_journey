#include <stdio.h>
#include <stdint.h>

// ── Firmware-realistic examples of all 4 const pointer types ──

// Type 2: pointer to const — safe read-only buffer parameter
void uart_transmit(const uint8_t *buf, uint8_t len) {
    printf("[UART TX] %u bytes: ", len);
    for (uint8_t i = 0U; i < len; i++) {
        printf("0x%02X ", buf[i]);
    }
    printf("\n");
    // *buf = 0;  // ← compiler would catch this ✅
}

// Type 2: read-only string parameter
void log_message(const char *msg) {
    printf("[LOG] %s\n", msg);
}

// Type 3: const pointer to hardware register (fixed address)
// (simulated — on STM32 this would be: uint32_t * const ODR = (uint32_t*)0x40020014)
static uint32_t sim_ODR_reg = 0U;
uint32_t * const ODR = &sim_ODR_reg;

int main(void) {
    printf("=== const Pointer Variants ===\n\n");

    uint8_t  val_a = 10U;
    uint8_t  val_b = 20U;

    // ── Type 1: uint8_t *ptr — fully mutable
    printf("--- Type 1: fully mutable pointer ---\n");
    uint8_t *ptr1 = &val_a;
    printf("*ptr1 = %u (val_a)\n", *ptr1);
    *ptr1 = 55U;
    printf("After *ptr1=55: val_a = %u\n", val_a);
    ptr1 = &val_b;
    printf("After ptr1=&val_b: *ptr1 = %u\n", *ptr1);

    // ── Type 2: const uint8_t *ptr — can't change value
    printf("\n--- Type 2: pointer to const (read-only data) ---\n");
    const uint8_t *ptr2 = &val_a;
    printf("*ptr2 = %u\n", *ptr2);
    ptr2 = &val_b;
    printf("After ptr2=&val_b: *ptr2 = %u\n", *ptr2);
    // *ptr2 = 99;  // ← uncommenting this causes compile error

    // ── Type 2 in use — UART transmit
    printf("\n--- Type 2 in use: uart_transmit ---\n");
    uint8_t packet[] = {0xAAU, 0xBBU, 0xCCU, 0xDDU};
    uart_transmit(packet, sizeof(packet));
    log_message("System initialized");

    // ── Type 3: uint8_t * const ptr — fixed pointer
    printf("\n--- Type 3: const pointer (fixed address) ---\n");
    uint8_t * const ptr3 = &val_a;
    printf("*ptr3 = %u\n", *ptr3);
    *ptr3 = 77U;
    printf("After *ptr3=77: val_a = %u\n", val_a);
    // ptr3 = &val_b;  // ← uncommenting causes compile error

    // ── Type 3 in use — hardware register simulation
    printf("\n--- Type 3 in use: fixed ODR register pointer ---\n");
    printf("ODR before: 0x%08lX\n", (unsigned long)*ODR);
    *ODR |= (1UL << 5U);    // set pin 5
    printf("ODR after set pin5: 0x%08lX\n", (unsigned long)*ODR);
    *ODR &= ~(1UL << 5U);   // clear pin 5
    printf("ODR after clear pin5: 0x%08lX\n", (unsigned long)*ODR);
    // ODR = NULL;  // ← uncommenting causes compile error

    // ── Type 4: const uint8_t * const — fully immutable
    printf("\n--- Type 4: fully immutable (flash lookup table) ---\n");
    static const uint8_t lut[8] = {0U,36U,71U,100U,128U,150U,178U,200U};
    const uint8_t * const lut_ptr = lut;
    printf("Sine LUT: ");
    for (uint8_t i = 0U; i < 8U; i++) {
        printf("%u ", lut_ptr[i]);
    }
    printf("\n");

    return 0;
}