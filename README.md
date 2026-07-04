# Sentinel: Smart Home Security and Monitoring System
A hardware/software Arduino project that combines RFID-based access control, gas and flame detection, and an automated garage door into one integrated smart home security system.

## Overview
Sentinel enhances home security and automation using RFID technology, sensors, and servo motors. The system:

- Unlocks the front door with an authorized RFID card
- Sounds alarms and lights LEDs on unauthorized access attempts
- Opens/closes the garage door with a single push button
- Detects gas leaks and fires and raises an immediate audible/visual alarm

## How It Works

### RFID Door Lock
- On power-up, the LCD displays `Welcome! Put your card.`
- When a card is scanned, the LCD shows `Scanning...`
- **Correct card:** LCD shows `Unlocked`, the servo motor rotates the door latch from 0° to 90°, the buzzer beeps briefly, and the green LED lights up.
- **Incorrect card:** LCD shows `Wrong card!`, the door stays locked, the red LED turns on, and the buzzer sounds a warning pattern.
- **Locking:** Scanning the authorized card again shows `Locked`, and the servo returns to 0°.

### Smart Garage Door
- Press the push button once to open the garage door (servo moves 90° → 0°).
- Press it again to close the door (servo moves 0° → 90°).

### Safety Monitoring
- **Gas sensor (MQ5):** If gas is detected, the buzzer sounds and the blue LED lights up.
- **Flame sensor:** If a flame is detected, the buzzer sounds and the red LED lights up.

## Repository Structure

```
.
├── Codes/
│   ├── gas.fire.garage/
│   │   └── gas.fire.garage.ino        # Gas/flame detection + garage door control
│   └── project.lcd.rfid/
│       └── project.lcd.rfid.ino       # RFID door lock + LCD interface
├── Connection Images/                  # Wiring diagrams and circuit photos
├── material used.docx                  # Full bill of materials
├── Smart-Home.docx                     # Project write-up
└── README.md
```

## Hardware Components

**Electrical**
- 2x Servo motors (door latch + garage door)
- 4x LEDs — 2 Red, 1 Green, 1 Blue
- RFID reader (MFRC522) with RFID card/tag
- 1x Push button
- 5x Resistors — 4x 330Ω, 1x 1KΩ
- 1x LCD 16x2 I2C display
- 1x Flame sensor
- 1x Gas sensor (MQ5)

**Home Model / Enclosure**
- Foam boards (x2), wooden dowels, paper, sliding bolt lock, 2x door hinges

**Software**
- Arduino IDE

## Required Arduino Libraries
Install these via the Arduino IDE Library Manager before uploading the sketches:

- `Servo`
- `LiquidCrystal_I2C`
- `SPI` (built-in)
- `MFRC522`

## Setup

1. Wire the components as shown in the diagrams under `Connection Images/`.
2. Open `Codes/project.lcd.rfid/project.lcd.rfid.ino` in the Arduino IDE, update the `UID` variable with your own RFID card's UID, and upload it to the board handling the door lock.
3. Open `Codes/gas.fire.garage/gas.fire.garage.ino` and upload it to the board handling the garage door and gas/flame safety monitoring.
4. Power the system and scan your card at the reader to test the door lock; trigger the gas/flame sensors to test the alarm system.

## Author
Mohammad Murra