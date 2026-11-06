# STM32 BMS — I2C Driver & CAN Hardware Reference

![Project banner](docs/assets/banner.svg)

> **Project stage:** KiCad hardware reference + portable I2C driver starter and host-mock unit tests. **No claim of a fabricated board, hardware validation, or completed BQ76952 firmware integration.**

A technical learning/development workspace centered on an STM32F103-based 4-series battery-management PCB with a BQ76952 battery-monitoring IC and a CAN physical interface. It pairs an **existing open-source KiCad reference design** with a new, **portable I2C transaction-layer example**, an automated mock-test harness, and a documentation workflow for extending and validating the project yourself.

![System block diagram](docs/assets/architecture.svg)

## What is here

| Area | Contents | Status |
| --- | --- | --- |
| `BMS-Can-Bus.kicad_sch` | Schematic from the upstream BMS project | Upstream reference, unchanged |
| `BMS-Can-Bus.kicad_pcb` | PCB layout from the upstream BMS project | Upstream reference, unchanged |
| `BMS-Can-Bus.kicad_pro` | KiCad project settings | Upstream reference, unchanged |
| `firmware/` | Platform-independent I2C transfer wrapper | Starter code; **not hardware-tested** |
| `tests/` | Host-side fake I2C port and unit tests | Runnable on a computer |
| `docs/assets/` | Original repository graphics and conceptual diagrams | Illustrative; not PCB renders |
| `docs/` | Attribution, integration notes and test plan | Working documentation |

## Architecture

- **Battery monitoring:** the upstream schematic uses the **TI BQ76952** battery monitor / protector.
- **Host MCU:** STM32F103 microcontroller, intended to communicate with the monitor by **I2C/SMBus**.
- **External interface:** the upstream design includes an **SN65HVD230 CAN transceiver** for the CAN physical layer. The CAN transceiver is not a UART interface, and this repository does not implement CAN firmware.
- **Power hardware:** upstream KiCad PCB; no independent verification of its current rating or safety has been performed here.

![I2C transaction concept](docs/assets/i2c-transaction.svg)

## Quick start: view the PCB

1. Download or clone the repository.
2. Open `BMS-Can-Bus.kicad_pro` with a compatible version of KiCad (the included board is saved by KiCad 10).
3. Review the schematic and layout as **reference design files**, not a manufacturing-ready verified PCB.
4. If KiCad warns about a missing `Library.pretty`, see [Known limitations](#known-limitations).

## Quick start: run the I2C unit tests

Prerequisite: `gcc` and `make` (or a C11-capable compiler).

```bash
make test
```

Alternatively:

```bash
cc -std=c11 -Wall -Wextra -Werror -pedantic -Ifirmware \
  firmware/i2c_driver.c tests/test_i2c_driver.c -o i2c_tests
./i2c_tests
```

These tests use fake callbacks and **do not communicate with physical I2C peripherals**. More detail is in [`docs/I2C_INTEGRATION.md`](docs/I2C_INTEGRATION.md).

## Firmware scope

The `i2c_driver` API supports:

- 7-bit slave-address validation;
- write transactions, read transactions, and combined write-then-read transactions (for adapters supporting repeated START);
- error propagation and explicit callback checks;
- transport-agnostic integration with STM32 HAL or a different MCU driver.

It does **not** implement complete BQ76952 command framing, data memory access, checksum, alert handling, CAN telemetry, STM32 startup code, or a production battery-protection algorithm. Those require device-specific datasheet work and hardware validation.

## Evidence and contribution tracking

If you are using this for a project portfolio or DreamStream reporting, record **only activities you actually completed**. Use [`docs/MY_CONTRIBUTIONS.md`](docs/MY_CONTRIBUTIONS.md) to log your changes, actual work dates, commits, test output, and review notes. Git commit timestamps cannot legitimately be backdated to imply earlier project activity.

## Known limitations

- **Unfabricated / untested reference:** the upstream design describes the PCB as not physically fabricated or hardware-tested. No safety or current-handling capability should be inferred from these files.
- **Referenced footprint library:** `fp-lib-table` points to `Library.pretty`, which was **not included** in the original archive. Footprint-resolution warnings may occur until the correct custom library is recovered.
- **Unverified board:** verify electrical connectivity, pin assignments, protection circuits, current limits, thermal design, isolation, and all footprints before considering fabrication. Lithium battery packs can be hazardous; do not connect a live pack using an unreviewed design.
- **Firmware starter:** the included portable I2C layer is suitable for learning and adapter testing, not proof of successful BQ76952 communication.

## Original design, licensing and attribution

The KiCad schematic, PCB layout, project settings and `fp-lib-table` were copied **unchanged** from the MIT-licensed open-source project **BMS-Can-Bus** by **Hasan Berk Daşar**. Original source: https://github.com/hasanberkdasar/BMS-Can-Bus . The original MIT `LICENSE` is preserved at the repository root. Read [`docs/ATTRIBUTION.md`](docs/ATTRIBUTION.md) for the file-level breakdown.

The additional README, SVG illustrations, firmware starter and test harness in this package were newly assembled as an extension to the reference. Review, adapt, run, and document your actual modifications before representing any portion as your own completed engineering contribution.
