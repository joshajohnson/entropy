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

#define ___ KC_NO

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN
};

// LED control
uint8_t status_en = 1;

// Custom Keycodes
enum custom_codes{
    STAT_EN = SAFE_RANGE,
    UNDER_EN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_2U(
    _______, _______, _______, _______,  KC_ESC,   KC_F1,    KC_F2,   KC_F3,   KC_F4,  KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,   KC_F11,  KC_F12, KC_INS, KC_DEL,  KC_HOME,  \
    KC_PMNS, KC_PAST, KC_PSLS, KC_NLCK,  KC_GRV,      KC_1,    KC_2,    KC_3,    KC_4,   KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,   KC_MINS,  KC_EQL,      KC_BSPC,  KC_PGUP,  \
               KC_P7,   KC_P8,   KC_P9,  KC_TAB,        KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  KC_LBRC, KC_RBRC,     KC_BSLS,  KC_PGDN,  \
    KC_PPLS,   KC_P4,   KC_P5,   KC_P6,  KC_CAPS,         KC_A,    KC_S,   KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,          KC_ENT,   KC_END,  \
               KC_P1,   KC_P2,   KC_P3,  KC_LSFT,           KC_Z,    KC_X,  KC_C,    KC_V,    KC_B,    KC_N,    KC_M,  KC_COMM,   KC_DOT,   KC_SLSH,     KC_RSFT,      KC_UP,  MO(_FN),  \
    KC_PENT, KC_PDOT,      KC_P0,        KC_LCTL,  KC_LGUI,    KC_LALT,                         KC_SPC,                           KC_RALT,       KC_RCTL,   KC_LEFT, KC_DOWN, KC_RIGHT
),

    [_FN] =     LAYOUT_2U(
    _______, _______, RGB_TOG, STAT_EN, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   RESET,  \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,     _______,      _______,  \
             _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    _______,   _______,  \
    _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,       _______,      _______,  \
             _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,      _______,     _______, _______,  \
    _______, _______,          _______, _______,   _______,    _______,                         _______,                     _______,              _______,  _______, _______, _______
)

};

/*
Per Key Actions
*/
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
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
    }
    return true;
}


/*
Encoder control

Default:
Enc 0: Disabled
Enc 1: Disabled
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
    } else {
            if (index == 0) {
            // if (clockwise) {
            //     tap_code(KC_WH_D);
            // } else {
            //     tap_code(KC_WH_U);
            // }
        } else if (index == 1) {
            if (clockwise) {
                // Normal scroll is too slow, so 2x?
                tap_code(KC_WH_D);
                tap_code(KC_WH_D);
            } else {
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

LEDs shows caps / num / scroll lock
OFF:    Default
RED:    CAPS LOCK
GREEN:  NUM LOCK
BLUE:   SCROLL LOCK
*/

void matrix_init_user(void) {
    rgblight_set_effect_range(0, 16); // Only use the first 16 LEDs for underglow
}

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
        uint8_t num = led_state.num_lock ? 0 : 128; // Inverted as Numlock should be on by default
        uint8_t scroll = led_state.scroll_lock ? 128 : 0;

        // Set Last LED
        rgblight_setrgb_range(caps, num, scroll, LED0, LED3+1);
    } else {
        rgblight_setrgb_range(0, 0, 0, LED0, LED3+1);
    }
    return true;
}
