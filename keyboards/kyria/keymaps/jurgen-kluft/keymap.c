#include QMK_KEYBOARD_H
#include "oled.h"
#include "smart.h"
#include "oneshot.h"
#include "layers.h"

#define KC_VBAR LSFT(KC_BSLASH)

#define KC_MAC_UNDO LGUI(KC_Z)
#define KC_MAC_REDO LGUI(LSFT(KC_Z))
#define KC_MAC_CUT LGUI(KC_X)
#define KC_MAC_COPY LGUI(KC_C)
#define KC_MAC_PASTE LGUI(KC_V)
#define KC_PC_UNDO LCTL(KC_Z)
#define KC_PC_REDO LCTL(LSFT(KC_Z))
#define KC_PC_CUT LCTL(KC_X)
#define KC_PC_COPY LCTL(KC_C)
#define KC_PC_PASTE LCTL(KC_V)

#define OS_MAC

#ifdef OS_MAC
#    define KC_UNDO KC_MAC_UNDO
#    define KC_REDO KC_MAC_REDO
#    define KC_CUT KC_MAC_CUT
#    define KC_COPY KC_MAC_COPY
#    define KC_PASTE KC_MAC_PASTE
#    define KC_TRANS KC_TRANSPARENT
#    define KC_NDT C(KC_RIGHT)
#    define KC_PDT C(KC_LEFT)
#    define KC_CLOSE LGUI(KC_W)
#    define KC_SAVE LGUI(KC_S)
#else
#    define KC_UNDO KC_PC_UNDO
#    define KC_REDO KC_PC_REDO
#    define KC_CUT KC_PC_CUT
#    define KC_COPY KC_PC_COPY
#    define KC_PASTE KC_PC_PASTE
#    define KC_TRANS KC_TRANSPARENT
#    define KC_NDT LCTL(LGUI(KC_RIGHT))
#    define KC_PDT LCTL(LGUI(KC_LEFT))
#    define KC_CLOSE LCTL(KC_W)
#    define KC_SAVE LCTL(KC_S)
#endif

#define KC_DQUOTE LSFT(KC_QUOTE)
#define KC_LBRACE LSFT(KC_9)
#define KC_RBRACE LSFT(KC_0)
#define KC_LCBRACE LSFT(KC_LBRACKET)
#define KC_RCBRACE LSFT(KC_RBRACKET)

#define LA_SYM MO(_SYM)
#define LA_NAV MO(_NAV)
#define LA_FNC MO(_FNC)
#define LT_MOS TG(_MOUS)

