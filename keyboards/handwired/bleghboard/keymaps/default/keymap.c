#include "../../bleghboard.h"

#define _______ KC_TRNS
#define XXXXXXX KC_NO

#define L_QWERTY 0

#define ESC_CTL LCTL_T(KC_ESC)

enum keycodes {
    QWERTY = SAFE_RANGE,
    LOWER,
    // UPPER,
};

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
    switch (keycode) {
        default:
            return true;
    }
}

void matrix_scan_user(void) {
}

void matrix_init_user(void) {
}
