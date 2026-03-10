#ifndef BIT_TOOLS_H
#define BIT_TOOLS_H

#include <stdint.h>

// ── Macros ─────────────────────────────────────────────────────
#define BIT(n)               (1UL << (n))
#define SET_BIT(reg,  bit)   ((reg) |=  BIT(bit))
#define CLEAR_BIT(reg, bit)  ((reg) &= ~BIT(bit))
#define TOGGLE_BIT(reg, bit) ((reg) ^=  BIT(bit))
#define READ_BIT(reg,  bit)  (((reg) >> (bit)) & 1UL)
#define IS_SET(reg,    bit)  (((reg) &  BIT(bit)) != 0U)

// ── Types ──────────────────────────────────────────────────────
typedef enum {
    BT_OK    = 0,
    BT_ERROR = 1
} BitToolStatus_t;

// ── Function Declarations ──────────────────────────────────────
void           register_inspect (uint32_t reg, const char *name);
void           register_diff    (uint32_t before,
                                 uint32_t after,
                                 const char *name);
uint32_t       build_mask       (uint8_t start_bit, uint8_t num_bits);
void           gpio_moder_decode(uint32_t moder);
void           uart_sr_decode   (uint8_t sr);
BitToolStatus_t bit_range_check (uint32_t val,
                                 uint8_t  num_bits);
void bit_tools_print_bin32_standalone(uint32_t val);

#endif // BIT_TOOLS_H