enum custom_keycodes {
    KC_QWERTY = SAFE_RANGE,
    KC_RSTHD,
    KC_OLED,
    OS_SHFT,
    OS_CTRL,
    OS_ALT,
    OS_CMD,
    KC_SMART_CAPSLOCK,
    KC_SMART_NUMBER,
    UC_SHRG,  // ¯\_(ツ)_/¯
    UC_DISA,  // ಠ_ಠ
    UC_LVIT,  // ♥‿♥
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    //#                         ╭───────╮                                                                        ╭───────╮                          
    //#                 ╭───────╯   E   ╰───────╮                                                        ╭───────╯   I   ╰───────╮                  
    //#                 │   W   │       │   R   ╭───────╮                                        ╭───────╮   U   │       │   O   │                  
    //# ╭───────╮───────╯       ╰───────╯       │   T   │                                        │   Y   │       ╰───────╯       ╰───────╭───────╮  
    //# │       │   Q   ╰───────╯   D   ╰───────╯       │                                        │       ╰───────╯   K   ╰───────╯   P   │       │  
    //# │       │       │   S   │       │   F   ╰───────╯                                        ╰───────╯   J   │       │   L   │       │       │  
    //# ╰───────╯───────╯       ╰───────╯       │   G   │                                        │   H   │       ╰───────╯       ╰───────╰───────╯  
    //# │       │   A   ╰───────╯   C   ╰───────╯       │                                        │       ╰───────╯   ,   ╰───────╯   ;   │       │  
    //# │       │       │   X   │       │   V   ╰───────╯                                        ╰───────╯   M   │       │   .   │       │       │  
    //# ╰───────╯───────╯       ╰───────╯       │   B   │ ╭───────╮                    ╭───────╮ │   N   │       ╰───────╯       ╰───────╰───────╯  
    //# │       │   Z   ╰───────╯       ╰───────╯       │ │       ╰───────╮    ╭───────╯       │ │       ╰───────╯       ╰───────╯   /   │ RSTHD │  
    //# │       │       │              ╭───────╮╰───────╯ │       │       │    │       │       │ ╰───────╯╭───────╮              │       │       │  
    //# ╰───────╯───────╯     ╭───────╮│       ╰───────╮  ╰───────╯       │    │       ╰───────╯  ╭───────╯ A_FNC │╭───────╮     ╰───────╰───────╯  
    //#                       │ T_MOS ││       │ A_NAV ╰───────╮  ╰───────╯    ╰───────╯  ╭───────╯ A_SYM │       ││ T_MOS │                        
    //#                       │       │╰───────╯       │ SPACE ╰───────╮          ╭───────╯   ⌫   │       ╰───────╯│       │                        
    //#                       ╰encodr─╯        ╰───────╯       │   ⌫   │          │       │       ╰───────╯        ╰encodr─╯                        
    //#                                                ╰───────╯       │          │       ╰───────╯                                                 
    //#                                                        ╰───────╯          ╰───────╯                                                         
  [_QWERTY] = LAYOUT(
    KC_TRANS, KC_Q, KC_W, KC_E,   KC_R,     KC_T,                                               KC_Y,   KC_U,   KC_I,     KC_O,   KC_P,     KC_TRANS, 
    KC_TRANS, KC_A, KC_S, KC_D,   KC_F,     KC_G,                                               KC_H,   KC_J,   KC_K,     KC_L,   KC_SCLN,  KC_TRANS, 
    KC_TRANS, KC_Z, KC_X, KC_C,   KC_V,     KC_B,   KC_TRANS, KC_TRANS,    KC_TRANS, KC_TRANS,  KC_N,   KC_M,   KC_COMMA, KC_DOT, KC_SLASH, KC_RSTHD, 
                          LT_MOS, KC_TRANS, LA_NAV, KC_SPACE, KC_BSPACE,   KC_TRANS, KC_BSPACE, LA_SYM, LA_FNC, LT_MOS                                
  ),
  [_RSTHD] = LAYOUT(
    KC_TRANS, KC_J,    KC_C, KC_Y,   KC_F,     KC_K,                                              KC_Z,   KC_L,   KC_BSPACE, KC_U,   KC_Q,    KC_TRANS,  
    KC_TRANS, KC_R,    KC_S, KC_T,   KC_H,     KC_D,                                              KC_M,   KC_N,   KC_A,      KC_I,   KC_O,    KC_TRANS,  
    KC_TRANS, KC_SCLN, KC_V, KC_G,   KC_P,     KC_B,   KC_TRANS, KC_TRANS,    KC_TRANS, KC_TRANS, KC_X,   KC_W,   KC_COMMA,  KC_DOT, KC_SCLN, KC_QWERTY, 
                             LT_MOS, KC_TRANS, LA_NAV, KC_SPACE, KC_BSPACE,   KC_TRANS, KC_E,     LA_SYM, LA_FNC, LT_MOS                                 
  ),
  [_QWERTY_CAPS] = LAYOUT(
    KC_TRANS, LSFT(KC_Q), LSFT(KC_W), LSFT(KC_E), LSFT(KC_R), LSFT(KC_T),                                           LSFT(KC_Y), LSFT(KC_U), LSFT(KC_I), LSFT(KC_O), LSFT(KC_P), KC_TRANS, 
    KC_TRANS, LSFT(KC_A), LSFT(KC_S), LSFT(KC_D), LSFT(KC_F), LSFT(KC_G),                                           LSFT(KC_H), LSFT(KC_J), LSFT(KC_K), LSFT(KC_L), KC_UNDS,    KC_TRANS, 
    KC_TRANS, LSFT(KC_Z), LSFT(KC_X), LSFT(KC_C), LSFT(KC_V), LSFT(KC_B), KC_TRANS, KC_TRANS,   KC_TRANS, KC_TRANS, LSFT(KC_N), LSFT(KC_M), KC_COMMA,   KC_DOT,     KC_AT,      KC_TRANS, 
                                      KC_TRANS,   KC_TRANS,   KC_TRANS,   KC_TRANS, KC_TRANS,   KC_TRANS, KC_TRANS, KC_TRANS,   KC_TRANS,   KC_TRANS                                      
  ),
  [_RSTHD_CAPS] = LAYOUT(
    KC_TRANS, LSFT(KC_J), LSFT(KC_C), LSFT(KC_Y), LSFT(KC_F), LSFT(KC_K),                                             LSFT(KC_Z), LSFT(KC_L), KC_BSPACE,  LSFT(KC_U), LSFT(KC_Q), KC_TRANS, 
    KC_TRANS, LSFT(KC_R), LSFT(KC_S), LSFT(KC_T), LSFT(KC_H), LSFT(KC_D),                                             LSFT(KC_M), LSFT(KC_N), LSFT(KC_A), LSFT(KC_I), LSFT(KC_O), KC_TRANS, 
    KC_TRANS, KC_UNDS,    LSFT(KC_V), LSFT(KC_G), LSFT(KC_P), LSFT(KC_B), KC_TRANS, KC_TRANS,   KC_TRANS, KC_TRANS,   LSFT(KC_X), LSFT(KC_W), KC_COMMA,   KC_DOT,     KC_AT,      KC_TRANS, 
                                      KC_TRANS,   KC_TRANS,   KC_TRANS,   KC_TRANS, KC_TRANS,   KC_TRANS, LSFT(KC_E), KC_TRANS,   KC_TRANS,   KC_TRANS                                      
  ),
  [_SMART_NUM] = LAYOUT(
    KC_TRANS, KC_TRANS, KC_TRANS, KC_LBRACKET, KC_RBRACKET, KC_SLASH,                                           KC_MINUS, KC_LPRN,  KC_RPRN,  KC_TRANS, KC_TRANS, KC_TRANS, 
    KC_TRANS, KC_5,     KC_6,     KC_7,        KC_8,        KC_ASTR,                                            KC_PLUS,  KC_1,     KC_2,     KC_3,     KC_4,     KC_TRANS, 
    KC_TRANS, KC_TRANS, KC_TRANS, KC_TRANS,    KC_9,        KC_EQUAL, KC_TRANS, KC_TRANS,   KC_TRANS, KC_TRANS, KC_EQUAL, KC_0,     KC_COMMA, KC_DOT,   KC_TRANS, KC_TRANS, 
                                  KC_TRANS,    KC_TRANS,    KC_TRANS, KC_TRANS, KC_TRANS,   KC_TRANS, KC_TRANS, KC_TRANS, KC_TRANS, KC_TRANS                                
  ),
  // Symbols in order of frequency # | & { } , ? [ ] _ < > $ % ` ' / - 0 : \ 1 ( ) = ^ ~ " 6 7 8 ! . 9 + @ * 2 3 4 5 
  [_SYM] = LAYOUT(
    UC_SHRG, KC_TRANS, KC_SLASH,  KC_LBRC,  KC_RBRC,  KC_CIRC,                                                   KC_DQUO,  KC_LABK,  KC_RABK,  KC_UNDS,  KC_TILDE, KC_TRANS, 
    UC_DISA, KC_HASH,  KC_EQUAL,  KC_LCBR,  KC_RCBR,  KC_ASTR,                                                   KC_PLUS,  KC_LPRN,  KC_RPRN,  KC_MINUS, KC_COLN,  KC_TRANS, 
    UC_LVIT, KC_DLR,   KC_BSLASH, KC_PIPE,  KC_AMPR,  KC_GRV,          KC_TRANS, KC_TRANS,   KC_TRANS, KC_TRANS, KC_QUOT,  KC_PERC,  KC_EXLM,  KC_QUES,  KC_AT,    KC_TRANS, 
                                  KC_TRANS, KC_TRANS, KC_SMART_NUMBER, KC_TRANS, KC_TRANS,   KC_TRANS, KC_TRANS, KC_TRANS, KC_TRANS, KC_TRANS                                
  ),
  [_NUM] = LAYOUT(
    KC_TRANS, KC_TRANS, KC_TRANS, KC_LBRACKET, KC_RBRACKET, KC_SLASH,                                           KC_MINUS, KC_LPRN,  KC_RPRN,  KC_TRANS, KC_TRANS, KC_TRANS, 
    KC_TRANS, KC_5,     KC_6,     KC_7,        KC_8,        KC_ASTR,                                            KC_PLUS,  KC_1,     KC_2,     KC_3,     KC_4,     KC_TRANS, 
    KC_TRANS, KC_TRANS, KC_TRANS, KC_TRANS,    KC_9,        KC_EQUAL, KC_TRANS, KC_TRANS,   KC_TRANS, KC_TRANS, KC_EQUAL, KC_0,     KC_TRANS, KC_TRANS, KC_TRANS, KC_TRANS, 
                                  KC_TRANS,    KC_TRANS,    KC_TRANS, KC_TRANS, KC_TRANS,   KC_TRANS, KC_TRANS, KC_TRANS, KC_TRANS, KC_TRANS                                
  ),
  [_NAV] = LAYOUT(
    KC_TRANS, KC_TRANS, KC_CLOSE, KC_ESCAPE, KC_ENTER, KC_TAB,                                            KC_INSERT,         KC_PGUP,   KC_HOME,  KC_TRANS, KC_TRANS, KC_TRANS, 
    KC_TRANS, OS_CMD,   OS_ALT,   OS_CTRL,   OS_SHFT,  KC_DELETE,                                         KC_LEFT,           KC_DOWN,   KC_UP,    KC_RIGHT, KC_TRANS, KC_TRANS, 
    KC_TRANS, KC_UNDO,  KC_CUT,   KC_COPY,   KC_PASTE, KC_BSPACE, KC_TRANS, KC_TRANS,   KC_PDT, KC_TRANS, KC_TRANS,          KC_PGDOWN, KC_END,   KC_TRANS, KC_TRANS, KC_TRANS, 
                                  KC_TRANS,  KC_TRANS, KC_TRANS,  KC_TRANS, KC_TRANS,   KC_NDT, KC_TRANS, KC_SMART_CAPSLOCK, KC_TRANS,  KC_TRANS                                
  ),
  [_FNC] = LAYOUT(
    KC_TRANS, KC_F12, KC_F11, KC_F10,   KC_F9,    KC_TRANS,                                           KC_TRANS, KC_TRANS, KC_TRANS, KC_TRANS, KC_TRANS, KC_TRANS, 
    KC_TRANS, KC_F8,  KC_F7,  KC_F6,    KC_F5,    KC_TRANS,                                           KC_TRANS, OS_SHFT,  OS_CTRL,  OS_ALT,   OS_CMD,   KC_TRANS, 
    KC_TRANS, KC_F4,  KC_F3,  KC_F2,    KC_F1,    KC_TRANS, KC_TRANS, KC_TRANS,   KC_TRANS, KC_TRANS, KC_TRANS, KC_TRANS, KC_TRANS, KC_TRANS, KC_TRANS, KC_TRANS, 
                              KC_TRANS, KC_TRANS, KC_TRANS, KC_TRANS, KC_TRANS,   KC_TRANS, KC_TRANS, KC_TRANS, KC_TRANS, KC_TRANS                                
  ),
  [_MOUS] = LAYOUT(
    MU_MOD,   KC_MPLY,  MU_TOG,   KC_TRANS, KC_TRANS, KC_OLED,                                            KC_MS_WH_UP,   KC_MS_BTN1,    KC_MS_UP,   KC_MS_BTN2,     RGB_SAI, RGB_SAD, 
    MU_TOG,   KC_LGUI,  KC_LALT,  KC_LCTL,  KC_LSFT,  KC_TRANS,                                           KC_MS_WH_DOWN, KC_MS_LEFT,    KC_MS_DOWN, KC_MS_RIGHT,    RGB_HUI, RGB_HUD, 
    KC_TRANS, KC_TRANS, KC_TRANS, KC_TRANS, KC_TRANS, KC_TRANS, KC_TRANS, KC_TRANS,   KC_TRANS, KC_TRANS, KC_TRANS,      KC_MS_WH_LEFT, KC_MS_BTN3, KC_MS_WH_RIGHT, RGB_VAI, RGB_VAD, 
                                  KC_TRANS, KC_TRANS, KC_TRANS, KC_PDT,   KC_NDT,     KC_TRANS, KC_TRANS, KC_TRANS,      KC_TRANS,      KC_TRANS                                      
  )
};
// clang-format on
typedef enum {
    htc_scanning           = 0,
    htc_primary_pressed    = 1,
    htc_secondary_pressed  = 2,
    htc_secondary_released = 4,
    htc_primary_released   = 8,
    htc_activated          = 0xF,
} ehold_tap_combo_state;

