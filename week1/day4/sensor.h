#ifndef SENSOR_H
#define SENSOR_H

#include <stdint.h>

// ── Constants ─────────────────────────────────────────────────
#define SENSOR_ID_TEMP  (0x01U)
#define SENSOR_ID_HUM   (0x02U)
#define SENSOR_I2C_ADDR (0x76U)   // BME280 default I2C address

// ── Types ─────────────────────────────────────────────────────
typedef enum {
    SENSOR_OK      = 0,
    SENSOR_ERROR   = 1,
    SENSOR_TIMEOUT = 2
} SensorStatus_t;

typedef struct {
    uint8_t  sensor_id;
    uint16_t temperature_x100;    // 2540 = 25.40°C
    uint16_t humidity_x100;       // 6000 = 60.00%
    uint32_t pressure_x100;       // 101325 = 1013.25 hPa
    uint32_t timestamp_ms;
    uint8_t  valid;
} SensorData_t;

// ── Function Declarations ─────────────────────────────────────
SensorStatus_t sensor_init  (uint8_t i2c_address);
SensorStatus_t sensor_read  (SensorData_t *out);
void           sensor_print (const SensorData_t *data);

#endif // SENSOR_H