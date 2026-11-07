# Validation plan

| ID | Test / review | Expected evidence | Status |
| --- | --- | --- | --- |
| SW-001 | Host mock: write forwards slave address + payload | `make test` | Implemented mock test |
| SW-002 | Host mock: read forwards expected byte count | `make test` | Implemented mock test |
| SW-003 | Host mock: write-then-read uses combined callback | `make test` | Implemented mock test |
| SW-004 | Host mock: invalid address rejected | `make test` | Implemented mock test |
| SW-005 | Host mock: errors propagated | `make test` | Implemented mock test |
| HW-001 | Review I2C pull-up resistors / voltage domains | Schematic review notes | Not performed |
| HW-002 | Logic-analyzer capture of I2C START/ACK/STOP | Captured waveforms | Not performed |
| HW-003 | BQ76952 response to a documented command | Real bus capture | Not performed |
| HW-004 | CAN physical interface and MCU CAN configuration | Scope/CAN analyzer capture | Not performed |
| HW-005 | PCB electrical-rule, DRC and footprint review | Saved report | Not performed |
| HW-006 | Battery-protection and safety validation | Formal test report | Not performed |

**Safety:** battery protection hardware must be independently reviewed and validated before connection to a lithium battery pack. The original PCB files are not a validated BMS.
