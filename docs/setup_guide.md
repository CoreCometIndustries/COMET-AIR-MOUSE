# 📚 Setup & Flashing Guide

This guide provides instructions for flashing the **COMET AIR MOUSE** firmware to the ESP32-C3. You can either flash the pre-compiled `.bin` release directly using a web browser (no setup needed) or set up Arduino IDE to modify the source code.

---

## ⚡ Method 1: Browser-Based Web Flashing (Recommended)

No software installation, libraries, or Arduino IDE setup is required. All you need is a Web Serial compatible browser (Google Chrome, Microsoft Edge, or Opera) and a USB cable.

### Step-by-Step Instructions:

1. **Download Release Binary**:
   - Download the latest binary from GitHub Releases:
     - `ESP32-C3-AIR-MOUSE.ino.merged.bin` (Complete full flash image, includes bootloader + partition table + app) **OR**
     - `ESP32-C3-AIR-MOUSE.ino.bin` (Application binary)

2. **Open Web ESPTool**:
   - Navigate to [Espressif Web ESPTool](https://espressif.github.io/esptool-js/) or [Adafruit Web Serial ESPTool](https://adafruit.github.io/Adafruit_WebSerial_ESPTool/).

3. **Connect Your ESP32-C3**:
   - Connect your ESP32-C3 board to your PC via USB.
   - Click **Connect** on the website and select the USB Serial/COM port corresponding to your ESP32-C3.
   - Set baud rate to **115200** or **921600**.

4. **Select Binary File & Memory Offset**:
   - If using **`ESP32-C3-AIR-MOUSE.ino.merged.bin`**: Set address/offset to `0x0`.
   - If using **`ESP32-C3-AIR-MOUSE.ino.bin`**: Set address/offset to `0x10000`.

5. **Flash Firmware**:
   - Click **Program** or **Flash**. Wait until progress reaches 100%.
   - Press the **RESET** button on your ESP32-C3 board once flashing completes.

---

## 🛠️ Method 2: Arduino IDE & Developer Environment Setup

Use this method if you plan to edit, customize, or compile the source code.

### 1. Arduino IDE Setup
1. Download and install **Arduino IDE 2.x** from [arduino.cc](https://www.arduino.cc/en/software).
2. Open **Preferences** (`File > Preferences`).
3. Add the ESP32 Board Manager URL to **Additional Boards Manager URLs**:
   ```
   https://espressif.github.io/arduino-esp32/package_esp32_index.json
   ```
4. Go to **Tools > Board > Boards Manager**, search for `esp32` by Espressif Systems, and click **Install**.

### 2. Required Libraries
Install the following libraries in Arduino IDE (`Tools > Manage Libraries`):
1. **`MPU6050_tockn`** by **tockn** (I2C Gyro/Accelerometer parsing)
2. **`HijelHID_BLEMouse`** (BLE HID mouse interface for ESP32)

### 3. Board Configuration Settings
- **Board**: `ESP32C3 Dev Module` (or SuperMini / target variant)
- **CPU Frequency**: `160MHz (WiFi / BT)`
- **Flash Mode**: `QIO` or `DIO`
- **Flash Size**: `4MB (32Mb)`
- **Partition Scheme**: `Default 4MB with spiffs`
- **Core Debug Level**: `None` (or `Info`)
- **Upload Speed**: `921600` (or `115200`)

---

## 🔄 Calibration & Pairing Procedure

1. Connect/Power on the ESP32-C3.
2. Place the device **completely flat and still** on a surface during power-on/reset while gyro calibration occurs.
3. Open Bluetooth settings on your host device (PC, Laptop, Smartphone, Tablet).
4. Scan and pair with **`COMET AIRMOUSE`**.

