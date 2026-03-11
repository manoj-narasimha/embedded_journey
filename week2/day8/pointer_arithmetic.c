#include <stdio.h>
#include <stdint.h>

void print_array_info(const char *label,
                      const uint8_t *arr,
                      uint8_t len) {
    printf("%s:\n", label);
    for (uint8_t i = 0U; i < len; i++) {
        printf("  [%u] addr=%p  val=%u\n",
               i, (void*)(arr + i), arr[i]);
    }
}

int main(void) {
    printf("=== Pointer Arithmetic ===\n\n");

    uint8_t arr8[5]  = {10U, 20U, 30U, 40U, 50U};
    uint32_t arr32[4] = {100UL, 200UL, 300UL, 400UL};

    // uint8_t pointer — steps 1 byte at a time
    printf("--- uint8_t array (1-byte steps) ---\n");
    uint8_t *p8 = arr8;
    for (uint8_t i = 0U; i < 5U; i++) {
        printf("  p8+%u = %p  value = %u\n",
               i, (void*)(p8 + i), *(p8 + i));
    }

    // uint32_t pointer — steps 4 bytes at a time
    printf("\n--- uint32_t array (4-byte steps) ---\n");
    uint32_t *p32 = arr32;
    for (uint8_t i = 0U; i < 4U; i++) {
        printf("  p32+%u = %p  value = %lu\n",
               i, (void*)(p32 + i),
               (unsigned long)*(p32 + i));
    }

    // Array name IS a pointer
    printf("\n--- Array name = pointer to first element ---\n");
    printf("arr8      = %p\n", (void*)arr8);
    printf("&arr8[0]  = %p\n", (void*)&arr8[0]);
    printf("Same? %s\n",
           arr8 == &arr8[0] ? "YES ✅" : "NO");

    // Two ways to access elements — identical
    printf("\n--- arr[i] vs *(arr+i) — identical ---\n");
    for (uint8_t i = 0U; i < 5U; i++) {
        printf("  arr8[%u]=%u  *(arr8+%u)=%u  %s\n",
               i, arr8[i],
               i, *(arr8 + i),
               arr8[i] == *(arr8+i) ? "✅" : "❌");
    }

    // Pointer difference
    printf("\n--- Pointer difference ---\n");
    uint8_t *start = &arr8[0];
    uint8_t *end   = &arr8[4];
    printf("end - start = %td elements\n", end - start);

    // Traversal with pointer increment
    printf("\n--- Traversal with ptr++ ---\n");
    uint8_t *ptr = arr8;
    uint8_t *arr_end = arr8 + 5U;
    while (ptr < arr_end) {
        printf("  *ptr = %u  (addr %p)\n",
               *ptr, (void*)ptr);
        ptr++;
    }

    return 0;
}