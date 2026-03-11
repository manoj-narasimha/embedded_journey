#include <stdio.h>
#include <stdint.h>

// Global variables — DATA/BSS segment (low addresses on most systems)
uint32_t g_system_tick = 0UL;
uint8_t  g_device_id   = 0x42U;
uint8_t  g_rx_buffer[16];         // BSS — zeroed

// Simulated hardware register addresses (like STM32)
#define SIM_GPIOA_BASE  (0x40020000U)
#define SIM_GPIOA_ODR   (SIM_GPIOA_BASE + 0x14U)

void print_memory_map(void) {
    printf("=== Memory Address Map ===\n\n");

    printf("--- Global/Static (DATA/BSS) ---\n");
    printf("g_system_tick @ %p  size=%zu\n",
           (void*)&g_system_tick, sizeof(g_system_tick));
    printf("g_device_id   @ %p  size=%zu\n",
           (void*)&g_device_id, sizeof(g_device_id));
    printf("g_rx_buffer   @ %p  size=%zu\n",
           (void*)g_rx_buffer, sizeof(g_rx_buffer));

    // Local variables — STACK (higher addresses, downward growth)
    uint32_t local_a = 1UL;
    uint16_t local_b = 2U;
    uint8_t  local_c = 3U;
    uint8_t  local_arr[8] = {0};

    printf("\n--- Local (STACK) ---\n");
    printf("local_a   @ %p  size=%zu\n",
           (void*)&local_a, sizeof(local_a));
    printf("local_b   @ %p  size=%zu\n",
           (void*)&local_b, sizeof(local_b));
    printf("local_c   @ %p  size=%zu\n",
           (void*)&local_c, sizeof(local_c));
    printf("local_arr @ %p  size=%zu\n",
           (void*)local_arr, sizeof(local_arr));

    // Pointer relationships
    printf("\n--- Pointer Relationships ---\n");
    uint32_t *p_tick = &g_system_tick;
    uint8_t  *p_id   = &g_device_id;
    uint8_t  *p_buf  = g_rx_buffer;

    printf("p_tick = %p  *p_tick = %lu\n",
           (void*)p_tick, (unsigned long)*p_tick);
    printf("p_id   = %p  *p_id   = 0x%02X\n",
           (void*)p_id, *p_id);
    printf("p_buf  = %p  *p_buf  = %u\n",
           (void*)p_buf, *p_buf);

    // Adjacent array elements
    printf("\n--- Array memory is contiguous ---\n");
    uint8_t arr[5] = {1U, 2U, 3U, 4U, 5U};
    for (uint8_t i = 0U; i < 5U; i++) {
        printf("arr[%u] @ %p = %u  (diff from [0]: %td)\n",
               i, (void*)&arr[i], arr[i],
               &arr[i] - &arr[0]);
    }

    // Simulated hardware register pointer (what STM32 does)
    printf("\n--- Hardware Register Pointer (simulated) ---\n");
    printf("GPIOA base address : 0x%08X\n", SIM_GPIOA_BASE);
    printf("GPIOA ODR  address : 0x%08X\n", SIM_GPIOA_ODR);
    printf("Offset of ODR      : 0x%02X (%u bytes)\n",
           SIM_GPIOA_ODR - SIM_GPIOA_BASE,
           SIM_GPIOA_ODR - SIM_GPIOA_BASE);
}

int main(void) {
    print_memory_map();
    return 0;
}