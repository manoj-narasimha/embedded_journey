#include "converter.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>

// ── Print binary with grouping ─────────────────────────────────
void print_binary8(uint8_t val) {
    printf("0b");
    for (int i = 7; i >= 0; i--) {
        printf("%u", (val >> i) & 1U);
        if (i == 4) printf("_");
    }
}

void print_binary16(uint16_t val) {
    printf("0b");
    for (int i = 15; i >= 0; i--) {
        printf("%u", (val >> i) & 1U);
        if (i % 4 == 0 && i != 0) printf("_");
    }
}

void print_binary32(uint32_t val) {
    printf("0b");
    for (int i = 31; i >= 0; i--) {
        printf("%u", (val >> i) & 1U);
        if (i % 4 == 0 && i != 0) printf("_");
    }
}

// ── Full conversion display ────────────────────────────────────
void convert_all8(uint8_t val) {
    printf("\n  ┌─────────────────────────────────────┐\n");
    printf("  │  Value : %-28u│\n", val);
    printf("  ├─────────────────────────────────────┤\n");
    printf("  │  Dec   : %-28u│\n", val);
    printf("  │  Hex   : 0x%02X%-24s│\n", val, "");
    printf("  │  Oct   : 0o%-27o│\n", val);
    printf("  │  Bin   : ");
    print_binary8(val);
    printf("%-10s│\n", "");
    printf("  │  Size  : 8-bit (uint8_t)             │\n");
    printf("  │  Range : 0 to 255                    │\n");
    printf("  └─────────────────────────────────────┘\n");
}

void convert_all16(uint16_t val) {
    printf("\n  ┌─────────────────────────────────────┐\n");
    printf("  │  Value : %-28u│\n", val);
    printf("  ├─────────────────────────────────────┤\n");
    printf("  │  Dec   : %-28u│\n", val);
    printf("  │  Hex   : 0x%04X%-22s│\n", val, "");
    printf("  │  Oct   : 0o%-27o│\n", val);
    printf("  │  Bin   : ");
    print_binary16(val);
    printf("  │\n");
    printf("  │  Size  : 16-bit (uint16_t)            │\n");
    printf("  │  Range : 0 to 65535                  │\n");
    printf("  └─────────────────────────────────────┘\n");
}

void convert_all32(uint32_t val) {
    printf("\n  ┌──────────────────────────────────────────────┐\n");
    printf("  │  Value : %-37lu│\n", (unsigned long)val);
    printf("  ├──────────────────────────────────────────────┤\n");
    printf("  │  Dec   : %-37lu│\n", (unsigned long)val);
    printf("  │  Hex   : 0x%08lX%-29s│\n", (unsigned long)val, "");
    printf("  │  Oct   : 0o%-35lo│\n", (unsigned long)val);
    printf("  │  Bin   : ");
    print_binary32(val);
    printf("  │\n");
    printf("  │  Size  : 32-bit (uint32_t)                   │\n");
    printf("  │  Range : 0 to 4,294,967,295                  │\n");
    printf("  └──────────────────────────────────────────────┘\n");
}

// ── Conversion utilities ───────────────────────────────────────
ConvStatus_t decimal_to_binary_str(uint32_t val,
                                    char *out_buf,
                                    uint8_t buf_size) {
    if (out_buf == NULL)  return CONV_ERROR_NULL;
    if (buf_size < 33U)   return CONV_ERROR_RANGE;

    out_buf[32] = '\0';
    for (int i = 31; i >= 0; i--) {
        out_buf[31 - i] = (char)('0' + ((val >> i) & 1U));
    }
    return CONV_OK;
}

uint32_t binary_str_to_decimal(const char *bin_str) {
    if (bin_str == NULL) return 0U;
    uint32_t result = 0U;
    while (*bin_str == '0' || *bin_str == '1') {
        result = (result << 1U) | (uint32_t)(*bin_str - '0');
        bin_str++;
    }
    return result;
}

uint32_t hex_to_decimal(const char *hex_str) {
    if (hex_str == NULL) return 0U;
    uint32_t result = 0U;
    // skip 0x prefix if present
    if (hex_str[0] == '0' &&
       (hex_str[1] == 'x' || hex_str[1] == 'X')) {
        hex_str += 2;
    }
    while (*hex_str) {
        uint8_t digit = 0U;
        if      (*hex_str >= '0' && *hex_str <= '9') digit = (uint8_t)(*hex_str - '0');
        else if (*hex_str >= 'a' && *hex_str <= 'f') digit = (uint8_t)(*hex_str - 'a' + 10);
        else if (*hex_str >= 'A' && *hex_str <= 'F') digit = (uint8_t)(*hex_str - 'A' + 10);
        else break;
        result = (result << 4U) | digit;
        hex_str++;
    }
    return result;
}

// ── ASCII table ────────────────────────────────────────────────
void print_ascii_table(void) {
    printf("\n  ── Printable ASCII Table ───────────────────────\n");
    printf("  Dec  Hex  Char  │  Dec  Hex  Char  │  Dec  Hex  Char\n");
    printf("  ─────────────────┼──────────────────┼────────────────\n");
    for (int i = 32; i < 64; i++) {
        printf("  %3d  0x%02X  %c     │  %3d  0x%02X  %c     │  %3d  0x%02X  %c\n",
               i,    i,    (char)i,
               i+32, i+32, (char)(i+32),
               i+64, i+64, (char)(i+64));
    }
}