typedef enum {
    htc_action_toggle_smartnum = 1,
    htc_action_toggle_capsword = 2,
} ehold_tap_combo_action;

typedef struct {
    uint16_t               m_keycode_primary;
    uint16_t               m_keycode_secondary;
    ehold_tap_combo_state  m_state;
    ehold_tap_combo_action m_action;
} hold_tap_combo_t;

//static hold_tap_combo_t htc_combo_smart_number = {.m_keycode_primary = LA_NAV, .m_keycode_secondary = LA_SYM, .m_state = htc_scanning, .m_action = htc_action_toggle_smartnum};
//static hold_tap_combo_t htc_combo_caps_word    = {.m_keycode_primary = LA_SYM, .m_keycode_secondary = LA_NAV, .m_state = htc_scanning, .m_action = htc_action_toggle_capsword};

int8_t process_htc(hold_tap_combo_t* htc, uint16_t keycode, keyrecord_t* record, int8_t keycode_consumed) {
    ehold_tap_combo_state state = 0;
    if (keycode == htc->m_keycode_primary) {
        if (record->event.pressed) {
            state = htc_primary_pressed;
        } else {
            if (htc->m_state == htc_primary_pressed) {
                state = htc_primary_released;
            }
        }
    } else if (keycode == htc->m_keycode_secondary) {
        if (record->event.pressed) {
            if (htc->m_state == (htc_primary_pressed | htc_primary_released)) {
                state = htc_secondary_pressed;
            }
        } else {
            if (htc->m_state == (htc_primary_pressed | htc_primary_released | htc_secondary_pressed)) {
                state = htc_secondary_released;
            }
        }
    }

    if (state == 0 || keycode_consumed > 0) {
        htc->m_state = 0;
    } else {
        htc->m_state |= state;
        if (htc->m_state == htc_activated) {
            // execute action
            if (htc->m_action == htc_action_toggle_smartnum) {
                smart_feature_toggle(SMART_NUMBERS, _SMART_NUM);
            } else if (htc->m_action == htc_action_toggle_capsword) {
                uint8_t layer = _QWERTY_CAPS;
                if ((default_layer_state & (1 << _RSTHD)) != 0) layer = _RSTHD_CAPS;
                smart_feature_toggle(SMART_CAPSLOCK, layer);
            }

            htc->m_state = htc_scanning;
            return 1;
        }
    }

    return 0;
}

