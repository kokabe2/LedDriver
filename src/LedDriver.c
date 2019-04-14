#include "LedDriver.h"

#include <stddef.h>
#include "RuntimeError.h"


enum {
    kFirstLed = 1,
    kLastLed = 8,
};

struct LedDriverStruct {
    bool isUsed;
    uint8_t* ioAddress;
    uint8_t bitmask;
};


static struct LedDriverStruct instance = {false, NULL, 0};


static bool Validate(uint8_t* ioAddress, uint8_t bitmask)
{
    if (!ioAddress)
        RUNTINE_ERROR("LED Driver: null I/O address", 0);
    else if (!bitmask)
        RUNTINE_ERROR("LED Driver: no LEDs available", 0);
    else
        return true;

    return false;
}

static LedDriver NewInstance(uint8_t* ioAddress, uint8_t bitmask)
{
    if (instance.isUsed) return NULL;

    instance.isUsed = true;
    instance.ioAddress = ioAddress;
    instance.bitmask = bitmask;

    return &instance;
}

LedDriver LedDriver_Create(uint8_t* ioAddress, uint8_t bitmask)
{
    if (!Validate(ioAddress, bitmask)) return NULL;

    LedDriver self = NewInstance(ioAddress, bitmask);
    if (self) LedDriver_TurnAllOff(self);

    return self;
}

static void DeleteInstance(LedDriver* self)
{
    (*self)->isUsed = false;
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

static uint8_t ConvertToBit(int ledNumber) { return 1 << ledNumber - 1; }

static bool IsLedUnavailable(LedDriver self, int ledNumber)
{
    if (self->bitmask & ConvertToBit(ledNumber)) return false;

    RUNTINE_ERROR("LED Driver: unavailable LED number", ledNumber);
    return true;
}

static void SetLedImageBit(LedDriver self, int ledNumber)
{
    *self->ioAddress |= ConvertToBit(ledNumber);
}

void LedDriver_TurnOn(LedDriver self, int ledNumber)
{
    if (IsInvalid(self) || IsLedOutOfBounds(ledNumber)
        || IsLedUnavailable(self, ledNumber))
        return;

    SetLedImageBit(self, ledNumber);
}

static void ClearLedImageBit(LedDriver self, int ledNumber)
{
    *self->ioAddress &= ~ConvertToBit(ledNumber);
}

void LedDriver_TurnOff(LedDriver self, int ledNumber)
{
    if (IsInvalid(self) || IsLedOutOfBounds(ledNumber)
        || IsLedUnavailable(self, ledNumber))
        return;

    ClearLedImageBit(self, ledNumber);
}

static void SetAllLedImageBits(LedDriver self)
{
    *self->ioAddress |= self->bitmask;
}

void LedDriver_TurnAllOn(LedDriver self)
{
    if (IsInvalid(self)) return;

    SetAllLedImageBits(self);
}

static void ClearAllLedImageBits(LedDriver self)
{
    *self->ioAddress &= ~self->bitmask;
}

void LedDriver_TurnAllOff(LedDriver self)
{
    if (IsInvalid(self)) return;

    ClearAllLedImageBits(self);
}

static bool IsLedImageBitOn(LedDriver self, int ledNumber)
{
    return *self->ioAddress & ConvertToBit(ledNumber);
}

bool LedDriver_IsOn(LedDriver self, int ledNumber)
{
    if (IsInvalid(self) || IsLedOutOfBounds(ledNumber)
        || IsLedUnavailable(self, ledNumber))
        return false;

    return IsLedImageBitOn(self, ledNumber);
}

bool LedDriver_IsOff(LedDriver self, int ledNumber)
{
    return !LedDriver_IsOn(self, ledNumber);
}
