/*
 * =========================================================
 * COMET AIR MOUSE
 * ESP32-C3 | MPU6050 | BLE HID
 * =========================================================
 *
 * Motion-controlled wireless mouse using the MPU6050.
 *
 * Features:
 * - BLE HID mouse
 * - Gyroscope cursor control
 * - Left / Right click
 * - Scroll control
 * - Adjustable sensitivity & smoothing
 *
 * Pinout:
 * MPU6050 SDA  -> GPIO 5
 * MPU6050 SCL  -> GPIO 4
 * Left Button  -> GPIO 3
 * Right Button -> GPIO 2
 *
 * Motion:
 * Gyro Z -> Mouse X (inverted)
 * Gyro Y -> Mouse Y
 *
 * Device: COMET AIRMOUSE
 * =========================================================
 */
#include <Wire.h>
#include <MPU6050_tockn.h>
#include <HijelHID_BLEMouse.h>

HijelBLEMouse mouse(
  "COMET AIRMOUSE",
  "COMET",
  100,
  5,
  true
);

// MPU6050
MPU6050 mpu6050(Wire);

// ESP32-C3 I2C
#define SDA_PIN 5
#define SCL_PIN 4

// BUTTONS
#define LEFT_BUTTON  3
#define RIGHT_BUTTON 2

// MOUSE SETTINGS
float smoothing   = 0.82;
float sensitivity = 0.20;

int deadzone = 1;

// BUTTON SETTINGS
unsigned long leftPressStart  = 0;
unsigned long rightPressStart = 0;

bool leftHeld  = false;
bool rightHeld = false;

const unsigned long clickThreshold = 180;

// SCROLL
unsigned long lastScrollTime = 0;
const unsigned long scrollDelay = 120;

// GYRO
float gyroBiasZ = 0;
float gyroBiasY = 0;

float fX = 0;
float fY = 0;

// =====================================================
// CALIBRATE GYRO
// =====================================================

void calibrateGyro() {

  Serial.println();
  Serial.println("========================================");
  Serial.println("Calibrating gyro");
  Serial.println("Keep Air Mouse completely still!");
  Serial.println("========================================");

  float sumZ = 0;
  float sumY = 0;

  const int samples = 500;

  for (int i = 0; i < samples; i++) {

    mpu6050.update();

    sumZ += mpu6050.getGyroZ();
    sumY += mpu6050.getGyroY();

    delay(3);
  }

  gyroBiasZ = sumZ / samples;
  gyroBiasY = sumY / samples;

  Serial.println("Gyro calibration complete");

  Serial.print("Bias Z: ");
  Serial.println(gyroBiasZ, 2);

  Serial.print("Bias Y: ");
  Serial.println(gyroBiasY, 2);

  Serial.println();
}

// =====================================================
// SETUP
// =====================================================

void setup() {

  Serial.begin(115200);

  delay(1000);

  Serial.println();
  Serial.println("========================================");
  Serial.println("       COMET AIR MOUSE");
  Serial.println("       ESP32-C3 BLE HID");
  Serial.println("========================================");

  // ---------------------------------------------------
  // I2C
  // ---------------------------------------------------

  Wire.begin(SDA_PIN, SCL_PIN);

  Wire.setClock(400000);

  delay(100);

  // ---------------------------------------------------
  // MPU6050
  // ---------------------------------------------------

  Serial.println("Initializing MPU6050...");

  mpu6050.begin();

  Serial.println("MPU6050 OK");

  // Let MPU6050_tockn calculate offsets
  Serial.println();
  Serial.println("Calculating MPU6050 offsets...");
  Serial.println("DO NOT MOVE THE AIR MOUSE!");

  mpu6050.calcGyroOffsets(true);

  Serial.println("MPU6050 offsets complete");

  // ---------------------------------------------------
  // BUTTONS
  // ---------------------------------------------------

  pinMode(LEFT_BUTTON, INPUT_PULLUP);
  pinMode(RIGHT_BUTTON, INPUT_PULLUP);

  // ---------------------------------------------------
  // OUR ADDITIONAL GYRO CALIBRATION
  // ---------------------------------------------------

  delay(1000);

  calibrateGyro();

  // ---------------------------------------------------
  // BLE HID
  // ---------------------------------------------------

  Serial.println();
  Serial.println("Starting BLE HID Mouse...");

  // Just Works is the library default.
  // No PIN/passkey required.

  mouse.setUpdateRate(HIDRate::Hz125);

  mouse.setBatteryLevel(100);

  mouse.setLogLevel(HIDLogLevel::Normal);

  mouse.begin();

  Serial.println("BLE mouse started");

  Serial.println();
  Serial.println("========================================");
  Serial.println("Bluetooth name:");
  Serial.println("COMET AIRMOUSE");
  Serial.println();
  Serial.println("Waiting for connection...");
  Serial.println("========================================");
}

