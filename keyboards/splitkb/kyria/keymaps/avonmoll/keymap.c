/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "oneshot.h"

/*
DONE: Implement closing ), ], }
DONE: Implement Greek layer (unicode)
DONE: Make a button for switching between Linux and Mac for cut, copy, paste, etc.
*/

enum layers {
    _COLEMAK_DH = 0,
	_QWERTY,
    _NAV,
    _SYM,
    _FUNCTION,
    _ADJUST,
	_GREEK,
	_SGREEK,
};


// Aliases for readability
#define QWERTY   DF(_QWERTY)
#define COLEMAK  DF(_COLEMAK_DH)

#define SYM      MO(_SYM)
#define NAV      MO(_NAV)
#define FKEYS    MO(_FUNCTION)
#define ADJUST   MO(_ADJUST)
#define GREEK    OSL(_GREEK)
#define SGREEK   OSL(_SGREEK)

#define PLY_PAUS KC_MEDIA_PLAY_PAUSE

enum custom_keycodes {
	OS_GUI = SAFE_RANGE,
	OS_SHF,
	OS_CTL,
	OS_ALT,
	TABL,
	TABR,
	W_BSP,
	TOG_MAC,
	UNDO,
	CUT,
	COPY,
	PASTE,
    UC_SHRG,  // ¯\_(ツ)_/¯
	UC_ALPH,  // α
	UC_BETA,  // β
	UC_GAMM,  // γ
	UC_CGAM,  // Γ
	UC_DELT,  // δ
	UC_CDEL,  // Δ
	UC_EPSI,  // ϵ
	UC_VEPS,  // ε
	UC_ZETA,  // ζ
	UC_ETA,   // η
	UC_THET,  // θ
	UC_CTHE,  // Θ
	UC_KAPP,  // κ
	UC_LAMB,  // λ
	UC_CLAM,  // Λ
	UC_MU,    // μ
	UC_NU,    // ν
	UC_XI,    // ξ
	UC_CXI,   // Ξ
	UC_PI,    // π
	UC_CPI,   // Π
	UC_RHO,   // ρ
	UC_SIGM,  // σ
	UC_CSIG,  // Σ
	UC_TAU,   // τ
	UC_PHI,   // ϕ
	UC_CPHI,  // Φ
	UC_CHI,   // χ
	UC_PSI,   // ψ
	UC_CPSI,  // Ψ
	UC_OMEG,  // ω
	UC_COME,  // Ω
	UC_UPSI,  // υ
	UC_CUPS,  // Υ
};

// Note: LAlt/Enter (ALT_ENT) is not the same thing as the keyboard shortcut Alt+Enter.
// The notation `mod/tap` denotes a key that activates the modifier `mod` when held down, and
// produces the key `tap` when tapped (i.e. pressed and released).

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: Colemak DH
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  `  ~  |   Q  |   W  |   F  |   P  |   B  |                              |   J  |   L  |   U  |   Y  | ;  : |   :    |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |   <    |   A  |   R  |   S  |   T  |   G  |                              |   M  |   N  |   E  |   I  |   O  |   >    |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | CapsLk |   Z  |   X  |   C  |   D  |   V  | Esc  |F-keys|  |GREEK | WBSpc|   K  |   H  | ,  < | . >  | /  ? |   ?    |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |Play/ | HYP  | Nav  | Space| Tab  |  | ENTR | BSpc | Sym  | HYP  | Menu |
 *                        |Pause |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_COLEMAK_DH] = LAYOUT(
     KC_GRV  , KC_Q ,  KC_W   ,  KC_F  ,   KC_P ,   KC_B,                                        KC_J,   KC_L ,  KC_U ,   KC_Y ,KC_SCLN, KC_COLN,
     KC_LT   , KC_A ,  KC_R   ,  KC_S  ,   KC_T ,   KC_G,                                        KC_M,   KC_N ,  KC_E ,   KC_I ,  KC_O , KC_GT  ,
     KC_CAPS , KC_Z ,  KC_X   ,  KC_C  ,   KC_D ,   KC_V, KC_ESC, FKEYS  ,     GREEK  , W_BSP  , KC_K,   KC_H ,KC_COMM, KC_DOT ,KC_SLSH, KC_QUES,
                                KC_MPLY, KC_HYPR,   NAV , KC_SPC , KC_TAB,     KC_ENT , KC_BSPC, SYM , KC_HYPR, KC_APP
    ),

/*
 * Base Layer: QWERTY
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  `  ~  |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |   :    |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |   <    |   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |   >    |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | CapsLk |   Z  |   X  |   C  |   V  |   B  | Esc  |F-keys|  |GREEK | WBSpc|   N  |   M  | ,  < | . >  | /  ? |   ?    |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |Play/ | HYP  | Nav  | Space| Tab  |  | ENTR | BSpc | Sym  | HYP  | Menu |
 *                        |Pause |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_QWERTY] = LAYOUT(
     KC_GRV  , KC_Q ,  KC_W   ,  KC_E  ,   KC_R ,   KC_T,                                        KC_Y,   KC_U ,  KC_I ,   KC_O , KC_P,    KC_COLN,
     KC_LT   , KC_A ,  KC_S   ,  KC_D  ,   KC_F ,   KC_G,                                        KC_H,   KC_J ,  KC_K ,   KC_L , KC_SCLN, KC_GT  ,
     KC_CAPS , KC_Z ,  KC_X   ,  KC_C  ,   KC_V ,   KC_B, KC_ESC, FKEYS  ,     GREEK  , W_BSP  , KC_N,   KC_M ,KC_COMM, KC_DOT , KC_SLSH, KC_QUES,
                                KC_MPLY, KC_HYPR, NAV , KC_SPC , KC_TAB,     KC_ENT , KC_BSPC  , SYM,    KC_HYPR, KC_APP
    ),

