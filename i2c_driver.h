#ifndef I2C_DRIVER_H
#define I2C_DRIVER_H

#include <stddef.h>
#include <stdint.h>

/* Generic 7-bit I2C transport; no MCU HAL or BQ76952 framing built in. */
typedef enum {
    I2C_OK = 0,
    I2C_ERR_ARGUMENT = -1,
    I2C_ERR_UNSUPPORTED = -2,
    I2C_ERR_NACK = -3,
    I2C_ERR_TIMEOUT = -4,
    I2C_ERR_IO = -5
} I2C_Status;

typedef I2C_Status (*I2C_WriteFn)(void *ctx, uint8_t address7,
                                   const uint8_t *data, size_t len);
typedef I2C_Status (*I2C_ReadFn)(void *ctx, uint8_t address7,
                                  uint8_t *data, size_t len);
typedef I2C_Status (*I2C_WriteReadFn)(void *ctx, uint8_t address7,
                                       const uint8_t *tx, size_t tx_len,
                                       uint8_t *rx, size_t rx_len);

typedef struct {
    void *ctx;
    I2C_WriteFn write;
    I2C_ReadFn read;
    /* Adapter must use a combined transaction if repeated START is required. */
    I2C_WriteReadFn write_read;
} I2C_Port;

I2C_Status i2c_write(const I2C_Port *port, uint8_t address7,
                     const uint8_t *data, size_t len);
I2C_Status i2c_read(const I2C_Port *port, uint8_t address7,
                    uint8_t *data, size_t len);
I2C_Status i2c_write_read(const I2C_Port *port, uint8_t address7,
                          const uint8_t *tx, size_t tx_len,
                          uint8_t *rx, size_t rx_len);
const char *i2c_status_string(I2C_Status status);

#endif
