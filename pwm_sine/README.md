# Sine PWM Generation - STM32

This project implements sine wave generation using PWM on an STM32 microcontroller, based on a Direct Digital Synthesis (DDS) approach.

## Overview

A sine waveform is approximated by updating the PWM duty cycle using a lookup table (LUT).
The update is performed inside a timer interrupt at a fixed rate.

The output frequency can be controlled in real-time via UART.

---

## How It Works

* A **sine lookup table (LUT)** stores precomputed samples
* A **timer interrupt (TIM3)** updates the PWM duty cycle
* A **step variable** controls how fast the LUT is traversed
* The **output frequency** is adjusted by modifying this step via UART

---

##  Required Hardware

* STM32 microcontroller (tested on Black Pill STM32f411CEU6)
* USB to TTL converter (for UART communication)
* Oscilloscope (recommended for visualization)
* RC low-pass filter (to smooth PWM into analog signal)

---

## Software & Tools

* STM32CubeIDE
* HAL drivers
* C language

---

## Peripheral Configuration

### Timer (TIM3 - PWM + Interrupt)

* Mode: PWM Generation (Channel 1)
* Counter Mode: Upcounting
* Prescaler: configured to achieve ~32 kHz update rate
* Auto-reload (ARR): defines PWM resolution (e.g., 1000)
* Interrupt: **Enabled (Update Event)**

### PWM Output

* Channel: TIM3 Channel 1
* Duty cycle updated dynamically from LUT
* Output pin configured as Alternate Function Push-Pull

---

### UART (USART1)

* Mode: Asynchronous
* Baudrate: 115200
* Word Length: 8 bits
* Stop Bits: 1
* Parity: None
* Interrupt: **Enabled (Receive IT mode)**

---

## How to Use

### 1. Build and Flash

* Open project in STM32CubeIDE
* Build and flash to your board

### 2. RC Low-Pass Filter Design

To convert the PWM signal into a smooth analog sine wave, use a simple RC low-pass filter.

A good rule of thumb is to set the cutoff frequency about 100 times lower than the PWM frequency.

Example configuration:

* Resistor: 1 kΩ
* Capacitor: 500 nF

Cutoff frequency:

```
Fc = 1 / (2πRC) ≈ 320 Hz
```

This filter attenuates the high-frequency PWM components while preserving the sine waveform.

Connect the filter as:

* PWM output → Resistor → Output node
* Capacitor from output node to GND

For better smoothing, you can cascade multiple RC stages.

---

### 2. Connect UART

Use a serial terminal such as:

* PuTTY
* Tera Term
* Arduino Serial Monitor

---

### 3. Send Frequency

Send a number via UART (in Hz), followed by Enter:

Example:

```bash
50
```

### Frequency Limits

* Minimum: 20 Hz
* Maximum: 200 Hz

---

## Output Signal

* The PWM signal represents a sine waveform
* To obtain a smooth analog signal:

  * Use a **low-pass RC filter**
* Higher PWM frequency improves waveform quality

---

## Important Notes

- The update frequency (`F_UPDATE`) is fixed at 32 kHz
- The output frequency is calculated as:

`f_out = (step × F_UPDATE) / LUT_SIZE`

### Explanation

The timer updates the PWM at a fixed rate (`F_UPDATE`).

At each update, the LUT index increases by `step`.

#### Step 1 — Steps per second

In one second, the index advances by:

`steps_per_second = step × F_UPDATE`

#### Step 2 — Steps per cycle

To complete one full sine wave, the LUT must be fully traversed:

`steps_per_cycle = LUT_SIZE`

#### Step 3 — Frequency definition

Frequency is the number of cycles per second:

`f_out = steps_per_second / steps_per_cycle`

#### Step 4 — Substitute values

Replacing the expressions:

`f_out = (step × F_UPDATE) / LUT_SIZE`

### Intuition

- Larger `step` → faster traversal → higher frequency  
- Smaller `step` → slower traversal → lower frequency  

---

## Possible Improvements

* Add DAC output (instead of PWM)
* Implement DMA for LUT updates
* Add display or GUI control

---

## License

This project is open-source under the MIT License.