#ifdef ENABLE_ONESHOT

bool is_oneshot_modifier_cancel_key(uint16_t keycode) {
    switch (keycode) {
        case LA_FNC:
        case LA_NAV:
            return true;
        default:
            return false;
    }
}

bool is_oneshot_modifier_ignored_key(uint16_t keycode) {
    switch (keycode) {
        case LA_SYM:
        case LA_NAV:
        case LA_FNC:
        case KC_LSFT:
        case KC_SMART_NUMBER:
            return true;
    }
    return false;
}

oneshot_mod get_modifier_for_trigger_key(uint16_t keycode) {
    switch (keycode) {
        case OS_SHFT:
            return ONESHOT_LSFT;
        case OS_CTRL:
            return ONESHOT_LCTL;
        case OS_ALT:
            return ONESHOT_LALT;
        case OS_CMD:
            return ONESHOT_LGUI;
    }
    return ONESHOT_NONE;
}

#endif

bool smart_feature_cancel_key(uint16_t keycode, keyrecord_t* recor) {
    switch (keycode) {
        case LA_SYM:
        case LA_NAV:
            return true;
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    process_record_oled(keycode, record);

    switch (keycode) {
        case KC_SMART_NUMBER:
            if (record->event.pressed) {
                smart_feature_toggle(SMART_NUMBERS, _NUM);
            }
            break;
        case KC_SMART_CAPSLOCK:
            if (record->event.pressed) {
                uint8_t layer = _QWERTY_CAPS;
                if ((default_layer_state & (1 << _RSTHD)) != 0) layer = _RSTHD_CAPS;
                smart_feature_toggle(SMART_CAPSLOCK, layer);
            }
            break;
        case KC_OLED:
            if (record->event.pressed) {
                toggle_display_oled();
                rgblight_enable();
            }
    }

    // Some features below need to know if the keycode was consumed. For example: If NAV was used
    // to cancel a MOD then HTC should return to its initial state.
    // Also if NAV was used as a cancel key for a smart feature then it should not cancel anything
    // in 'update_oneshot_modifiers'.

    int8_t keycode_consumed = 0;

    if ((smart_feature_cancel_key(keycode, record)) || (keycode < QK_MODS_MAX && !IS_MOD(keycode))) {
        if (smart_feature_state(SMART_CAPSLOCK)) {
            keycode_consumed = 1;
            smart_capslock_process(keycode, record);
        }
        if (smart_feature_state(SMART_NUMBERS)) {
            keycode_consumed = 1;
            smart_numbers_process(keycode, record);
        }
    }

#ifdef ENABLE_ONESHOT
    keycode_consumed += update_oneshot_modifiers(keycode, record, keycode_consumed);
#endif

    //keycode_consumed += process_htc(&htc_combo_smart_number, keycode, record, keycode_consumed);
    //keycode_consumed += process_htc(&htc_combo_caps_word, keycode, record, keycode_consumed);

    switch (keycode) {
        case KC_QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            break;
        case KC_RSTHD:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_RSTHD);
            }
            break;
#ifdef UNICODE_ENABLE
        case UC_SHRG:  // ¯\_(ツ)_/¯
            if (record->event.pressed) {
                send_unicode_string("¯\\_(ツ)_/¯");
            }
            break;
        case UC_DISA:  // ಠ_ಠ
            if (record->event.pressed) {
                send_unicode_string("ಠ_ಠ");
            }
            break;
        case UC_LVIT:  // ♥‿♥
            if (record->event.pressed) {
                send_unicode_string("♥‿♥");
            }
            break;
#endif
    }

    return true;
};

