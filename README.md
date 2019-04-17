# LedDriver

[![Build Status](https://travis-ci.org/kokabe2/LedDriver.svg?branch=master)](https://travis-ci.org/kokabe2/LedDriver)

A LED driver for embedded systems.

## Features

- Multiple-instance module
- Written in C
- Testability
- MIT license

## Assumptions and constraints

- The implementation of LEDs is memory-mapped I/O and 8 bits
- The I/O address is writable and readable
- The bit value 1 is LED on and 0 is LED off
- Dynamic memory allocation

## Usage

I recommend just copying LedDriver.h and LedDriver.c into your project.
Then just #include "LedDriver.h" to use the LedDriver functions.

## Function Documentation

### LedDriver_Create

```C
LedDriver LedDriver_Create(uint8_t* ioAddress, uint8_t (*decoder)(int));
```

Create a LedDriver instance.

Note: All LEDs will be off if successfully.

Inputs:

- `ioAddress` - The I/O address for LEDs.
- `decoder` - The function to convert to bit from the LED number (1 to 8).

Returns the instance if created successfully, NULL if an error occurred.

### LedDriver_Destroy

```C
void LedDriver_Destroy(LedDriver* self);
```

Destroy a LedDriver instance.

Note: All LEDs will be off if successfully.

Inputs:

- `self` - The pointer to LedDriver instance.

### LedDriver_TurnOn

```C
void LedDriver_TurnOn(LedDriver self, int ledNumber);
```

Turn on a LED.

Inputs:

- `self` - The LedDriver instance.
- `ledNumber` - The number of LED to turn on.

### LedDriver_TurnOff

```C
void LedDriver_TurnOff(LedDriver self, int ledNumber);
```

Turn off a LED.

Inputs:

- `self` - The LedDriver instance.
- `ledNumber` - The number of LED to turn off.

### LedDriver_TurnAllOn

```C
void LedDriver_TurnAllOn(LedDriver self);
```

Turn on all LEDs.

Inputs:

- `self` - The LedDriver instance.

### LedDriver_TurnAllOff

```C
void LedDriver_TurnAllOff(LedDriver self);
```

Turn off all LEDs.

Inputs:

- `self` - The LedDriver instance.

### LedDriver_IsOn

```C
bool LedDriver_IsOn(LedDriver self, int ledNumber);
```

Check if the LED is on.

Inputs:

- `self` - The LedDriver instance.
- `ledNumber` - The number of LED to check.

### LedDriver_IsOff

```C
bool LedDriver_IsOff(LedDriver self, int ledNumber);
```

Check if the LED is off.

Inputs:

- `self` - The LedDriver instance.
- `ledNumber` - The number of LED to check.

## How to use this project

### Build

```bash
$ cd LedDriver
$ mkdir build
$ cd build
$ cmake ..
$ make
```

### Run the tests

Either using `ctest` or directly using `bin/gtests` in the build directory.
