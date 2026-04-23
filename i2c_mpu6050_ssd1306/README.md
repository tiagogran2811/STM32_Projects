# STM32 + MPU6050 + SSD1306 (I2C)

This project implements acquisition and visualization of motion data using an **MPU6050 IMU** and an **SSD1306 OLED display**, both connected via **I2C** to an STM32F411 (Black Pill).

---

## Overview

The system reads raw accelerometer and gyroscope data, converts them into physical units, estimates orientation (roll and pitch), and displays everything on an OLED screen.

---

## Features

* I2C communication with multiple devices (MPU6050 + SSD1306)
* Raw sensor acquisition:

  * Acceleration (Ax, Ay, Az)
  * Angular velocity (Gx, Gy, Gz)
* Unit conversion:

  * g (acceleration)
  * °/s (angular velocity)
* Angle estimation:

  * Roll and Pitch using a complementary filter

---

## Angle Estimation

Accelerometer-based angles:

* Roll = atan2(Ay, Az)
* Pitch = atan2(-Ax, sqrt(Ay² + Az²))

Complementary filter:

```
angle = α * (angle + gyro * dt) + (1 - α) * accel
```

---

## Hardware

* STM32F411 (Black Pill)
* MPU6050 (Accelerometer + Gyroscope)
* SSD1306 OLED (I2C)

---

## Configuration

* I2C running at 400 kHz (Fast Mode)
* MPU6050:

  * Accelerometer: ±2g
  * Gyroscope: ±250°/s

---

## Notes

* Yaw is not calculated (no magnetometer)
* Complementary filter coefficient (α) can be tuned
* Loop delay affects responsiveness

---

## Possible Improvements

* Implement Kalman filter
* Add magnetometer (MPU9250)
* Use interrupts or DMA instead of polling
* Improve OLED UI

---

## Author

Developed for embedded systems practice using STM32CubeIDE.