// Layer-specific encoder knob functions
#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
    uint16_t layers = (layer_state | default_layer_state);
    if (index == 0) {  // left knob
        switch (get_highest_layer(layers)) {
            case _SYM:  // Desktop switching
                if (clockwise) {
                    tap_code16(KC_NDT);
                } else {
                    tap_code16(KC_PDT);
                }
                break;
            case _FNC:  // Mousewheel Up/Down
                if (clockwise) {
                    tap_code(KC_MS_WH_UP);
                } else {
                    tap_code(KC_MS_WH_DOWN);
                }
                break;
            case _MOUS:  // Underglow color
                if (clockwise) {
                    rgblight_increase_hue();
                } else {
                    rgblight_decrease_hue();
                }
                break;
            default:  // Volume Up/Down
                if (clockwise) {
                    tap_code(KC_VOLD);
                } else {
                    tap_code(KC_VOLU);
                }
                break;
        }
    } else if (index == 1) {  // right knob
        switch (get_highest_layer(layers)) {
            case _NAV:  // Undo/Redo
                if (clockwise) {
                    tap_code16(KC_UNDO);
                } else {
                    tap_code16(KC_REDO);
                }
                break;
            case _MOUS:  // Underglow brightness
                if (clockwise) {
                    rgblight_increase_val();
                } else {
                    rgblight_decrease_val();
                }
                break;
            default:  // Brightness Up/Down
                if (clockwise) {
                    tap_code(KC_BRIU);
                } else {
                    tap_code(KC_BRID);
                }
                break;
        }
    } else {
        tap_code16(S(KC_SLASH));
    }
}
#endif

