#include "i2c_driver.h"

static int valid_address(uint8_t address7)
{
    return address7 <= 0x7F;
}

I2C_Status i2c_write(const I2C_Port *port, uint8_t address7,
                     const uint8_t *data, size_t len)
{
    if (!port || !valid_address(address7) || !data || !len)
        return I2C_ERR_ARGUMENT;
    if (!port->write)
        return I2C_ERR_UNSUPPORTED;
    return port->write(port->ctx, address7, data, len);
}

I2C_Status i2c_read(const I2C_Port *port, uint8_t address7,
                    uint8_t *data, size_t len)
{
    if (!port || !valid_address(address7) || !data || !len)
        return I2C_ERR_ARGUMENT;
    if (!port->read)
        return I2C_ERR_UNSUPPORTED;
    return port->read(port->ctx, address7, data, len);
}

I2C_Status i2c_write_read(const I2C_Port *port, uint8_t address7,
                          const uint8_t *tx, size_t tx_len,
                          uint8_t *rx, size_t rx_len)
{
    if (!port || !valid_address(address7) || !tx || !tx_len || !rx || !rx_len)
        return I2C_ERR_ARGUMENT;
    if (!port->write_read)
        return I2C_ERR_UNSUPPORTED;
    return port->write_read(port->ctx, address7, tx, tx_len, rx, rx_len);
}

const char *i2c_status_string(I2C_Status status)
{
    switch (status) {
    case I2C_OK: return "OK";
    case I2C_ERR_ARGUMENT: return "invalid argument";
    case I2C_ERR_UNSUPPORTED: return "operation unsupported";
    case I2C_ERR_NACK: return "NACK";
    case I2C_ERR_TIMEOUT: return "timeout";
    case I2C_ERR_IO: return "I/O error";
    default: return "unknown error";
    }
}
