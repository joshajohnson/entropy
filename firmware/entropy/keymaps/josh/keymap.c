/* Copyright 2020 joshajohnson
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

#include "muse.h"

// Useability defines
#define ___ KC_NO
#define KC_WRAP KC_F22

// Shorter defs to fit in keymap
#define MO_SPC_LOW LT(_LOWER, KC_SPACE)
#define MT_RA_M1 RALT_T(KC_MS_BTN1)
#define MT_RC_APP RCTL_T(KC_APP)
#define OSL_M OSL(_MACRO)

/* LED control */
uint8_t status_en = 1;

/* Jiggler */
static uint32_t key_timer = 0;
static bool dir = true;
static bool en = false;

/*
Custom codes for layers and keys
*/
enum layer_names {
    _COLEMAK = 0,
    _QWERTY,
    _NORMAL,
    _MACRO,
    _LOWER,
    _RAISE,
    _FN
};

enum custom_codes{
    STAT_EN = SAFE_RANGE,
    UNDER_EN,
    JIGGLER,
    SNDSTRM,
    USSR,
    ALLSTR,
    RCKRLL,
    M_THM,
    M_GMVR,
    M_MSHRM
};

/*
Keymap
*/
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_COLEMAK] = LAYOUT_2U_SS(
    _______,LCTL(KC_W), KC_MUTE, KC_MPLY,  KC_ESC,   KC_F1,    KC_F2,   KC_F3,   KC_F4,  KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,   KC_F11,  KC_F12, KC_INS, KC_DEL,  KC_HOME,  \
    KC_PMNS, KC_PAST,   KC_PSLS,   OSL_M,  KC_GRV,      KC_1,    KC_2,    KC_3,    KC_4,   KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,   KC_MINS,  KC_EQL,    KC_BSPC,    KC_PGUP,  \
               KC_P7,     KC_P8,   KC_P9,  KC_TAB,        KC_Q,    KC_W,    KC_F,    KC_P,   KC_G,    KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN,   KC_LBRC, KC_RBRC,  KC_BSLS,    KC_PGDN,  \
    KC_PPLS,   KC_P4,     KC_P5,   KC_P6, KC_BSPC,         KC_A,    KC_R,   KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,   KC_QUOT,          KC_ENT,     KC_END,  \
               KC_P1,     KC_P2,   KC_P3, KC_LSFT,           KC_Z,    KC_X,  KC_C,    KC_V,    KC_B,    KC_K,    KC_M,  KC_COMM,   KC_DOT, KC_SLSH,       KC_RSFT,    KC_UP,    MO(_FN),  \
    KC_PENT, KC_PDOT,        KC_P0,       KC_LCTL,  KC_LGUI,    KC_LALT,          MO_SPC_LOW,    KC_SPC,          MO(_RAISE),        MT_RA_M1,   MT_RC_APP,  KC_LEFT, KC_DOWN, KC_RIGHT
),

    [_QWERTY] = LAYOUT_2U_SS(
    _______, _______, _______, _______,  KC_ESC,   KC_F1,    KC_F2,   KC_F3,   KC_F4,  KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,   KC_F11,  KC_F12, KC_INS, KC_DEL,  KC_HOME,  \
    KC_PMNS, KC_PAST, KC_PSLS,   OSL_M,  KC_GRV,      KC_1,    KC_2,    KC_3,    KC_4,   KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,   KC_MINS,  KC_EQL,    KC_BSPC,    KC_PGUP,  \
               KC_P7,   KC_P8,   KC_P9,  KC_TAB,        KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,   KC_LBRC, KC_RBRC,  KC_BSLS,    KC_PGDN,  \
    KC_PPLS,   KC_P4,   KC_P5,   KC_P6,  KC_BSPC,         KC_A,    KC_S,   KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,  KC_SCLN,   KC_QUOT,         KC_ENT,     KC_END,  \
               KC_P1,   KC_P2,   KC_P3,  KC_LSFT,           KC_Z,    KC_X,  KC_C,    KC_V,    KC_B,    KC_N,    KC_M,  KC_COMM,   KC_DOT, KC_SLSH,       KC_RSFT,    KC_UP,    MO(_FN),  \
    KC_PENT, KC_PDOT,      KC_P0,        KC_LCTL,  KC_LGUI,    KC_LALT,          MO_SPC_LOW,    KC_SPC,          MO(_RAISE),        MT_RA_M1,   MT_RC_APP,  KC_LEFT, KC_DOWN, KC_RIGHT
),

    [_NORMAL] = LAYOUT_2U_SS(
    _______, _______, _______, _______,  KC_ESC,   KC_F1,    KC_F2,   KC_F3,   KC_F4,  KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,   KC_F11,  KC_F12, KC_INS, KC_DEL,  KC_HOME,  \
    KC_PMNS, KC_PAST, KC_PSLS, KC_NLCK,  KC_GRV,      KC_1,    KC_2,    KC_3,    KC_4,   KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,   KC_MINS,  KC_EQL,    KC_BSPC,    KC_PGUP,  \
               KC_P7,   KC_P8,   KC_P9,  KC_TAB,        KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,   KC_LBRC, KC_RBRC,  KC_BSLS,    KC_PGDN,  \
    KC_PPLS,   KC_P4,   KC_P5,   KC_P6,  KC_CAPS,         KC_A,    KC_S,   KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,  KC_SCLN,   KC_QUOT,         KC_ENT,     KC_END,  \
               KC_P1,   KC_P2,   KC_P3,  KC_LSFT,           KC_Z,    KC_X,  KC_C,    KC_V,    KC_B,    KC_N,    KC_M,  KC_COMM,   KC_DOT, KC_SLSH,       KC_RSFT,    KC_UP,    MO(_FN),  \
    KC_PENT, KC_PDOT,      KC_P0,        KC_LCTL,  KC_LGUI,    KC_LALT,          KC_SPC,        KC_SPC,            KC_SPC,          KC_RALT,   KC_RCTL,     KC_LEFT, KC_DOWN, KC_RIGHT
),

    [_MACRO] = LAYOUT_2U_SS(
    KC_PSTE, KC_HELP, KC_MENU, KC_SLCT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  \
    _______, _______, _______, KC_STOP, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,     _______,      _______,  \
             _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    _______,   _______,  \
    _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,       _______,      _______,  \
             _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,      _______,     _______, _______,  \
    _______, _______,          _______, _______,   _______,    _______,         _______,       _______,      _______,        _______,              _______,  _______, _______, _______
),

    [_LOWER] = LAYOUT_2U_SS(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  \
    _______, _______, _______, TG(_MACRO), _______, KC_F1,    KC_F2,   KC_F3,   KC_F4,  KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,   KC_F11,  KC_F12,     _______,       _______,  \
             _______, _______, _______,  KC_ESC,     _______, _______, _______, _______, _______, _______, _______, KC_PGDN, KC_PGUP, _______, _______, _______,    _______,   _______,  \
    _______, _______, _______, _______,  KC_DEL,        KC_LEFT, KC_DOWN,  KC_UP, KC_RIGHT, _______, _______,  KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, _______,       _______,     _______,  \
             _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______,  KC_END, KC_HOME, _______, _______,      _______,     _______, _______,  \
    _______, _______,          _______, _______,   _______,    _______,         _______,       _______,      _______,        _______,              _______,  _______, _______, _______
),

    [_RAISE] = LAYOUT_2U_SS(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  \
    _______, _______, _______, KC_CAPS, _______, KC_F1,    KC_F2,   KC_F3,   KC_F4,  KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,   KC_F11,  KC_F12,      _______,      _______,  \
             _______, _______, _______,  KC_ESC,     _______, _______, _______, _______, _______, _______, _______, KC_PGDN, KC_PGUP, _______, _______, _______,    _______,   _______,  \
    _______, _______, _______, _______,  KC_DEL,        KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______, _______, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, _______,        _______,      _______,  \
             _______, _______, _______, _______,          _______, _______, KC_BTN1, KC_BTN2, _______, _______,  KC_END, KC_HOME, _______, _______,      _______,     _______, _______,  \
    _______, _______,          _______, _______,   _______,    _______,         _______,       _______,      _______,        _______,              _______,  _______, _______, _______
),

    [_FN] = LAYOUT_2U_SS(
    JIGGLER, _______, RGB_TOG, STAT_EN,    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   RESET,  \
    CK_DOWN, _______, _______, KC_NLCK, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,     _______,     TG(_QWERTY),  \
              RCKRLL,   M_THM, _______,    _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    _______,  TG(_NORMAL),  \
    CK_UP,      USSR,  M_GMVR, _______,    _______,        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,       _______,      _______,  \
              ALLSTR, M_MSHRM, _______,    _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,      _______,     _______, _______,  \
    CK_TOGG, SNDSTRM,          _______,    _______,   _______,    _______,         _______,       _______,      _______,        _______,              _______,  _______, _______, _______
)

};

