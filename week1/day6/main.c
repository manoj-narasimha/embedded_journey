#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "converter.h"
#include "bit_tools.h"

// ── Banner ─────────────────────────────────────────────────────
static void print_banner(void) {
    printf("\n");
    printf("  ╔═══════════════════════════════════════════╗\n");
    printf("  ║   Embedded Number Systems & Bit Toolkit   ║\n");
    printf("  ║              Week 1 — Day 6               ║\n");
    printf("  ╚═══════════════════════════════════════════╝\n\n");
}

static void section(const char *title) {
    printf("\n");
    printf("  ╔═══════════════════════════════════════════╗\n");
    printf("  ║  %-41s║\n", title);
    printf("  ╚═══════════════════════════════════════════╝\n");
}

// ══════════════════════════════════════════════════════════════
int main(void) {
    print_banner();

    // ── Demo 1: Number Conversions ────────────────────────────
    section("1. Number System Conversions");

    printf("\n  >> 8-bit value: 42\n");
    convert_all8(42U);

    printf("\n  >> 16-bit value: 4095 (12-bit ADC max)\n");
    convert_all16(4095U);

    printf("\n  >> 32-bit value: 0x40020000 (GPIOA base address)\n");
    convert_all32(0x40020000U);

    printf("\n  >> 32-bit value: 168000000 (STM32F4 CPU clock)\n");
    convert_all32(168000000UL);

    // ── Demo 2: Binary String Conversion ──────────────────────
    section("2. Binary String ↔ Decimal");

    const char *bin_strings[] = {
        "00000001",
        "10101010",
        "11111111",
        "10000000"
    };
    printf("\n  Binary string → Decimal:\n");
    for (uint8_t i = 0; i < 4U; i++) {
        printf("  %s → %lu\n",
               bin_strings[i],
               (unsigned long)binary_str_to_decimal(bin_strings[i]));
    }

    printf("\n  Hex string → Decimal:\n");
    const char *hex_strings[] = {"0xFF", "0x1A", "0x40020000", "0xDEAD"};
    for (uint8_t i = 0; i < 4U; i++) {
        printf("  %-12s → %lu\n",
               hex_strings[i],
               (unsigned long)hex_to_decimal(hex_strings[i]));
    }

    // ── Demo 3: Register Inspector ────────────────────────────
    section("3. Register Inspector");

    uint32_t RCC_AHB1ENR = 0x00000000U;
    SET_BIT(RCC_AHB1ENR, 0U);    // GPIOA
    SET_BIT(RCC_AHB1ENR, 2U);    // GPIOC
    SET_BIT(RCC_AHB1ENR, 21U);   // DMA1
    register_inspect(RCC_AHB1ENR, "RCC_AHB1ENR");

    uint32_t GPIOA_ODR = 0x00000000U;
    SET_BIT(GPIOA_ODR, 5U);      // LED on PA5
    SET_BIT(GPIOA_ODR, 13U);     // LED on PA13
    register_inspect(GPIOA_ODR, "GPIOA_ODR");

    // ── Demo 4: Register Diff ─────────────────────────────────
    section("4. Register Diff (Before vs After)");

    uint32_t moder_before = 0x00000000U;
    uint32_t moder_after  = moder_before;

    // Configure pin 5 as OUTPUT
    moder_after &= ~(3U << (5U * 2U));
    moder_after |=  (1U << (5U * 2U));

    // Configure pin 2 as ALTERNATE FUNCTION
    moder_after &= ~(3U << (2U * 2U));
    moder_after |=  (2U << (2U * 2U));

    register_diff(moder_before, moder_after, "GPIOA_MODER");

    // ── Demo 5: Bitmask Builder ───────────────────────────────
    section("5. Bitmask Builder");

    struct {
        uint8_t start;
        uint8_t width;
        const char *desc;
    } masks[] = {
        {0U,  8U,  "Byte 0 mask"},
        {8U,  8U,  "Byte 1 mask"},
        {5U,  1U,  "Single bit 5"},
        {10U, 2U,  "GPIO MODER pin 5 [11:10]"},
        {0U,  12U, "12-bit ADC mask"},
        {16U, 16U, "Upper 16 bits"}
    };

    printf("\n  %-28s  Mask (Hex)    Mask (Dec)\n", "Description");
    printf("  %-28s  ──────────    ──────────\n", "───────────");
    for (uint8_t i = 0; i < 6U; i++) {
        uint32_t m = build_mask(masks[i].start, masks[i].width);
        printf("  %-28s  0x%08lX    %lu\n",
               masks[i].desc,
               (unsigned long)m,
               (unsigned long)m);
    }

    // ── Demo 6: GPIO MODER Decoder ────────────────────────────
    section("6. STM32 GPIO MODER Decoder");

    uint32_t moder_val = 0x00000000U;
    // PA0 = INPUT (default)
    // PA5 = OUTPUT
    moder_val |= (1U << (5U * 2U));
    // PA9 = ALTERNATE FUNCTION (UART TX)
    moder_val |= (2U << (9U * 2U));
    // PA10 = ALTERNATE FUNCTION (UART RX)
    moder_val |= (2U << (10U * 2U));
    // PA12 = ANALOG
    moder_val |= (3U << (12U * 2U));

    gpio_moder_decode(moder_val);

    // ── Demo 7: UART SR Decoder ───────────────────────────────
    section("7. UART Status Register Decoder");

    printf("\n  Scenario A: TX ready, RX has data:\n");
    uart_sr_decode(0xA0U);   // TXE + RXNE set

    printf("\n  Scenario B: Overrun error occurred:\n");
    uart_sr_decode(0x08U);   // ORE set

    // ── Demo 8: ADC Value Analysis ────────────────────────────
    section("8. ADC Value Analysis");

    uint16_t adc_readings[] = {0, 512, 1024, 2048, 3072, 4095};
    uint32_t vref_mv        = 3300U;
    uint8_t  adc_bits       = 12U;
    uint32_t adc_max        = (1UL << adc_bits) - 1UL;  // 4095

    printf("\n  ADC: %u-bit | Vref: %lumV\n\n",
           adc_bits, (unsigned long)vref_mv);
    printf("  %-6s  %-10s  %-12s  %s\n",
           "Raw", "Voltage", "Percent", "Bar");
    printf("  %-6s  %-10s  %-12s  %s\n",
           "─────", "─────────", "───────", "───────────────────");

    for (uint8_t i = 0; i < 6U; i++) {
        uint16_t raw     = adc_readings[i];
        uint32_t volt_mv = (uint32_t)raw * vref_mv / adc_max;
        uint8_t  pct     = (uint8_t)((uint32_t)raw * 100U / adc_max);

        printf("  %-6u  %4lumV       %3u%%          [",
               raw, (unsigned long)volt_mv, pct);
        for (uint8_t b = 0; b < 20U; b++) {
            printf(b < (pct / 5U) ? "█" : "░");
        }
        printf("]\n");
    }

    // ── Demo 9: Range Validator ───────────────────────────────
    section("9. Bit Range Validator");

    struct {
        uint32_t val;
        uint8_t  bits;
    } checks[] = {
        {255U,  8U},
        {256U,  8U},
        {4095U, 12U},
        {4096U, 12U},
        {65535U, 16U},
        {65536U, 16U}
    };

    printf("\n  %-12s  %-6s  %s\n", "Value", "Bits", "Result");
    printf("  %-12s  %-6s  %s\n", "─────────", "────", "──────");
    for (uint8_t i = 0; i < 6U; i++) {
        BitToolStatus_t r = bit_range_check(checks[i].val,
                                             checks[i].bits);
        printf("  %-12lu  %-6u  %s\n",
               (unsigned long)checks[i].val,
               checks[i].bits,
               r == BT_OK ? "✅ VALID" : "❌ OVERFLOW");
    }

    // ── Demo 10: Struct Packing ───────────────────────────────
    section("10. Sensor Data Packing into uint32_t");

    // Pack 3 sensor values into one 32-bit value for efficient UART TX
    // Format: [31:20]=temperature(12bit) [19:10]=humidity(10bit) [9:0]=pressure(10bit)
    uint16_t temperature = 2567U;   // 25.67°C (max 4095 → 12 bits)
    uint16_t humidity    = 582U;    // 58.2%   (max 1023 → 10 bits)
    uint16_t pressure    = 760U;    // 760 mmHg (max 1023 → 10 bits)

    uint32_t packed =
        ((uint32_t)(temperature & 0xFFFU) << 20U) |
        ((uint32_t)(humidity    & 0x3FFU) << 10U) |
        ((uint32_t)(pressure    & 0x3FFU));

    printf("\n  Packing sensor data into uint32_t:\n");
    printf("  Temperature : %u (12-bit field [31:20])\n", temperature);
    printf("  Humidity    : %u (10-bit field [19:10])\n", humidity);
    printf("  Pressure    : %u (10-bit field [9:0])\n\n",  pressure);
    printf("  Packed word : "); bit_tools_print_bin32_standalone(packed);
    printf("\n  Packed hex  : 0x%08lX\n\n", (unsigned long)packed);

    // Unpack and verify
    uint16_t u_temp = (uint16_t)((packed >> 20U) & 0xFFFU);
    uint16_t u_hum  = (uint16_t)((packed >> 10U) & 0x3FFU);
    uint16_t u_pres = (uint16_t)((packed)         & 0x3FFU);

    printf("  Unpacked verify:\n");
    printf("  Temperature : %u %s\n", u_temp,
           u_temp == temperature ? "✅" : "❌");
    printf("  Humidity    : %u %s\n", u_hum,
           u_hum == humidity ? "✅" : "❌");
    printf("  Pressure    : %u %s\n", u_pres,
           u_pres == pressure ? "✅" : "❌");

    printf("\n\n  ✅ Toolkit demo complete!\n\n");
    return 0;
}