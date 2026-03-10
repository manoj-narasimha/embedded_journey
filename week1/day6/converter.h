#ifndef CONVERTER_H
#define CONVERTER_H

#include <stdint.h>

// ── Types ──────────────────────────────────────────────────────
typedef enum {
    CONV_OK            = 0,
    CONV_ERROR_RANGE   = 1,
    CONV_ERROR_NULL    = 2
} ConvStatus_t;

// ── Function Declarations ──────────────────────────────────────
void         print_binary8 (uint8_t  val);
void         print_binary16(uint16_t val);
void         print_binary32(uint32_t val);

void         convert_all8  (uint8_t  val);
void         convert_all16 (uint16_t val);
void         convert_all32 (uint32_t val);

ConvStatus_t decimal_to_binary_str (uint32_t val,
                                    char *out_buf,
                                    uint8_t buf_size);
uint32_t     binary_str_to_decimal (const char *bin_str);
uint32_t     hex_to_decimal        (const char *hex_str);

void         print_ascii_table     (void);

#endif // CONVERTER_H