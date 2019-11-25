/* Copyright 2019 Daniel Flanagan
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

#define ESC_CTL LCTL_T(KC_ESC)

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes { QWERTY = SAFE_RANGE, LOWER, UPPER, QMKBEST, QMKURL };

enum custom_layers { L_QWERTY };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [L_QWERTY] = LAYOUT(
        KC_GRV , KC_1   , KC_2 , KC_3  , KC_4, KC_5,
        KC_TAB , KC_Q   , KC_W , KC_E  , KC_R, KC_T,
        ESC_CTL, KC_A   , KC_S , KC_D  , KC_F, KC_G,
        KC_LSFT, KC_A   , KC_S , KC_D  , KC_F, KC_G,
        KC_LALT, KC_LGUI, LOWER, QWERTY
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    /*
    switch (keycode) {
        case QMKBEST:
            if (record->event.pressed) {
                // when keycode QMKBEST is pressed
                SEND_STRING("QMK is the best thing ever!");
            } else {
                // when keycode QMKBEST is released
            }
            break;
        case QMKURL:
            if (record->event.pressed) {
                // when keycode QMKURL is pressed
                SEND_STRING("https://qmk.fm/" SS_TAP(X_ENTER));
            } else {
                // when keycode QMKURL is released
            }
            break;
    }
    */
    return true;
}

void matrix_init_user(void) {}

void matrix_scan_user(void) {}

void led_set_user(uint8_t usb_led) {}
