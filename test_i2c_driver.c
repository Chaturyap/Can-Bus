#include "i2c_driver.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    unsigned calls;
    uint8_t address;
    uint8_t last_tx[32];
    size_t tx_len;
    size_t rx_len;
    I2C_Status result;
} FakeBus;

static I2C_Status fake_write(void *ctx, uint8_t address,
                             const uint8_t *data, size_t len)
{
    FakeBus *b = ctx;
    assert(len <= sizeof(b->last_tx));
    b->calls++;
    b->address = address;
    b->tx_len = len;
    memcpy(b->last_tx, data, len);
    return b->result;
}

static I2C_Status fake_read(void *ctx, uint8_t address,
                            uint8_t *data, size_t len)
{
    FakeBus *b = ctx;
    b->calls++;
    b->address = address;
    b->rx_len = len;
    memset(data, 0xA5, len);
    return b->result;
}

static I2C_Status fake_write_read(void *ctx, uint8_t address,
                                  const uint8_t *tx, size_t tx_len,
                                  uint8_t *rx, size_t rx_len)
{
    FakeBus *b = ctx;
    assert(tx_len <= sizeof(b->last_tx));
    b->calls++;
    b->address = address;
    b->tx_len = tx_len;
    b->rx_len = rx_len;
    memcpy(b->last_tx, tx, tx_len);
    memset(rx, 0x5A, rx_len);
    return b->result;
}

int main(void)
{
    FakeBus fake = {0};
    I2C_Port port = {&fake, fake_write, fake_read, fake_write_read};
    uint8_t tx[] = {0x01, 0x23};
    uint8_t rx[3] = {0};
    const uint8_t device = 0x42; /* Example address; not a BQ76952 claim. */

    assert(i2c_write(&port, device, tx, sizeof(tx)) == I2C_OK);
    assert(fake.calls == 1 && fake.address == device);
    assert(fake.tx_len == 2 && fake.last_tx[1] == 0x23);
    puts("PASS: write forwards address and bytes");

    assert(i2c_read(&port, device, rx, sizeof(rx)) == I2C_OK);
    assert(fake.calls == 2 && fake.rx_len == 3 && rx[0] == 0xA5);
    puts("PASS: read forwards length and fills result");

    assert(i2c_write_read(&port, device, tx, 1, rx, 2) == I2C_OK);
    assert(fake.calls == 3 && fake.tx_len == 1 && fake.rx_len == 2);
    assert(rx[0] == 0x5A);
    puts("PASS: combined write-read uses single adapter callback");

    assert(i2c_write(&port, 0x80, tx, 1) == I2C_ERR_ARGUMENT);
    assert(i2c_read(NULL, device, rx, 1) == I2C_ERR_ARGUMENT);
    assert(i2c_write(&port, device, NULL, 1) == I2C_ERR_ARGUMENT);
    assert(fake.calls == 3);
    puts("PASS: invalid arguments rejected without bus transactions");

    fake.result = I2C_ERR_NACK;
    assert(i2c_write(&port, device, tx, 1) == I2C_ERR_NACK);
    fake.result = I2C_ERR_TIMEOUT;
    assert(i2c_read(&port, device, rx, 1) == I2C_ERR_TIMEOUT);
    assert(strcmp(i2c_status_string(I2C_ERR_TIMEOUT), "timeout") == 0);
    puts("PASS: adapter errors propagated");

    port.write_read = NULL;
    assert(i2c_write_read(&port, device, tx, 1, rx, 1) == I2C_ERR_UNSUPPORTED);
    puts("PASS: unsupported repeated-start operation reported");

    puts("All 6 host mock test groups passed (no hardware involved).");
    return 0;
}