/*
Per Key Actions
*/
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint8_t macro_flag;
    switch (keycode) {

    case RESET:
        if (record->event.pressed) {
            rgblight_setrgb(255, 0, 0); // RED underglow when in reset
            rgblight_setrgb_range(0, 0, 0, LED0, LED3+1); // Disable Status LEDs when going into reset
        } else {
        }
        break;

    case STAT_EN:
        if (record->event.pressed) {
            status_en ^=1; // Toggle status enable LEDs
        } else {
        }
        break;

    case RGB_TOG:
        if (record->event.pressed) {
            rgblight_setrgb_range(0, 0, 0, LED0, LED3+1); // Disable Status LEDs when disabling RGB
            return true;
        } else {
        }
        break;

    case JIGGLER:
        if (record->event.pressed) {
            en ^= 1;
            if (en){
                rgblight_setrgb_at(64, 64, 64, LED2);
            } else {
                rgblight_setrgb_at(0, 0, 0, LED2);
            }
            return true;
        } else {
        }
        break;
    }

    // Macro mode for numpad when on _MACRO layer
    if (IS_LAYER_ON(_MACRO) || macro_flag){

        switch (keycode){

        case KC_PSLS ... KC_PDOT:
        case KC_EXEC ... KC_PSTE:
            if (record->event.pressed) {
                register_code(KC_WRAP);
                macro_flag = 1;
                return true;
                break;
            } else {
                unregister_code(keycode);
                unregister_code(KC_WRAP);
                macro_flag = 0;
                return false;
                break;
            }
        }

    }
    return true;
}

