#pragma once

#include "layers.h"

enum
{
    SMART_CAPSLOCK = 0,
    SMART_NUMBERS  = 4
};

// ------ smart state -----------
bool smart_feature_state(uint8_t f);
void smart_feature_toggle(uint8_t f, uint8_t layer);
void smart_feature_disable(uint8_t f);

// ------ smart capital letters ----------
bool smart_capslock_process(uint16_t keycode, keyrecord_t* record);

// ------ smart numbers ----------
bool smart_numbers_process(uint16_t keycode, keyrecord_t* record);
