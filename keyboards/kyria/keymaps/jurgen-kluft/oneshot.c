#include "oneshot.h"

#ifdef ENABLE_ONESHOT

// the basic states a oneshot modifier can be in
typedef enum {
    UP_OFF = 0,
    DOWN_ON_TO_UP_ON,
    UP_ON,
    DOWN_ON_TO_UP_OFF,
} oneshot_state;

oneshot_state modifiers_with_state[ONESHOT_MOD_COUNT] = {
    UP_OFF, UP_OFF, UP_OFF, UP_OFF, UP_OFF, UP_OFF, UP_OFF, UP_OFF,
};

// oneshot mods always get registered immediately to the operating system, but we also
// need to keep track if the mod(s) got combined with a normal key (applied)
bool unapplied_mods_present = false;

// keycode of the last pressed 'normal' key which haven't been released yet
uint16_t repeating_normal_key = 0;

// utility functions (implemented at the bottom of this file)
void          set_modifier_state(oneshot_mod osmod, oneshot_state new_state);
void          set_modifier_state_all(oneshot_state new_state);
void          set_modifier_state_all_from_to(oneshot_state oneshot_state_from, oneshot_state oneshot_state_to);
oneshot_state get_modifier_state(oneshot_mod osmod);
bool          all_modifiers_are_off(void);

// see comment in corresponding headerfile
bool update_oneshot_modifiers(uint16_t keycode, keyrecord_t *record) {
    
    // cancel keys
    if (is_oneshot_modifier_cancel_key(keycode) && record->event.pressed) {
        unapplied_mods_present = false;
        set_modifier_state_all(UP_OFF);
        return false;
    }

    // ignored keys
    if (is_oneshot_modifier_ignored_key(keycode)) {
        return true;
    }

    oneshot_mod osmod = get_modifier_for_trigger_key(keycode);

    // trigger keys
    if (osmod != ONESHOT_NONE) {
        oneshot_state state = get_modifier_state(osmod);
        if (record->event.pressed) {
            if (state == UP_OFF) {
                set_modifier_state(osmod, DOWN_ON_TO_UP_ON);
                unapplied_mods_present = (repeating_normal_key == 0);
            } else if (state == UP_ON) {
                set_modifier_state(osmod, DOWN_ON_TO_UP_OFF);
            }
        } else {
            if (state == DOWN_ON_TO_UP_ON) {
                if (!unapplied_mods_present) {
                    set_modifier_state(osmod, UP_OFF);
                } else {
                    set_modifier_state(osmod, UP_ON);
                }
            } else if (state == DOWN_ON_TO_UP_OFF) {
                set_modifier_state(osmod, UP_OFF);
            }
        }
    }
    // normal keys
    else {
        if (record->event.pressed) {
            if (!all_modifiers_are_off()) {
                if (unapplied_mods_present) {
                    unapplied_mods_present = false;
                } else {
                    unregister_code(repeating_normal_key);
                    set_modifier_state_all_from_to(UP_ON, UP_OFF);
                }
            }
            repeating_normal_key = keycode;
        } else {
            if (!all_modifiers_are_off()) {
                unregister_code(keycode);
                set_modifier_state_all_from_to(UP_ON, UP_OFF);
            }
            repeating_normal_key = 0;
        }
    }

    return true;
}

// implementation of utility functions

// registers/unregisters a mod to the operating system on state change if necessary
void update_modifier(oneshot_mod osmod, oneshot_state previous_state, oneshot_state current_state) {
    if (previous_state == UP_OFF) {
        register_code(KC_LCTRL + osmod);
    } else {
        if (current_state == UP_OFF) {
            unregister_code(KC_LCTRL + osmod);
        }
    }
}

void set_modifier_state(oneshot_mod osmod, oneshot_state new_state) {
    oneshot_state previous_state = modifiers_with_state[osmod];
    if (previous_state != new_state) {
        modifiers_with_state[osmod] = new_state;
        update_modifier(osmod, previous_state, new_state);
    }
}

void set_modifier_state_all(oneshot_state new_state) {
    for (int8_t i = 0; i < ONESHOT_MOD_COUNT; i++) {
        oneshot_state previous_state = modifiers_with_state[i];
        if (previous_state != new_state) {
            modifiers_with_state[i] = new_state;
            update_modifier(i, previous_state, new_state);
        }
    }
}

void set_modifier_state_all_from_to(oneshot_state oneshot_state_from, oneshot_state oneshot_state_to) {
    for (int8_t i = 0; i < ONESHOT_MOD_COUNT; i++) {
        if (modifiers_with_state[i] == oneshot_state_from) {
            modifiers_with_state[i] = oneshot_state_to;
            update_modifier(i, oneshot_state_from, oneshot_state_to);
        }
    }
}

oneshot_state get_modifier_state(oneshot_mod osmod) { return modifiers_with_state[osmod]; }

bool all_modifiers_are_off() {
    for (int8_t i = 0; i < ONESHOT_MOD_COUNT; i++) {
        if (modifiers_with_state[i] != UP_OFF) {
            return false;
        }
    }
    return true;
}

#endif