/*
D

Default:
Enc 0: Disabled
Enc 1: Scroll Up / Down
Enc 2: Volume up / down / mute
Enc 3: Media next / prev / play-pause

When on _FN
Enc 0: Hue
Enc 1: Saturation
Enc 2: Brightness
Enc 3: LED Mode / enable
*/
void encoder_update_user(uint8_t index, bool clockwise) {
    if (IS_LAYER_ON(_FN)){
        if (index == 0) {
            if (clockwise) {
                rgblight_increase_hue_noeeprom();
            } else {
                rgblight_decrease_hue_noeeprom();
            }
        } else if (index == 1) {
            if (clockwise) {
                rgblight_increase_sat_noeeprom();
            } else {
                rgblight_decrease_sat_noeeprom();
            }
        } else if (index == 2) {
            if (clockwise) {
                rgblight_increase_val_noeeprom();
            } else {
                rgblight_decrease_val_noeeprom();
            }
        } else if (index == 3) {
            if (clockwise) {
                rgblight_step();
            } else {
                rgblight_step_reverse();
            }
        } else if (index == 4) {
            // if (clockwise) {
            //     tap_code(KC_MNXT);
            // } else {
            //     tap_code(KC_MPRV);
            // }
        }
    } else if (IS_LAYER_ON(_MACRO)){
        if (index == 0) {
            if (clockwise) {
                register_code(KC_WRAP);
                tap_code(KC_A);
                unregister_code(KC_WRAP);
            } else {
                register_code(KC_WRAP);
                tap_code(KC_B);
                unregister_code(KC_WRAP);
            }
        } else if (index == 1) {
            if (clockwise) {
                register_code(KC_WRAP);
                tap_code(KC_C);
                unregister_code(KC_WRAP);
            } else {
                register_code(KC_WRAP);
                tap_code(KC_D);
                unregister_code(KC_WRAP);
            }
        } else if (index == 2) {
            if (clockwise) {
                register_code(KC_WRAP);
                tap_code(KC_E);
                unregister_code(KC_WRAP);
            } else {
                register_code(KC_WRAP);
                tap_code(KC_F);
                unregister_code(KC_WRAP);
            }
        } else if (index == 3) {
             if (clockwise) {
                register_code(KC_WRAP);
                tap_code(KC_G);
                unregister_code(KC_WRAP);
            } else {
                register_code(KC_WRAP);
                tap_code(KC_H);
                unregister_code(KC_WRAP);
            }
        } else if (index == 4) {
            // if (clockwise) {
            //     register_code(KC_WRAP);
            //     tap_code(KC_A);
            //     unregister_code(KC_WRAP);
            // } else {
            //     register_code(KC_WRAP);
            //     tap_code(KC_B);
            //     unregister_code(KC_WRAP);
            // }
        }
    }   else {
            if (index == 0) {
            // if (clockwise) {
            //     tap_code(KC_WH_D);
            // } else {
            //     tap_code(KC_WH_U);
            // }
        } else if (index == 1) {
            if (clockwise) {
                // Normal scroll is too slow, so 3x?
                tap_code(KC_WH_D);
                tap_code(KC_WH_D);
                tap_code(KC_WH_D);
            } else {
                tap_code(KC_WH_U);
                tap_code(KC_WH_U);
                tap_code(KC_WH_U);
            }
        } else if (index == 2) {
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
        } else if (index == 3) {
            if (clockwise) {
                tap_code(KC_MNXT);
            } else {
                tap_code(KC_MPRV);
            }
        } else if (index == 4) {
            // if (clockwise) {
            //     tap_code(KC_MNXT);
            // } else {
            //     tap_code(KC_MPRV);
            // }
        }
    }
}

