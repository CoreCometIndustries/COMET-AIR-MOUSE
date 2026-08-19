# 🖱️ COMET AIR MOUSE (ESP32-C3 BLE HID)

Motion-controlled wireless Bluetooth Low Energy (BLE) HID Air Mouse powered by the **ESP32-C3** microcontroller and **MPU6050** 6-axis Gyroscope/Accelerometer.

---

## ✨ Features

- **Bluetooth LE HID Mouse**: Acts as a native Bluetooth mouse; no additional software/drivers needed on host PC or mobile device.
- **Gyroscope Motion Tracking**: Smooth 2D cursor control with adjustable exponential smoothing and deadzone filtering.
- **Button Controls**:
  - **Left Button**: Short press = Left Click | Long press (>= 180ms) = Scroll Down
  - **Right Button**: Short press = Right Click | Long press (>= 180ms) = Scroll Up
- **Automatic Gyro Calibration**: Calibrates gyro offsets on boot for drift-free precision tracking.
- **Power & Bluetooth Management**: Movement signals are suspended until BLE connection is paired.

---

## 📁 Repository Layout

```
firmware/
├── .gitignore                          # Git ignore rules for build binaries and IDE outputs
├── README.md                           # Main repository documentation
├── LICENSE                             # MIT Open Source License
├── src/                                # Main source code directory
│   └── ESP32-C3-AIR-MOUSE/
│       └── ESP32-C3-AIR-MOUSE.ino      # ESP32-C3 Air Mouse Arduino sketch
├── hardware/                           # Hardware pinout & schematic specifications
│   └── pinout.md
├── docs/                               # Setup & developer documentation
│   └── setup_guide.md
└── .github/                            # GitHub configuration & issue templates
    └── ISSUE_TEMPLATE/
        ├── bug_report.md
        └── feature_request.md
```

---

## 🔌 Hardware Pinout

| Component | Pin / Function | ESP32-C3 GPIO | Note |
|---|---|---|---|
| **MPU6050** | SDA | **GPIO 5** | I2C Data Line |
| **MPU6050** | SCL | **GPIO 4** | I2C Clock Line |
| **MPU6050** | VCC / GND | 3.3V / GND | Power Supply |
| **Left Button** | Click / Scroll Down | **GPIO 3** | Internal Pull-Up (`INPUT_PULLUP`) |
| **Right Button** | Click / Scroll Up | **GPIO 2** | Internal Pull-Up (`INPUT_PULLUP`) |

---
##  Connection 
<img width="557" height="529" alt="Screenshot 2026-08-17 135605" src="https://github.com/user-attachments/assets/ab82ead3-3bf2-4b7f-87ec-4d62b1134e70" />

## 🚀 Getting Started

### ⚡ Option 1: Quick Web Flashing (Recommended - No IDE or Libraries Required)

You do **not** need to install Arduino IDE, board cores, or libraries if you just want to use the Air Mouse. You can flash the pre-compiled firmware directly from your browser:

1. **Download `.bin` File**: Get the latest release `.bin` file (e.g. `ESP32-C3-AIR-MOUSE.bin`) from the GitHub Releases page.
2. **Open Web ESPTool**: Open an esptool web flasher in a Web Serial supported browser (Chrome, Edge, Opera):
   - [Espressif Web ESPTool](https://espressif.github.io/esptool-js/) or [Adafruit Web Serial ESPTool](https://adafruit.github.io/Adafruit_WebSerial_ESPTool/)
3. **Connect Board**: Plug your ESP32-C3 into USB, set baud rate to `115200` or `921600`, click **Connect**, and select your device's COM/Serial port.
4. **Flash Firmware**:
   - For **binary** (`.bin`): Add file at offset `0x0000`.
   - Click **Program / Flash**.
5. **Pair & Use**: Reset the board, place it flat on a desk during boot for auto gyro calibration, then pair **`COMET AIRMOUSE`** under host Bluetooth settings!

---

### 💻 Option 2: Compiling & Flashing from Source (For Developers)

If you want to modify the source code or build manually:

1. **Required Libraries**:
   - **Wire** (Built-in ESP32 core)
   - **MPU6050_tockn** (Install via Arduino Library Manager)
   - **HijelHID_BLEMouse** (BLE HID library for ESP32)
2. **Clone & Open**:
   ```bash
   git clone https://github.com/your-username/firmware.git
   cd firmware
   ```
   Open `src/ESP32-C3-AIR-MOUSE/ESP32-C3-AIR-MOUSE.ino` in **Arduino IDE**.
3. **Select Board**: Select **ESP32C3 Dev Module** under `Tools > Board > esp32`.
4. **Compile & Upload**: Upload to your ESP32-C3 board via Arduino IDE.


---

## ⚙️ Configuration & Tuning

Key variables inside [`ESP32-C3-AIR-MOUSE.ino`](src/ESP32-C3-AIR-MOUSE/ESP32-C3-AIR-MOUSE.ino):

```cpp
float smoothing   = 0.82; // Gyro filter factor (0.0 to 1.0)
float sensitivity = 0.20; // Cursor movement multiplier
int   deadzone    = 1;    // Minimum movement threshold to suppress jitter
```

---

## 📄 License

This project is licensed under the [MIT License](LICENSE).
