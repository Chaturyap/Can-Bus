# I2C integration notes — STM32 + BQ76952

## Purpose

The `firmware/i2c_driver.h` and `.c` files define a **generic transport interface**, not a complete device driver for a battery monitor.

The caller must supply an `I2C_Port` with device-specific low-level callbacks. A future STM32 HAL adapter may map `write`, `read`, and `write_read` to the relevant MCU HAL calls; pay special attention to **repeated START** behavior and to address representation.

## Addressing

- This API accepts a **7-bit I2C address** (`0x00`–`0x7F`).
- Some STM32 HAL functions expect the address shifted left by one bit. Perform that conversion **only inside the HAL adapter**, if the HAL requires it.
- Obtain the device address from actual pin configuration, datasheet, and a bus scan—not from guesses in example code.

## Example (pseudocode)

```c
#include "i2c_driver.h"

// supply HAL-backed callbacks here:
I2C_Port port = {
    .ctx = /* device-specific context */ NULL,
    .write = /* your_write */ NULL,
    .read = /* your_read */ NULL,
    .write_read = /* your_write_read */ NULL,
};

// Set callbacks to real functions before using the port.
// i2c_write_read(&port, address7, &cmd, 1, bytes, 2);
```

## Important BQ76952-specific gaps

The BQ76952 uses command/data structures that are **not always equivalent to reading a plain register with an 8-bit address**. Before adding a BQ-specific layer, use the relevant Texas Instruments technical reference manual for correct commands, byte ordering, supported I2C transactions, alert behavior, data-memory access, and CRC/checksum configuration. Avoid copying a simple generic register-read helper and assuming it works for all BQ76952 commands.

## Suggested next implementation steps

1. Verify MCU-to-monitor I2C pin and pull-up connections in KiCad.
2. Create an STM32 HAL adapter with correct repeated-START semantics.
3. Create a BQ76952 command layer per the device documentation.
4. Confirm basic communication on bench using a **properly reviewed, safely powered** setup.
5. Add tests for NACKs, timeouts, interrupted transfers and recovery.
6. Capture real traces and link them in `MY_CONTRIBUTIONS.md`.