/*
LED CONTROL

LED 0 shows keyboard layout
OFF:    COLEMAK
RED:    NORMAL
GREEN:  QWERTY
BLUE:   MACRO

LED 1 shows temp layers
OFF:    NO MOD
RED:    FN
GREEN:  RAISE
BLUE:   LOWER

LED 2 is currently not configured

LED 3 shows caps / num / scroll lock
OFF:    NUM LOCK (enabled by default)
RED:    CAPS LOCK
GREEN:  NUM LOCK DISABLED
BLUE:   SCROLL LOCK
*/
void matrix_init_user(void) {
    rgblight_set_effect_range(0, 16); // Only use the first 16 LEDs for underglow
}

layer_state_t layer_state_set_user(layer_state_t state) {

    if (status_en) {

        uint8_t normal = 0;
        uint8_t qwerty = 0;
        uint8_t macro = 0;

        if (IS_LAYER_ON(_NORMAL)){
            normal = 255;
        }
        if (IS_LAYER_ON(_QWERTY)){
            qwerty = 255;
        }
        if (IS_LAYER_ON(_MACRO)){
            macro = 255;
        }
        // First LED
        rgblight_setrgb_at(normal, qwerty, macro, LED0);

        // Second LED
        switch (get_highest_layer(state)) {
        case _LOWER:
            rgblight_setrgb_at(0, 0, 255, LED1);
            break;
        case _RAISE:
            rgblight_setrgb_at(0, 255, 0, LED1);
            break;
        case _FN:
            rgblight_setrgb_at(255, 0, 0, LED1);
            break;
        default:
            rgblight_setrgb_at(0, 0, 0, LED1);
            break;
        }
    } else {
        rgblight_setrgb_at(0, 0, 0, LED0);
        rgblight_setrgb_at(0, 0, 0, LED1);
    }

  return state;
};

// Caps / Num / Scroll lock indicator
bool led_update_kb(led_t led_state) {
    // Force caps to on by default
    // Numlock LED will flash for a short time on first boot, disregard it please!
    static bool once = 1;
    if (once && !led_state.num_lock){
        register_code(KC_NUMLOCK);
        unregister_code(KC_NUMLOCK);
        led_state.num_lock = true;
    }
    once = 0;

    if (status_en){

        uint8_t caps = led_state.caps_lock ? 255 : 0;
        uint8_t num = led_state.num_lock ? 0 : 255; // Inverted as Numlock should be on by default
        uint8_t scroll = led_state.scroll_lock ? 255 : 0;

        // Set Last LED
        rgblight_setrgb_at(caps, num, scroll, LED3);
    } else {
        rgblight_setrgb_at(0, 0, 0, LED3);
    }

    return true;
}

/*
Mouse Jiggler
*/
void matrix_scan_user(void) {
    if (timer_elapsed32(key_timer) > 60000) {
        key_timer = timer_read32();
        if (en && dir)
            tap_code(KC_MS_U);
        else if (en && !dir)
            tap_code(KC_MS_D);
        dir ^= 1;
    }
}
