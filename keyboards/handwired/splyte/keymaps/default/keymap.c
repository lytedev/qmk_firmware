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

#define XXXXXXX KC_NO
#define _______ KC_TRNS
#define ESC_CTL LCTL_T(KC_ESC)

enum layers { L_QWERTY, L_LEFT, L_RIGHT, L_CONFIG, L_BOTH };

#define TAB_ALT LALT_T(KC_TAB)
#define K_L_L MO(L_LEFT)
#define K_L_R MO(L_RIGHT)
#define K_L_C MO(L_CONFIG)
#define K_L_B MO(L_BOTH)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [L_QWERTY] = LAYOUT(
        KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5     ,  KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_BSPC,
        TAB_ALT, KC_Q   , KC_W   , KC_E   , KC_R   , KC_T     ,  KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSPC,
        ESC_CTL, KC_A   , KC_S   , KC_D   , KC_F   , KC_G     ,  KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B     ,  KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_ENT ,
                          KC_LGUI, KC_SPC , K_L_L  , K_L_C    ,  K_L_C  , KC_LALT, K_L_R  , KC_RALT
    ),

    [L_LEFT] = LAYOUT(
        KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6    ,  KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 ,
        KC_TILD, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC  ,  KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL ,
        KC_DEL , _______, _______, _______, _______, _______  ,  _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
        _______, _______, _______, _______, _______, _______  ,  _______, _______, _______, _______, _______, _______,
                          _______, _______, _______, _______  ,  _______, K_L_B  , K_L_B, _______
    ),

		// the insert key at M's position is for easily inputting Shift+Insert
    [L_RIGHT] = LAYOUT(
        KC_ESC , KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC  ,  KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL ,
        KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5     ,  KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_DEL ,
        KC_GRV , _______, _______, _______, _______, _______  ,  _______, KC_MINS, KC_EQL , KC_LBRC, KC_RBRC, KC_BSLS,
        _______, _______, _______, _______, _______, _______  ,  _______, KC_INS , _______, _______, _______, _______,
                          _______, KC_LALT, K_L_B  , _______  ,  _______, _______, _______, _______
    ),

    [L_CONFIG] = LAYOUT(
        RESET  , _______, _______, _______, _______, _______  ,  _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______  ,  _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______  ,  _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______  ,  _______, _______, _______, _______, _______, _______,
                          _______, _______, _______, _______  ,  _______, _______, _______, _______
    ),

    [L_BOTH] = LAYOUT(
        _______, _______, _______, _______, _______, _______  ,  _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______  ,  KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY, _______, _______,
        _______, _______, _______, _______, _______, _______  ,  KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, _______, _______,
        _______, _______, _______, _______, _______, _______  ,  KC_HOME, KC_PGDN, KC_PGUP, KC_END , _______, _______,
                          _______, _______, _______, _______  ,  _______, _______, _______, _______
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void matrix_init_user(void) {}

void matrix_scan_user(void) {}

void led_set_user(uint8_t usb_led) {}
