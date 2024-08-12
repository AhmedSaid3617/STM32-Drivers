# STM32 Microcontroller Drivers

This repository contains a collection of drivers for the STM32 family of microcontrollers. These drivers are designed to interface with various peripherals and features of the STM32 series, making it easier to develop embedded applications.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Supported STM32 Series](#supported-stm32-series)
- [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Introduction

STM32 microcontrollers are widely used in embedded systems due to their flexibility and performance. This repository provides a set of drivers that facilitate communication with different peripherals, including GPIO, UART, SPI, I2C, ADC, and more.

The drivers are written in C and are designed to be lightweight and efficient, suitable for both hobbyist projects and professional applications.

## Features

- **Modular Design:** Each driver is independent, allowing you to include only the drivers you need.
- **Low-Level Abstraction:** Direct access to hardware registers for maximum control.
- **Easy Integration:** Simple API for quick and easy integration into your projects.
- **Documentation:** Detailed comments and usage examples for each driver.

## Internal Peripherals
- [GPIO](./drivers/src/gpio.c)
- [EXTI](./drivers/src/exti.c)
- [NVIC](./drivers/src/gpio.c)
- [SysTick](./drivers/src/systick.c)

## External Peripherals
External peripherals are external modules that should be connected to your STM32 as specified in the docs or comments in the respective dirver source files.
- [Keypad](./drivers/src/keypad.c)

## Usage

Each driver is located in its respective directory within the `src` folder. To use a driver, include the header file in your source code:

```c
#include "gpio.h"
#include "keypad.h"
```

## License

This project is licensed under the MIT License - see the [LICENSE](./LICENSE.md) file for details.

