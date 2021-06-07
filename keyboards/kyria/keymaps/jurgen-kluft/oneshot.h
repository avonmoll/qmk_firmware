#pragma once
#include QMK_KEYBOARD_H

#define ENABLE_ONESHOT

#ifdef ENABLE_ONESHOT

// This enables a feature where you can put a modifier in a 'hold' state and where
// it will only be deactivated when pressing a oneshot cancel key.
#define ENABLE_ONESHOT_HOLD

// Represents the four states a oneshot key can be in
typedef enum
{
    os_up_unqueued = 0x00,
    os_up_queued   = 0x01,
    os_down_unused = 0x02,
    os_down_used   = 0x04,
    os_state_mask  = 0x0F,
#ifdef ENABLE_ONESHOT_HOLD
    os_mode_none   = 0x00,
    os_mode_hold   = 0x80,
    os_mode_mask   = 0x80,
#endif
} oneshot_state;

// Custom oneshot mod implementation that doesn't rely on timers. If a mod is
// used while it is held it will be unregistered on keyup as normal, otherwise
// it will be queued and only released after the next non-mod keyup.
void update_oneshot(oneshot_state* state, uint16_t mod, uint16_t trigger, uint16_t keycode, keyrecord_t* record);

// To be implemented by the consumer. Defines keys to cancel oneshot mods.
bool is_oneshot_cancel_key(uint16_t keycode);

// To be implemented by the consumer. Defines keys to ignore when determining
// whether a oneshot mod has been used. Setting this to modifiers and layer
// change keys allows stacking multiple oneshot modifiers, and carrying them
// between layers.
bool is_oneshot_ignored_key(uint16_t keycode);

#endif