/*
 * Nav Layer: Media, navigation
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      | TABL | TABR |      |                              | PgUp | Home |   ↑  | End  | VolUp| Delete |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  Alt |  Ctl | Shift| GUI  |      |                              | PgDn |  ←   |   ↓  |   →  | VolDn| Insert |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  UN  |  CUT | COPY | PASTE|      |      |ScLck |  |      |      | Pause|M Prev|M Play|M Next|VolMut| PrtSc  |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NAV] = LAYOUT(
      _______, _______, _______,   TABL ,   TABR  , _______,                                     KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_VOLU, KC_DEL,
      _______, OS_ALT , OS_CTL , OS_SHF ,  OS_GUI , _______,                                     KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_VOLD, KC_INS,
      _______,   UNDO ,    CUT ,    COPY,    PASTE, _______, KC_SLCK, _______, _______, _______,KC_PAUSE, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_PSCR,
                                 _______, _______ , _______, _______, _______, _______, _______, _______, _______, _______
    ),

/*
 * Sym Layer: Numbers and symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  7   |  5   |  3   |  1   |  9   |                              |   8  |  0   |  2   |  4   |  6   |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        | ' "  |  {}  |  []  |  ()  |  = + |                              |      |  GUI |  SHF | CTL  | ALT  |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  &   |  %   |  #   |  !   |  - _ |      |      |  |      |      |   *  | \ |  |  @   |  $   |  ^   |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_SYM] = LAYOUT(
     _______ ,   KC_7 ,   KC_5 ,   KC_3 ,   KC_1 ,   KC_9 ,                                       KC_8 ,   KC_0 ,   KC_2 ,   KC_4 ,   KC_6 , _______,
     _______ , KC_QUOT, KC_LCBR, KC_LBRC, KC_LPRN, KC_EQL ,                                     _______, OS_GUI , OS_SHF , OS_CTL , OS_ALT , _______,
     _______ , KC_AMPR, KC_COLN, KC_HASH, KC_EXLM, KC_MINS, _______, _______, _______, _______, KC_ASTR, KC_BSLS, KC_AT  ,  KC_DLR, KC_CIRC, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

/*
 * Function Layer: Function keys
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              |      |  F1  |  F2  |  F3  |  F4  |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |                              |      |  F5  |  F6  |  F7  |  F8  |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |      |  F9  |  F10 |  F11 |  F12 |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_FUNCTION] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     _______, KC_F1  ,  KC_F2 ,  KC_F3 ,  KC_F4 , _______,
      _______, _______, _______, _______, _______, _______,                                     _______, KC_F5  ,  KC_F6 ,  KC_F7 ,  KC_F8 , _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_F9  ,  KC_F10,  KC_F11,  KC_F12, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

/*
 * Adjust Layer: Default layer settings, RGB
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |QWERTY|      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |      | MAC  |      |                              | TOG  | SAI  | HUI  | VAI  | MOD  |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |Colmak|      |      |      |      |  |      |      |      | SAD  | HUD  | VAD  | RMOD |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_ADJUST] = LAYOUT(
      _______, _______, _______, QWERTY , _______, UC_M_LN,                                    _______, _______, _______, _______,  _______, _______,
      _______, _______, _______, _______, TOG_MAC, UC_M_MA,                                    RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI,  RGB_MOD, _______,
      _______, _______, _______, COLEMAK, _______, _______,_______, _______, _______, _______, _______, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD, _______,
                                 _______, _______, _______,_______, _______, _______, _______, _______, _______, _______
    ),

/*
 * Greek layer: Send Greek letters via send_unicode_string
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        | SHRG |  ω   |  ϕ   |  π   |  β   |                              |  η   |  λ   |  υ   |  ψ   |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  α   |  ρ   |  σ   |  τ   |  γ   |                              |  μ   |  ν   |  ϵ   |      |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  ζ   |  χ   |  ξ   |  δ   |  ε   |      |      |  |SGREEK|      |  κ   |  θ   |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_GREEK] = LAYOUT(
      _______, UC_SHRG, UC_OMEG, UC_PHI , UC_PI  , UC_BETA,                                     UC_ETA , UC_LAMB, UC_UPSI, UC_PSI , _______, _______,
      _______, UC_ALPH, UC_RHO , UC_SIGM, UC_TAU , UC_GAMM,                                     UC_MU  , UC_NU  , UC_EPSI, _______, _______, _______,
      _______, UC_ZETA, UC_CHI , UC_XI  , UC_DELT, UC_VEPS, _______, _______, SGREEK , _______, UC_KAPP, UC_THET, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

/*
 * Shifted Greek layer: Send capital Greek letters via send_unicode_string
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |  Ω   |  Φ   |  Π   |      |                              |      |  Λ   |  Υ   |  Ψ   |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |  Σ   |      |  Γ   |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |  Ξ   |  Δ   |      |      |      |  |      |      |      |  Θ   |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_SGREEK] = LAYOUT(
      _______, _______, UC_COME, UC_CPHI, UC_CPI , _______,                                     _______, UC_CLAM, UC_CUPS, UC_CPSI, _______, _______,
      _______, _______, _______, UC_CSIG, _______, UC_CGAM,                                     _______, _______, _______, _______, _______, _______,
      _______, _______, _______, UC_CXI , UC_CDEL, _______, _______, _______, _______, _______, _______, UC_CTHE, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
	
// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),
};

layer_state_t layer_state_set_user(layer_state_t state) { return update_tri_layer_state(state, _NAV, _SYM, _ADJUST); }

// Key overrides for closing ) ] }
const key_override_t rparen_override = ko_make_basic(MOD_MASK_SHIFT, KC_LPRN, KC_RPRN);
const key_override_t rbrace_override = ko_make_basic(MOD_MASK_SHIFT, KC_LBRC, KC_RBRC);
const key_override_t rcbrac_override = ko_make_basic(MOD_MASK_SHIFT, KC_LCBR, KC_RCBR);

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
    &rparen_override,
    &rbrace_override,
    &rcbrac_override,
    NULL // Null terminate the array of overrides!
};

// Callum-style one-shot mods
#ifdef ENABLE_ONESHOT
bool is_oneshot_modifier_cancel_key(uint16_t keycode) {
    switch (keycode) {
        case KC_ESC:
            return true;
        default:
            return false;
    }
}

bool is_oneshot_modifier_ignored_key(uint16_t keycode) {
    switch (keycode) {
        case SYM:
        case NAV:
		case FKEYS:
        case ADJUST:
        case GREEK:
            return true;
    }
    return false;
}

oneshot_mod get_modifier_for_trigger_key(uint16_t keycode) {
    switch (keycode) {
        case OS_SHF:
            return ONESHOT_LSFT;
        case OS_CTL:
            return ONESHOT_LCTL;
        case OS_ALT:
            return ONESHOT_LALT;
        case OS_GUI:
            return ONESHOT_LGUI;
    }
    return ONESHOT_NONE;
}
#endif

bool is_macos = false;

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    int8_t keycode_consumed = 0;

#ifdef ENABLE_ONESHOT
    keycode_consumed += update_oneshot_modifiers(keycode, record, keycode_consumed);
#endif

    switch (keycode) {
        case TOG_MAC:
            if (record->event.pressed) {
				is_macos = !is_macos;
            }
            break;
		case TABL:
			if (record->event.pressed) {
				if(is_macos) {
					register_code(KC_LGUI);
					register_code(KC_LSFT);
					tap_code(KC_TAB);
					unregister_code(KC_LGUI);
					unregister_code(KC_LSFT);
				} else {
					register_code(KC_LCTL);
					register_code(KC_LSFT);
					tap_code(KC_TAB);
					unregister_code(KC_LCTL);
					unregister_code(KC_LSFT);
				}
			}
			break;
		case TABR:
			if (record->event.pressed) {
				if(is_macos) {
					register_code(KC_LGUI);
					tap_code(KC_TAB);
					unregister_code(KC_LGUI);
				} else {
					register_code(KC_LCTL);
					tap_code(KC_TAB);
					unregister_code(KC_LCTL);
				}
			}
			break;
		case W_BSP:
			if (record->event.pressed) {
				if(is_macos) {
					register_code(KC_LALT);
					tap_code(KC_BSPC);
					unregister_code(KC_LALT);
				} else {
					register_code(KC_LCTL);
					tap_code(KC_BSPC);
					unregister_code(KC_LCTL);
				}
			}
			break;
		case UNDO:
			if (record->event.pressed) {
				if (is_macos) {
					register_code(KC_LGUI);
					tap_code(KC_Z);
					unregister_code(KC_LGUI);
				} else {
					register_code(KC_LCTL);
					tap_code(KC_Z);
					unregister_code(KC_LCTL);
				}
			}
			break;
		case CUT:
			if (record->event.pressed) {
				if (is_macos) {
					register_code(KC_LGUI);
					tap_code(KC_X);
					unregister_code(KC_LGUI);
				} else {
					register_code(KC_LCTL);
					tap_code(KC_X);
					unregister_code(KC_LCTL);
				}
			}
			break;
		case COPY:
			if (record->event.pressed) {
				if (is_macos) {
					register_code(KC_LGUI);
					tap_code(KC_C);
					unregister_code(KC_LGUI);
				} else {
					register_code(KC_LCTL);
					tap_code(KC_C);
					unregister_code(KC_LCTL);
				}
			}
			break;
		case PASTE:
			if (record->event.pressed) {
				if (is_macos) {
					register_code(KC_LGUI);
					tap_code(KC_V);
					unregister_code(KC_LGUI);
				} else {
					register_code(KC_LCTL);
					tap_code(KC_V);
					unregister_code(KC_LCTL);
				}
			}
			break;
#ifdef UNICODE_ENABLE
        case UC_SHRG:  // ¯\_(ツ)_/¯
            if (record->event.pressed) {
                send_unicode_string("¯\\_(ツ)_/¯");
            }
            break;
		case UC_ALPH:  // α
            if (record->event.pressed) {
                send_unicode_string("α");
            }
            break;
		case UC_BETA:  // β
            if (record->event.pressed) {
                send_unicode_string("β");
            }
            break;
		case UC_GAMM:  // γ
            if (record->event.pressed) {
                send_unicode_string("γ");
            }
            break;
		case UC_CGAM:  // Γ
            if (record->event.pressed) {
                send_unicode_string("Γ");
            }
            break;
		case UC_DELT:  // δ
            if (record->event.pressed) {
                send_unicode_string("δ");
            }
            break;
		case UC_CDEL:  // Δ
            if (record->event.pressed) {
                send_unicode_string("Δ");
            }
            break;
		case UC_EPSI:  // ϵ
            if (record->event.pressed) {
                send_unicode_string("ϵ");
            }
            break;
		case UC_VEPS:  // ε
            if (record->event.pressed) {
                send_unicode_string("ε");
            }
            break;
		case UC_ZETA:  // ζ
            if (record->event.pressed) {
                send_unicode_string("ζ");
            }
            break;
		case UC_ETA:  // η
            if (record->event.pressed) {
                send_unicode_string("η");
            }
            break;
		case UC_THET:  // θ
            if (record->event.pressed) {
                send_unicode_string("θ");
            }
            break;
		case UC_CTHE:  // Θ
            if (record->event.pressed) {
                send_unicode_string("Θ");
            }
            break;
		case UC_KAPP:  // κ
            if (record->event.pressed) {
                send_unicode_string("κ");
            }
            break;
		case UC_LAMB:  // λ
            if (record->event.pressed) {
                send_unicode_string("λ");
            }
            break;
		case UC_CLAM:  // Λ
            if (record->event.pressed) {
                send_unicode_string("Λ");
            }
            break;
		case UC_MU:    // μ
            if (record->event.pressed) {
                send_unicode_string("μ");
            }
            break;
		case UC_NU:    // ν
            if (record->event.pressed) {
                send_unicode_string("ν");
            }
            break;
		case UC_XI:    // ξ
            if (record->event.pressed) {
                send_unicode_string("ξ");
            }
            break;
		case UC_CXI:   // Ξ
            if (record->event.pressed) {
                send_unicode_string("Ξ");
            }
            break;
		case UC_PI:    // π
            if (record->event.pressed) {
                send_unicode_string("π");
            }
            break;
		case UC_CPI:   // Π
            if (record->event.pressed) {
                send_unicode_string("Π");
            }
            break;
		case UC_RHO:   // ρ
            if (record->event.pressed) {
                send_unicode_string("ρ");
            }
            break;
		case UC_SIGM:  // σ
            if (record->event.pressed) {
                send_unicode_string("σ");
            }
            break;
		case UC_CSIG:  // Σ
            if (record->event.pressed) {
                send_unicode_string("Σ");
            }
            break;
		case UC_TAU:   // τ
            if (record->event.pressed) {
                send_unicode_string("τ");
            }
            break;
		case UC_PHI:   // ϕ
            if (record->event.pressed) {
                send_unicode_string("ϕ");
            }
            break;
		case UC_CPHI:  // Φ
            if (record->event.pressed) {
                send_unicode_string("Φ");
            }
            break;
		case UC_CHI:   // χ
            if (record->event.pressed) {
                send_unicode_string("χ");
            }
            break;
		case UC_PSI:   // ψ
            if (record->event.pressed) {
                send_unicode_string("ψ");
            }
            break;
		case UC_CPSI:  // Ψ
            if (record->event.pressed) {
                send_unicode_string("Ψ");
            }
            break;
		case UC_OMEG:  // ω
            if (record->event.pressed) {
                send_unicode_string("ω");
            }
            break;
		case UC_COME:  // Ω
            if (record->event.pressed) {
                send_unicode_string("Ω");
            }
            break;
		case UC_UPSI:  // υ
            if (record->event.pressed) {
                send_unicode_string("υ");
            }
            break;
		case UC_CUPS:  // Υ
            if (record->event.pressed) {
                send_unicode_string("Υ");
            }
            break;
#endif
    }
    return true;
};

/* The default OLED and rotary encoder code can be found at the bottom of qmk_firmware/keyboards/splitkb/kyria/rev1/rev1.c
 * These default settings can be overriden by your own settings in your keymap.c
 * For your convenience, here's a copy of those settings so that you can uncomment them if you wish to apply your own modifications.
 * DO NOT edit the rev1.c file; instead override the weakly defined default functions by your own.
 */

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        // QMK Logo and version information
        // clang-format off
        static const char PROGMEM qmk_logo[] = {
            0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
            0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
            0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};
        // clang-format on

        oled_write_P(qmk_logo, false);
        oled_write_P(PSTR("Kyria rev1.4\n\n"), false);

        // Host Keyboard Layer Status
        oled_write_P(PSTR("Layer: "), false);
        switch (get_highest_layer(layer_state|default_layer_state)) {
			case _COLEMAK_DH:
				oled_write_P(PSTR("Colemak-DH\n"), false);
				break;
            case _QWERTY:
                oled_write_P(PSTR("QWERTY\n"), false);
                break;
            case _NAV:
                oled_write_P(PSTR("Nav\n"), false);
                break;
            case _SYM:
                oled_write_P(PSTR("Sym\n"), false);
                break;
            case _FUNCTION:
                oled_write_P(PSTR("Function\n"), false);
                break;
            case _ADJUST:
                oled_write_P(PSTR("Adjust\n"), false);
                break;
            case _GREEK:
                oled_write_P(PSTR("Greek\n"), false);
                break;
            case _SGREEK:
                oled_write_P(PSTR("Capital Greek\n"), false);
                break;
            default:
                oled_write_P(PSTR("Undefined\n"), false);
        }

        // Write host Keyboard LED Status to OLEDs
        led_t led_usb_state = host_keyboard_led_state();
        oled_write_P(led_usb_state.num_lock    ? PSTR("NUMLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.caps_lock   ? PSTR("CAPLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.scroll_lock ? PSTR("SCRLCK ") : PSTR("       "), false);
    } else {
        // clang-format off
        static const char PROGMEM kyria_logo[] = {
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,224,240,112,120, 56, 60, 28, 30, 14, 14, 14,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 14, 14, 14, 30, 28, 60, 56,120,112,240,224,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,192,224,240,124, 62, 31, 15,  7,  3,  1,128,192,224,240,120, 56, 60, 28, 30, 14, 14,  7,  7,135,231,127, 31,255,255, 31,127,231,135,  7,  7, 14, 14, 30, 28, 60, 56,120,240,224,192,128,  1,  3,  7, 15, 31, 62,124,240,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,240,252,255, 31,  7,  1,  0,  0,192,240,252,254,255,247,243,177,176, 48, 48, 48, 48, 48, 48, 48,120,254,135,  1,  0,  0,255,255,  0,  0,  1,135,254,120, 48, 48, 48, 48, 48, 48, 48,176,177,243,247,255,254,252,240,192,  0,  0,  1,  7, 31,255,252,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,255,255,255,  0,  0,  0,  0,  0,254,255,255,  1,  1,  7, 30,120,225,129,131,131,134,134,140,140,152,152,177,183,254,248,224,255,255,224,248,254,183,177,152,152,140,140,134,134,131,131,129,225,120, 30,  7,  1,  1,255,255,254,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0,255,255,  0,  0,192,192, 48, 48,  0,  0,240,240,  0,  0,  0,  0,  0,  0,240,240,  0,  0,240,240,192,192, 48, 48, 48, 48,192,192,  0,  0, 48, 48,243,243,  0,  0,  0,  0,  0,  0, 48, 48, 48, 48, 48, 48,192,192,  0,  0,  0,  0,  0,
            0,  0,  0,255,255,255,  0,  0,  0,  0,  0,127,255,255,128,128,224,120, 30,135,129,193,193, 97, 97, 49, 49, 25, 25,141,237,127, 31,  7,255,255,  7, 31,127,237,141, 25, 25, 49, 49, 97, 97,193,193,129,135, 30,120,224,128,128,255,255,127,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0, 63, 63,  3,  3, 12, 12, 48, 48,  0,  0,  0,  0, 51, 51, 51, 51, 51, 51, 15, 15,  0,  0, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48, 48, 63, 63, 48, 48,  0,  0, 12, 12, 51, 51, 51, 51, 51, 51, 63, 63,  0,  0,  0,  0,  0,
            0,  0,  0,  0, 15, 63,255,248,224,128,  0,  0,  3, 15, 63,127,255,239,207,141, 13, 12, 12, 12, 12, 12, 12, 12, 30,127,225,128,  0,  0,255,255,  0,  0,128,225,127, 30, 12, 12, 12, 12, 12, 12, 12, 13,141,207,239,255,127, 63, 15,  3,  0,  0,128,224,248,255, 63, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  3,  7, 15, 62,124,248,240,224,192,128,  1,  3,  7, 15, 30, 28, 60, 56,120,112,112,224,224,225,231,254,248,255,255,248,254,231,225,224,224,112,112,120, 56, 60, 28, 30, 15,  7,  3,  1,128,192,224,240,248,124, 62, 15,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  7, 15, 14, 30, 28, 60, 56,120,112,112,112,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,112,112,112,120, 56, 60, 28, 30, 14, 15,  7,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
        };
        // clang-format on
        oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
    }
    return false;
}
#endif

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {

    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        // Page up/Page down
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    return false;
}
#endif
