
# AS1170 Evaluation Kit Interface

This repository contains the source code and GUI application for interfacing with the **AS1170 Evaluation Kit** using an **ESP32 microcontroller** and a **Python-based GUI**. The project demonstrates I2C communication, PWM control, and register manipulation for the AS1170 device.

## 📦 Contents

- `ESP32/`: Arduino source code for the ESP32-S2 DevKit M1.
- `AS1170_GUI.exe`: Executable GUI application for Windows.
- `docs/`: User guides and documentation.

---

## 🚀 Getting Started

### ESP32 Firmware

#### Requirements

- ESP32-S2 DevKit M1
- Arduino IDE (v2.0.17 or compatible)
- USB to UART driver (CP210x from Silicon Labs)
- Required libraries:
  - `Wire.h`
  - `SD.h`
  - `HardwareSerial.h`
  - `Arduino.h`
  - `driver/ledc.h`

#### Setup Instructions

1. **Install USB Driver**: [CP210x VCP Drivers – Silicon Labs](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers)
2. **Configure Arduino IDE**:
   - Add ESP32 board URL:  
     `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
   - Install **ESP32 by Espressif Systems** (version 2.0.17)
   - Select board: `ESP32S2 Dev Module`
3. **Connect Hardware**:
   - SDA (GPIO 14), SCL (GPIO 15), PWM (GPIO 5)
   - Connect AS1170 EVK and required pull-up/down resistors
4. **Upload Code** and open Serial Monitor (baud rate: 115200)

---

### GUI Application

#### Requirements

- Windows OS
- AS1170 hardware connected via USB
- `AS1170_GUI.exe` executable

#### Launch Instructions

1. Connect the AS1170 hardware to your PC.
2. Ensure the USB to UART driver is installed.
3. Run `AS1170_GUI.exe`.

#### Features

- Real-time register monitoring and control
- PWM and current configuration
- Fault and status indicators
- Serial communication with ESP32
- Interactive GUI with toolbars, status bar, and configuration panels

---

## 🧠 Architecture Overview

### ESP32 Firmware

- I2C communication with AS1170
- PWM signal generation
- Serial command interface
- Register read/write logic

### GUI Application

- Built with PyQt
- Serial communication via Silicon Labs port
- Modular design:
  - `Controller`: Manages app lifecycle
  - `ClientView`: Main interactive window
  - `commands.py`: Serial command interface

---

## 🛠 Commands

The GUI communicates with the ESP32 using serial commands:

- `read`: Read register values
- `write`: Write to a register
- `reset`: Reset all registers
- `strobePWM`: Trigger PWM output

---

## 📄 Documentation

- [AS1170 ESP32 Guide](docs/AS1170%20ESP32.docx)
- [AS1170 GUI User Guide](docs/AS1170%20GUI%20UserGuide.docx)

---

## 🧾 License

© ams-OSRAM AG. All rights reserved.  
This project is provided for evaluation purposes only. See documentation for legal disclaimers.
