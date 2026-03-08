#include "sensor.h"
#include <stdio.h>

// ── Private state ──────────────────────────────────────────────
static uint8_t s_i2c_address = 0U;
static uint8_t s_initialized  = 0U;

// Simulated tick counter (real firmware uses SysTick)
static uint32_t s_tick_ms = 0U;

// ── Private helpers ────────────────────────────────────────────
static uint32_t get_tick_ms(void) {
    s_tick_ms += 100U;    // simulate 100ms passing each read
    return s_tick_ms;
}

// Simulate reading raw ADC values from BME280 over I2C
static uint16_t read_raw_temperature(void) { return 2567U; }  // 25.67°C
static uint16_t read_raw_humidity(void)    { return 5823U; }  // 58.23%
static uint32_t read_raw_pressure(void)    { return 101325U;} // 1013.25 hPa

// ── Public functions ───────────────────────────────────────────
SensorStatus_t sensor_init(uint8_t i2c_address) {
    s_i2c_address = i2c_address;
    s_initialized  = 1U;
    printf("[SENSOR] Init OK — I2C addr: 0x%02X\n", s_i2c_address);
    return SENSOR_OK;
}

SensorStatus_t sensor_read(SensorData_t *out) {
    if (out == NULL)       return SENSOR_ERROR;
    if (!s_initialized)    return SENSOR_ERROR;

    out->sensor_id        = SENSOR_ID_TEMP;
    out->temperature_x100 = read_raw_temperature();
    out->humidity_x100    = read_raw_humidity();
    out->pressure_x100    = read_raw_pressure();
    out->timestamp_ms     = get_tick_ms();
    out->valid            = 1U;

    return SENSOR_OK;
}

void sensor_print(const SensorData_t *data) {
    if (data == NULL || !data->valid) {
        printf("[SENSOR] Invalid data\n");
        return;
    }
    printf("[SENSOR] ── Reading @ %lums ─────────────────\n",
           (unsigned long)data->timestamp_ms);
    printf("[SENSOR] Temperature : %u.%02u °C\n",
           data->temperature_x100 / 100U,
           data->temperature_x100 % 100U);
    printf("[SENSOR] Humidity    : %u.%02u %%\n",
           data->humidity_x100 / 100U,
           data->humidity_x100 % 100U);
    printf("[SENSOR] Pressure    : %lu.%02lu hPa\n",
           (unsigned long)(data->pressure_x100 / 100U),
           (unsigned long)(data->pressure_x100 % 100U));
    printf("[SENSOR] ─────────────────────────────────────\n");
}