/*
qmk-keyboard-format:json:begin
{
  "name": "Kyria",
  "numkeys": 50,
  "rows": [
      [ -3,  0,  1,  2,  3,  4,  5, -1, -1, -2, -1, -1,  6,  7,  8,  9, 10, 11 ],
      [ -3, 12, 13, 14, 15, 16, 17, -1, -1, -2, -1, -1, 18, 19, 20, 21, 22, 23 ],
      [ -3, 24, 25, 26, 27, 28, 29, 30, 31, -2, 32, 33, 34, 35, 36, 37, 38, 39 ],
      [ -3, -1, -1, -1, 40, 41, 42, 43, 44, -2, 45, 46, 47, 48, 49, -1, -1, -1 ]
  ],
  "spacing": [
      0,
      0,
      0,
      2
  ],
  "vizcellwidth": 5,
  "vizemits": [
      { "line": "[_QWERTY] = LAYOUT(", "layer": "_QWERTY" }
  ],
  "vizline": "//#",
  "vizboard": [
      "    //#                         ╭───────╮                                                                        ╭───────╮                          ",
      "    //#                 ╭───────╯ _003_ ╰───────╮                                                        ╭───────╯ _008_ ╰───────╮                  ",
      "    //#                 │ _002_ │       │ _004_ ╭───────╮                                        ╭───────╮ _007_ │       │ _009_ │                  ",
      "    //# ╭───────╮───────╯       ╰───────╯       │ _005_ │                                        │ _006_ │       ╰───────╯       ╰───────╭───────╮  ",
      "    //# │ _000_ │ _001_ ╰───────╯ _015_ ╰───────╯       │                                        │       ╰───────╯ _020_ ╰───────╯ _010_ │ _011_ │  ",
      "    //# │       │       │ _014_ │       │ _016_ ╰───────╯                                        ╰───────╯ _019_ │       │ _021_ │       │       │  ",
      "    //# ╰───────╯───────╯       ╰───────╯       │ _017_ │                                        │ _018_ │       ╰───────╯       ╰───────╰───────╯  ",
      "    //# │ _012_ │ _013_ ╰───────╯ _027_ ╰───────╯       │                                        │       ╰───────╯ _036_ ╰───────╯ _022_ │ _023_ │  ",
      "    //# │       │       │ _026_ │       │ _028_ ╰───────╯                                        ╰───────╯ _035_ │       │ _037_ │       │       │  ",
      "    //# ╰───────╯───────╯       ╰───────╯       │ _029_ │ ╭───────╮                    ╭───────╮ │ _034_ │       ╰───────╯       ╰───────╰───────╯  ",
      "    //# │ _024_ │ _025_ ╰───────╯       ╰───────╯       │ │ _030_ ╰───────╮    ╭───────╯ _033_ │ │       ╰───────╯       ╰───────╯ _038_ │ _039_ │  ",
      "    //# │       │       │              ╭───────╮╰───────╯ │       │ _031_ │    │ _032_ │       │ ╰───────╯╭───────╮              │       │       │  ",
      "    //# ╰───────╯───────╯     ╭───────╮│ _041_ ╰───────╮  ╰───────╯       │    │       ╰───────╯  ╭───────╯ _048_ │╭───────╮     ╰───────╰───────╯  ",
      "    //#                       │ _040_ ││       │ _042_ ╰───────╮  ╰───────╯    ╰───────╯  ╭───────╯ _047_ │       ││ _049_ │                        ",
      "    //#                       │       │╰───────╯       │ _043_ ╰───────╮          ╭───────╯ _046_ │       ╰───────╯│       │                        ",
      "    //#                       ╰encodr─╯        ╰───────╯       │ _044_ │          │ _045_ │       ╰───────╯        ╰encodr─╯                        ",
      "    //#                                                ╰───────╯       │          │       ╰───────╯                                                 ",
      "    //#                                                        ╰───────╯          ╰───────╯                                                         "
  ],
  "vizsymbols": {
      "TG(_MOUS)": "MOUSE",
      "TG(_SYSTEM)": " SYS ",
      "MO(_NAV)": "NAVI ",
      "MO(_FNC)": "FUNC ",
      "MO(_SYM)": " SYM ",
      "TG(_QWERTY_CAPS)": "CAPS ",
      "TG(_RSTHD_CAPS)": "CAPS ",
      "KC_SMART_NUMBER": "SMNUM",
      "KC_SMART_CAPSLOCK": "SMCAP",
      "OSM(MOD_LSFT)": "SHIFT",
      "_______": "     ",
      "KC_TRANS": "     ",
      "KC_0": "  0  " ,
      "KC_1": "  1  " ,
      "KC_2": "  2  " ,
      "KC_3": "  3  " ,
      "KC_4": "  4  " ,
      "KC_5": "  5  " ,
      "KC_6": "  6  " ,
      "KC_7": "  7  " ,
      "KC_8": "  8  " ,
      "KC_9": "  9  " ,
      "KC_A": "  A  " ,
      "KC_B": "  B  " ,
      "KC_C": "  C  " ,
      "KC_D": "  D  " ,
      "KC_E": "  E  " ,
      "KC_F": "  F  " ,
      "KC_G": "  G  " ,
      "KC_H": "  H  " ,
      "KC_I": "  I  " ,
      "KC_J": "  J  " ,
      "KC_K": "  K  " ,
      "KC_L": "  L  " ,
      "KC_M": "  M  " ,
      "KC_N": "  N  " ,
      "KC_O": "  O  " ,
      "KC_P": "  P  " ,
      "KC_Q": "  Q  " ,
      "KC_R": "  R  " ,
      "KC_S": "  S  " ,
      "KC_T": "  T  " ,
      "KC_U": "  U  " ,
      "KC_V": "  V  " ,
      "KC_W": "  W  " ,
      "KC_X": "  X  " ,
      "KC_Y": "  Y  " ,
      "KC_Z": "  Z  " ,
      "KC_COMMA": "  ,  ",
      "KC_COMM": "  ,  ",
      "KC_DOT": "  .  ",
      "KC_COLN": "  :  ",
      "KC_SCOLON": "  ;  ",
      "KC_SCLN": "  ;  ",
      "KC_SLASH": "  \/  ",
      "KC_SLSH": "  \/  ",
      "KC_BSLASH": "  \\  ",
      "KC_BSLS": "  \\  ",
      "KC_EXLM": "  !  ",
      "KC_QUES": "  ?  ",
      "KC_PIPE": "  |  ",
      "KC_QUOT": "  '  ",
      "KC_QUOTE": "  '  ",
      "KC_DQUO": "  \"  ",
      "KC_DQT": "  \"  ",
      "KC_HASH": "  #  ",
      "KC_AMPR": "  &  ",
      "KC_PERC": "  %  ",
      "KC_TILDE": "  ~  ",
      "KC_AT": "  @  ",
      "KC_DLR": "  $  ",
      "KC_CIRC": "  ^  ",
      "KC_EQL": "  =  ",
      "KC_EQUAL": "  =  ",
      "KC_ASTR": "  *  ",
      "KC_MINS": "  -  ",
      "KC_MINUS": "  -  ",
      "KC_UNDS": "  _  ",
      "KC_PLUS": "  +  ",
      "KC_LCBR": "  {  ",
      "KC_LBRACKET": "  {  ",
      "KC_RCBR": "  }  ",
      "KC_RBRACKET": "  }  ",
      "KC_LPRN": "  (  ",
      "KC_RPRN": "  )  ",
      "KC_GRV": "  `  ",
      "KC_LBRC": "  [  ",
      "KC_RBRC": "  ]  ",
      "KC_LABK": "  <  ",
      "KC_RABK": "  >  ",
      "KC_TILD": "  ~  ",
      "KC_ESC": " ESC " ,
      "KC_ESCAPE": " ESC " ,
      "KC_COPY": " Copy",
      "KC_PASTE": "Paste",
      "KC_CUT":    " Cut " ,
      "KC_UNDO":   " Undo" ,
      "KC_REDO": " Redo " ,
      "KC_VOLU": "  🕪  " ,
      "KC_VOLD": "  🕩  " ,
      "KC_MUTE":   "  🕨  " ,
      "KC_TAB": " TAB " ,
      "KC_MENU": "  𝌆  " ,
      "KC_CAPSLOCK": "  ⇪  " ,
      "KC_NUMLK": "  ⇭  " ,
      "KC_SCRLK": "  ⇳  " ,
      "KC_PRSCR": "  ⎙  " ,
      "KC_PAUSE": "  ⎉  " ,
      "KC_BREAK": "  ⎊  " ,
      "KC_ENTER": "  ⏎  " ,
      "KC_BSPACE": "  ⌫  " ,
      "KC_DELETE": "  ⌦  " ,
      "KC_INSERT": "Insrt" ,
      "KC_LEFT":  "  L  " ,
      "KC_RIGHT": "  R  " ,
      "KC_UP":    "  U  " ,
      "KC_DOWN":  "  D  " ,
      "KC_HOME": "  ⇤  " ,
      "KC_END": "  ⇥  " ,
      "KC_PGUP": "  ⇞  " ,
      "KC_PGDOWN": "  ⇟  " ,
      "KC_LSFT": "  ⇧  " ,
      "KC_RSFT": "  ⇧  " ,
      "OS_SHFT": "  ⇧  " ,
      "KC_LCTL": "  ^  " ,
      "KC_RCTL": "  ^  " ,
      "OS_CTRL": "  ^  " ,
      "KC_LALT": "  ⎇  " ,
      "KC_RALT": "  ⎇  " ,
      "OS_ALT": "  ⎇  " ,
      "KC_HYPER": "  ✧  " ,
      "KC_LGUI": "  ⌘  " ,
      "KC_RGUI": "  ⌘  ",
      "OS_CMD": "  ⌘  "
  }
}
qmk-keyboard-format:json:end
*/