// =====================================================
// LOOP
// =====================================================

void loop() {

  // ---------------------------------------------------
  // UPDATE MPU6050
  // ---------------------------------------------------

  mpu6050.update();

  // ---------------------------------------------------
  // BLE STATUS
  // ---------------------------------------------------

  static bool previousPaired = false;

  bool paired = mouse.isPaired();

  if (paired != previousPaired) {

    if (paired) {

      Serial.println();
      Serial.println("********************************");
      Serial.println("BLE MOUSE CONNECTED!");
      Serial.println("********************************");

    } else {

      Serial.println();
      Serial.println("BLE mouse disconnected");
    }

    previousPaired = paired;
  }

  // ---------------------------------------------------
  // BUTTON PROCESSING
  // ---------------------------------------------------

  unsigned long now = millis();

  // ===================================================
  // LEFT BUTTON
  // Short = LEFT CLICK
  // Long  = SCROLL DOWN
  // ===================================================

  if (digitalRead(LEFT_BUTTON) == LOW) {

    if (leftPressStart == 0) {

      leftPressStart = now;
      leftHeld = false;
    }

    if (!leftHeld &&
        now - leftPressStart >= clickThreshold) {

      leftHeld = true;
    }

    if (leftHeld &&
        paired &&
        now - lastScrollTime >= scrollDelay) {

      mouse.addScroll(-1);

      lastScrollTime = now;
    }
  }

  else {

    if (leftPressStart != 0) {

      if (!leftHeld &&
          now - leftPressStart < clickThreshold &&
          paired) {

        mouse.click(
          MouseButton::Left,
          20
        );
      }

      leftPressStart = 0;
      leftHeld = false;
    }
  }

  // ===================================================
  // RIGHT BUTTON
  // Short = RIGHT CLICK
  // Long  = SCROLL UP
  // ===================================================

  if (digitalRead(RIGHT_BUTTON) == LOW) {

    if (rightPressStart == 0) {

      rightPressStart = now;
      rightHeld = false;
    }

    if (!rightHeld &&
        now - rightPressStart >= clickThreshold) {

      rightHeld = true;
    }

    if (rightHeld &&
        paired &&
        now - lastScrollTime >= scrollDelay) {

      mouse.addScroll(1);

      lastScrollTime = now;
    }
  }

  else {

    if (rightPressStart != 0) {

      if (!rightHeld &&
          now - rightPressStart < clickThreshold &&
          paired) {

        mouse.click(
          MouseButton::Right,
          20
        );
      }

      rightPressStart = 0;
      rightHeld = false;
    }
  }

  // ---------------------------------------------------
  // DO NOT PROCESS GYRO UNTIL PAIRED
  // ---------------------------------------------------

  if (!paired) {

    delay(5);

    return;
  }

  // ===================================================
  // GYRO MOUSE
  // ===================================================

  float gyroX = -(mpu6050.getGyroZ() - gyroBiasZ);

  float gyroY =
    mpu6050.getGyroY() - gyroBiasY;

  // ---------------------------------------------------
  // SMOOTHING
  // ---------------------------------------------------

  fX =
    fX * smoothing +
    gyroX * (1.0 - smoothing);

  fY =
    fY * smoothing +
    gyroY * (1.0 - smoothing);

  // ---------------------------------------------------
  // SENSITIVITY
  // ---------------------------------------------------

  float moveX =
    fX * sensitivity;

  float moveY =
    fY * sensitivity;

  // ---------------------------------------------------
  // DEADZONE
  // ---------------------------------------------------

  if (fabs(moveX) < deadzone) {

    moveX = 0;
  }

  if (fabs(moveY) < deadzone) {

    moveY = 0;
  }

  // ---------------------------------------------------
  // DIAGONAL BOOST
  // ---------------------------------------------------

  if (moveX != 0 &&
      moveY != 0) {

    const float factor = 1.12;

    moveX *= factor;
    moveY *= factor;
  }

  // ---------------------------------------------------
  // SEND BLE MOVEMENT
  // ---------------------------------------------------

  int mouseX = (int)moveX;
  int mouseY = (int)moveY;

  if (mouseX != 0 ||
      mouseY != 0) {

    mouse.move(mouseX, mouseY);
  }

  delay(5);
}
