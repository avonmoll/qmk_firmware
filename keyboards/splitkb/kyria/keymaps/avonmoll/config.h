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

#pragma once

#ifdef RGBLIGHT_ENABLE
#    define RGBLIGHT_ANIMATIONS
#    define RGBLIGHT_HUE_STEP  8
#    define RGBLIGHT_SAT_STEP  8
#    define RGBLIGHT_VAL_STEP  8
// #    define RGBLIGHT_LIMIT_VAL 150 // original
#    define RGBLIGHT_LIMIT_VAL 200	
#    define RGBLIGHT_TIMEOUT_MINS 10
#endif

// Lets you roll mod-tap keys
#define IGNORE_MOD_TAP_INTERRUPT

// If you are using an Elite C rev3 on the slave side, uncomment the lines below:
// #define SPLIT_USB_DETECT
// #define NO_USB_STARTUP_CHECK

// Needed because my encoders are flipped
// see https://docs.qmk.fm/#/feature_encoders
#define ENCODER_DIRECTION_FLIP

// Needed because encoders are skipping every other actuation
// see https://docs.splitkb.com/hc/en-us/articles/360011068659-My-encoder-is-skipping-actions-when-turning-it
#define ENCODER_RESOLUTION 2
