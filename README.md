# STM32 Projects

This repository contains a collection of embedded systems projects developed using STM32 microcontrollers and STM32CubeIDE. The goal is to document learning progress, experiments, and implementations of key concepts in embedded programming.

## Project Structure

Each folder represents an individual project focused on a specific topic:

```
STM32_projects/
 ├── sine_pwm/        # Sine wave generation using PWM
 ├── uart/            # UART communication examples
 ├── adc/             # Analog-to-Digital Conversion experiments
 ├── timers/          # Timer configurations and applications
 └── ...              # (these files are just used as examples)
```

## Objectives

* Practice embedded systems development with STM32
* Explore peripherals such as PWM, ADC, UART, and Timers
* Implement signal processing techniques (e.g., sine wave generation)
* Build a solid foundation for real-world embedded applications

## Tools & Technologies

* STM32 Microcontrollers (e.g., STM32F103, Black Pill)
* STM32CubeIDE
* HAL (Hardware Abstraction Layer)
* C Programming Language

## Highlights

* **Sine PWM (DDS)**: Generates a sine wave using a lookup table and PWM modulation
* **UART Communication**: Serial communication with a PC for data exchange and control
  
## How to Use

1. Clone the repository:

   ```bash
   git clone <https://github.com/tiagogran2811/STM32_Projects.git>
   ```

2. Open STM32CubeIDE

3. Import a project:

   ```
   File > Import > Existing Projects into Workspace
   ```

4. Select the desired project folder

5. Build and flash to your STM32 board

## Notes

* Make sure the correct board and clock configurations are set for your hardware
* Some projects may require external components (filters, sensors, etc.)

## Future Improvements

* Add documentation for each project
* Include schematics and circuit diagrams
* Improve code modularity and reuse
* Add real-time control via UART or other interfaces

## Contributions

This repository is mainly for personal learning, but suggestions and improvements are always welcome.

## License

This project is open-source and available under the MIT License.
