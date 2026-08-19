# 🔌 Hardware Pinout & Wiring Specifications

This document outlines the hardware setup and wiring diagram for the **COMET AIR MOUSE** project using an **ESP32-C3** development board and an **MPU6050** 6-axis IMU sensor.

---

## 📌 Pin Mapping

| ESP32-C3 Pin | Connected Component | Function Description | Hardware Notes |
|---|---|---|---|
| **GPIO 5** | MPU6050 SDA | I2C Data Line | Requires pull-up (usually on MPU6050 breakout board) |
| **GPIO 4** | MPU6050 SCL | I2C Clock Line | Requires pull-up (usually on MPU6050 breakout board) |
| **GPIO 3** | Left Tactile Switch | Left Click / Scroll Down | Active LOW, configured as `INPUT_PULLUP` |
| **GPIO 2** | Right Tactile Switch | Right Click / Scroll Up | Active LOW, configured as `INPUT_PULLUP` |
| **3.3V** | MPU6050 VCC | Power | Connect to 3.3V power rail |
| **GND** | MPU6050 GND & Switch GND | Ground | Common Ground |

---

## 🛠️ Schematic Connection Diagram


<img width="557" height="529" alt="Screenshot 2026-08-17 135605" src="https://github.com/user-attachments/assets/4b63c2fa-5861-4b36-ab4f-579083a7dd2b" />



## ⚠️ Notes on Button Logic & Debouncing

- Buttons rely on internal ESP32 pull-up resistors (`INPUT_PULLUP`). The switches should pull the pin to **GND** when pressed.
- Software thresholding:
  - **Press < 180 ms**: Triggers Mouse Click (`Left` or `Right`).
  - **Press >= 180 ms**: Enters continuous Scroll mode (`-1` or `+1`).
