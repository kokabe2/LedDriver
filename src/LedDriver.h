#pragma once

#include <stdbool.h>
#include <stdint.h>


typedef struct LedDriverStruct* LedDriver;

LedDriver LedDriver_Create(uint8_t* ioAddress, uint8_t bitmask);
void LedDriver_Destroy(LedDriver* self);
void LedDriver_TurnOn(LedDriver self, int ledNumber);
void LedDriver_TurnOff(LedDriver self, int ledNumber);
void LedDriver_TurnAllOn(LedDriver self);
void LedDriver_TurnAllOff(LedDriver self);
bool LedDriver_IsOn(LedDriver self, int ledNumber);
bool LedDriver_IsOff(LedDriver self, int ledNumber);
