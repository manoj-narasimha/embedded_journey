#include <stdio.h>
#include <stdint.h>

// ── Simulated driver with proper NULL checking ─────────────────
typedef struct {
    uint16_t raw;
    uint16_t voltage_mv;
    uint8_t  valid;
} AdcResult_t;

typedef enum {
    ADC_OK      = 0,
    ADC_ERROR   = 1,
    ADC_NULL    = 2
} AdcStatus_t;

// Simulate ADC hardware read
static AdcStatus_t adc_read(AdcResult_t *out) {
    // Always check NULL first
    if (out == NULL) {
        printf("[ADC] ERROR: NULL pointer passed!\n");
        return ADC_NULL;
    }

    // Simulate hardware read
    out->raw        = 2048U;
    out->voltage_mv = (uint16_t)((uint32_t)out->raw * 3300U / 4095U);
    out->valid      = 1U;

    return ADC_OK;
}

// Return pointer from function — common pattern
static uint8_t s_tx_buffer[64] = {0};

uint8_t *get_tx_buffer(void) {
    return s_tx_buffer;    // return pointer to static buffer
}

uint8_t *get_null_buffer(void) {
    return NULL;           // simulate failure
}

int main(void) {
    printf("=== NULL Pointer Safety ===\n\n");

    // ── Case 1: Safe usage
    printf("--- Case 1: Correct usage ---\n");
    AdcResult_t result = {0};
    AdcStatus_t status = adc_read(&result);
    if (status == ADC_OK) {
        printf("ADC: raw=%u  voltage=%u mV\n",
               result.raw, result.voltage_mv);
    }

    // ── Case 2: NULL passed — driver handles it gracefully
    printf("\n--- Case 2: NULL passed to driver ---\n");
    status = adc_read(NULL);
    printf("Status: %s\n",
           status == ADC_NULL ? "ADC_NULL (handled safely)" : "other");

    // ── Case 3: Pointer returned from function
    printf("\n--- Case 3: Pointer from function ---\n");
    uint8_t *buf = get_tx_buffer();
    if (buf != NULL) {
        buf[0] = 0xAAU;
        buf[1] = 0xBBU;
        printf("buf[0]=0x%02X  buf[1]=0x%02X\n", buf[0], buf[1]);
    }

    // ── Case 4: NULL returned from function — safe handling
    printf("\n--- Case 4: NULL returned — safe handling ---\n");
    uint8_t *bad_buf = get_null_buffer();
    if (bad_buf == NULL) {
        printf("Buffer unavailable — skipping operation safely\n");
    } else {
        bad_buf[0] = 0xFF;   // only reached if not NULL
    }

    // ── Case 5: Pointer to struct member
    printf("\n--- Case 5: Pointer to struct member ---\n");
    AdcResult_t readings[3] = {{1000U, 0U, 0U},
                                {2000U, 0U, 0U},
                                {3000U, 0U, 0U}};

    for (uint8_t i = 0U; i < 3U; i++) {
        uint16_t *raw_ptr = &readings[i].raw;
        readings[i].voltage_mv =
            (uint16_t)((uint32_t)(*raw_ptr) * 3300U / 4095U);
        printf("Reading[%u]: raw=%u  voltage=%u mV\n",
               i, readings[i].raw, readings[i].voltage_mv);
    }

    return 0;
}