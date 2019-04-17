#include "LedDriver.h"

#include <stddef.h>
#include <stdlib.h>
#include "RuntimeError.h"


enum {
    kFirstLed = 1,
    kLastLed = 8,
};

struct LedDriverStruct {
    uint8_t* ioAddress;
    uint8_t (*decoder)(int);
};


static bool Validate(uint8_t* ioAddress, uint8_t (*decoder)(int))
{
    if (!ioAddress)
        RUNTINE_ERROR("LED Driver: null I/O address", 0);
    else if (!decoder)
        RUNTINE_ERROR("LED Driver: null decode function", 0);
    else
        return true;

    return false;
}

static LedDriver NewInstance(uint8_t* ioAddress, uint8_t (*decoder)(int))
{
    LedDriver self = calloc(1, sizeof(struct LedDriverStruct));
    if (!self) return NULL;

    self->ioAddress = ioAddress;
    self->decoder = decoder;

    return self;
}

LedDriver LedDriver_Create(uint8_t* ioAddress, uint8_t (*decoder)(int))
{
    if (!Validate(ioAddress, decoder)) return NULL;

    LedDriver self = NewInstance(ioAddress, decoder);
    if (self) LedDriver_TurnAllOff(self);

    return self;
}

static void DeleteInstance(LedDriver* self)
{
    free(*self);
    *self = NULL;
}

void LedDriver_Destroy(LedDriver* self)
{
    if (!self || !*self) return;

    LedDriver_TurnAllOff(*self);
    DeleteInstance(self);
}

static bool IsInvalid(LedDriver self)
{
    if (self) return false;

    RUNTINE_ERROR("LED Driver: null instance", 0);
    return true;
}

static bool IsLedOutOfBounds(int ledNumber)
{
    if (ledNumber >= kFirstLed && ledNumber <= kLastLed) return false;

    RUNTINE_ERROR("LED Driver: out-of-bounds LED", ledNumber);
    return true;
}

static void SetLedImageBit(LedDriver self, int ledNumber)
{
    *self->ioAddress |= self->decoder(ledNumber);
}

void LedDriver_TurnOn(LedDriver self, int ledNumber)
{
    if (IsInvalid(self) || IsLedOutOfBounds(ledNumber)) return;

    SetLedImageBit(self, ledNumber);
}

static void ClearLedImageBit(LedDriver self, int ledNumber)
{
    *self->ioAddress &= ~self->decoder(ledNumber);
}

void LedDriver_TurnOff(LedDriver self, int ledNumber)
{
    if (IsInvalid(self) || IsLedOutOfBounds(ledNumber)) return;

    ClearLedImageBit(self, ledNumber);
}

static void SetAllLedImageBits(LedDriver self)
{
    for (int i = kFirstLed; i <= kLastLed; i++)
        *self->ioAddress |= self->decoder(i);
}

void LedDriver_TurnAllOn(LedDriver self)
{
    if (IsInvalid(self)) return;

    SetAllLedImageBits(self);
}

static void ClearAllLedImageBits(LedDriver self)
{
    for (int i = kFirstLed; i <= kLastLed; i++)
        *self->ioAddress &= ~self->decoder(i);
}

void LedDriver_TurnAllOff(LedDriver self)
{
    if (IsInvalid(self)) return;

    ClearAllLedImageBits(self);
}

static bool IsLedImageBitOn(LedDriver self, int ledNumber)
{
    return *self->ioAddress & self->decoder(ledNumber);
}

bool LedDriver_IsOn(LedDriver self, int ledNumber)
{
    if (IsInvalid(self) || IsLedOutOfBounds(ledNumber)) return false;

    return IsLedImageBitOn(self, ledNumber);
}

bool LedDriver_IsOff(LedDriver self, int ledNumber)
{
    return !LedDriver_IsOn(self, ledNumber);
}
