#include "bit_tools.h"
#include <stdio.h>

// ── Register inspector ─────────────────────────────────────────
void register_inspect(uint32_t reg, const char *name) {
    printf("\n  ── Register: %s = 0x%08lX ──────────────────\n",
           name, (unsigned long)reg);

    // Bit position header
    printf("  Bit: ");
    for (int i = 31; i >= 0; i--) {
        if (i % 8 == 7) printf("|");
        printf("%2d", i);
    }
    printf("\n");

    // Bit values
    printf("  Val: ");
    for (int i = 31; i >= 0; i--) {
        if (i % 8 == 7) printf("| ");
        printf(" %lu", READ_BIT(reg, (uint8_t)i));
    }
    printf("\n");

    // Hex breakdown by byte
    printf("  Byte breakdown:\n");
    printf("    [31:24] = 0x%02lX  [23:16] = 0x%02lX  "
           "[15:8] = 0x%02lX  [7:0] = 0x%02lX\n",
           (unsigned long)((reg >> 24U) & 0xFFU),
           (unsigned long)((reg >> 16U) & 0xFFU),
           (unsigned long)((reg >> 8U)  & 0xFFU),
           (unsigned long)( reg         & 0xFFU));

    // Set bits list
    printf("  Set bits: ");
    uint8_t any = 0U;
    for (int i = 31; i >= 0; i--) {
        if (IS_SET(reg, (uint8_t)i)) {
            printf("%d ", i);
            any = 1U;
        }
    }
    if (!any) printf("(none)");
    printf("\n");
}

// ── Register diff — show what changed ─────────────────────────
void register_diff(uint32_t before, uint32_t after, const char *name) {
    uint32_t changed = before ^ after;
    printf("\n  ── Register Diff: %s ────────────────────\n", name);
    printf("  Before : 0x%08lX\n", (unsigned long)before);
    printf("  After  : 0x%08lX\n", (unsigned long)after);
    printf("  Changed: 0x%08lX\n", (unsigned long)changed);

    if (changed == 0U) {
        printf("  No bits changed.\n");
        return;
    }

    printf("  Bit changes:\n");
    for (int i = 31; i >= 0; i--) {
        if (IS_SET(changed, (uint8_t)i)) {
            uint8_t was = (uint8_t)READ_BIT(before, (uint8_t)i);
            uint8_t now = (uint8_t)READ_BIT(after,  (uint8_t)i);
            printf("    Bit %2d: %u → %u  (%s)\n",
                   i, was, now,
                   now ? "SET" : "CLEARED");
        }
    }
}

// ── Build a bitmask ────────────────────────────────────────────
uint32_t build_mask(uint8_t start_bit, uint8_t num_bits) {
    if (num_bits == 0U || num_bits > 32U) return 0U;
    uint32_t mask = (num_bits == 32U) ?
                    0xFFFFFFFFU :
                    (uint32_t)((1UL << num_bits) - 1UL);
    return mask << start_bit;
}

// ── STM32 GPIO MODER decoder ───────────────────────────────────
void gpio_moder_decode(uint32_t moder) {
    const char *modes[] = {"INPUT ", "OUTPUT", "ALT-FN", "ANALOG"};
    printf("\n  ── GPIO MODER Decode: 0x%08lX ──────────\n",
           (unsigned long)moder);
    printf("  Pin | Mode   | Bits[val]\n");
    printf("  ────┼────────┼──────────\n");
    for (int pin = 15; pin >= 0; pin--) {
        uint32_t mode = (moder >> (uint8_t)(pin * 2)) & 0x3U;
        printf("   %2d | %s | [%2d:%2d]=%lu\n",
               pin, modes[mode],
               pin*2+1, pin*2,
               (unsigned long)mode);
    }
}

// ── UART status register decoder ──────────────────────────────
void uart_sr_decode(uint8_t sr) {
    printf("\n  ── UART SR Decode: 0x%02X ───────────────────\n", sr);
    printf("  Bit 7 TXE  (TX empty)      : %s\n",
           IS_SET(sr, 7U) ? "SET   ← safe to write"   : "CLEAR ← busy");
    printf("  Bit 6 TC   (TX complete)   : %s\n",
           IS_SET(sr, 6U) ? "SET   ← transmission done" : "CLEAR");
    printf("  Bit 5 RXNE (RX not empty)  : %s\n",
           IS_SET(sr, 5U) ? "SET   ← data ready to read" : "CLEAR");
    printf("  Bit 4 IDLE (idle line)     : %s\n",
           IS_SET(sr, 4U) ? "SET"  : "CLEAR");
    printf("  Bit 3 ORE  (overrun error) : %s\n",
           IS_SET(sr, 3U) ? "SET   ← ⚠️ data lost!"     : "CLEAR");
    printf("  Bit 2 NF   (noise flag)    : %s\n",
           IS_SET(sr, 2U) ? "SET   ← ⚠️ noise detected" : "CLEAR");
    printf("  Bit 1 FE   (framing error) : %s\n",
           IS_SET(sr, 1U) ? "SET   ← ⚠️ framing error"  : "CLEAR");
    printf("  Bit 0 PE   (parity error)  : %s\n",
           IS_SET(sr, 0U) ? "SET   ← ⚠️ parity error"   : "CLEAR");
}

// ── Range check ────────────────────────────────────────────────
BitToolStatus_t bit_range_check(uint32_t val, uint8_t num_bits) {
    if (num_bits >= 32U) return BT_OK;
    uint32_t max = (1UL << num_bits) - 1UL;
    return (val <= max) ? BT_OK : BT_ERROR;
}

void bit_tools_print_bin32_standalone(uint32_t val) {
    for (int i = 31; i >= 0; i--) {
        printf("%lu", READ_BIT(val, (uint8_t)i));
        if (i % 4 == 0 && i != 0) printf("_");
    }
}