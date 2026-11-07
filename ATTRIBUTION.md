# Source and attribution

## Source of original electronic-design files

- Project: `BMS-Can-Bus`
- Original repository: https://github.com/hasanberkdasar/BMS-Can-Bus
- Original author and copyright holder: **Hasan Berk Daşar**
- License: **MIT**; complete original text is preserved in `/LICENSE`.

The files below are taken directly from the supplied upstream ZIP without modification:

- `/BMS-Can-Bus.kicad_sch`
- `/BMS-Can-Bus.kicad_pcb`
- `/BMS-Can-Bus.kicad_pro`
- `/fp-lib-table`
- `/LICENSE`

## New additions in this repository package

- A restructured README explaining provenance, limitations and workflow.
- `docs/assets/*.svg`: new conceptual block graphics, not renders of the KiCad PCB.
- `firmware/i2c_driver.*`: a new generic C I2C transport-layer starter.
- `tests/test_i2c_driver.c`, `Makefile`, and GitHub Actions unit-test workflow.
- Integration, validation, and contribution templates.

**Do not remove the original LICENSE, claim the original board is your own design, or describe hardware test results that do not exist.**
