# Project README

This README provides an overview of the Autonomous Car project. 🚗💡🤖

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Hardware Requirements](#hardware-requirements)
- [Usage](#usage)
- [Installation](#installation)
- [Contributing](#contributing)
- [License](#license)
- [Acknowledgments](#acknowledgments)
- [Contact](#contact)

## Introduction

Welcome to the final version of the Autonomous Car project! This project focuses on developing an autonomous car that detects light and avoids obstacles. The car is implemented using FreeRTOS and incorporates various components such as the Tiva C tm4c123gh6pm microcontroller, 2 LDR sensors, an ultrasonic sensor, 4 DC motors, a character LCD, and 2 push buttons.

## Features

- Light Detection: The car uses the 2 LDR sensors to detect light intensity and identify areas with higher light. It adjusts its direction towards brighter areas. 💡☀️

- Obstacle Avoidance: The ultrasonic sensor is used to detect obstacles in the car's path. The car makes real-time decisions to avoid collisions. 🛑🚧

- User Interaction: The car includes 2 push buttons for user interaction. The "Start" button initiates the car's movement, and the "Stop" button halts its operation. The character LCD displays relevant information. 🆒🖥️

- Temperature Monitoring: The car measures and displays the ambient temperature using the internal temperature sensor of the microcontroller. 🌡️

- Light Difference Measurement: The car calculates and displays the difference between the readings of the 2 LDR sensors. ➖🔆🔅

- Stopwatch Timer: The car includes a stopwatch timer that starts when the "Start" button is pressed and stops when the "Stop" button is pressed or after a minute of continuous operation. ⏱️

## Hardware Requirements

To run this project, you will need the following components:

- Tiva C tm4c123gh6pm microcontroller
- Ultrasonic sensor
- Character LCD
- 2 LDR sensors
- 2 push buttons
- 4 DC motors

## Usage

1. Press the "Start" button to initiate the car's movement.
2. The car will start moving forward until it detects a difference in light intensity using the LDR sensors.
3. Upon detecting higher light intensity, the car will adjust its direction to move towards the brighter area.
4. Simultaneously, the ultrasonic sensor will scan for obstacles, and the car will make necessary adjustments to avoid collisions.
5. The character LCD will display real-time information, including the ambient temperature, light difference between the LDR sensors, and the stopwatch timer indicating the elapsed time since the car started moving.
6. Press the "Stop" button to halt the car's operation or wait for one minute of continuous operation for it to automatically stop.

## Installation

1. Ensure that the Tiva C tm4c123gh6pm microcontroller is properly connected to the necessary components, including the LDR sensors, ultrasonic sensor, DC motors, character LCD, and push buttons.
2. Install the FreeRTOS framework on the microcontroller.
3. Compile and upload the project code to the microcontroller using an appropriate development environment or IDE.
4. Power on the autonomous car and verify that all components are functioning correctly.

## Contributing

Contributions to enhance the functionality and performance of the autonomous car project are welcome. To contribute, please follow the standard practices of forking the repository, making changes, and submitting a pull request.

## License

This project is licensed under the [MIT License](LICENSE). Feel free to modify and distribute the codebase following the terms of the license.

## Acknowledgments

We would like to express our gratitude to the contributors and developers of FreeRTOS for providing a robust framework for real-time operating systems. Additionally, we appreciate the support and guidance from our mentors and advisors throughout the development process.

## Contact

For any further inquiries or questions, please contact the project team at kkaremmohamed13@gmail.com 📧
