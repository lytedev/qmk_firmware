#pragma once

#include "config_common.h"

#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x1337
#define DEVICE_VER      0x0001
#define MANUFACTURER    lytedev
#define PRODUCT         bleghboard
#define DESCRIPTION     A BLE split, orthlinear keyboard

#define MATRIX_ROWS 5
#define MATRIX_COLS 6

// TODO: IO expander?

/* keyboard matrix assignments
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 */
#define MATRIX_ROW_PINS { B7, B6, B5, D7, C6 }
#define MATRIX_COL_PINS { F7, F6, F5, F4, F1, F0 }
#define UNUSED_PINS

/* COL2ROW | ROW2COL
 * COL2ROW = COL = anode (+), ROW = cathode (-, marked on diode)
 * ROW2COL = ROW = anode (+), COL = cathode (-, marked on diode)
 */
#define DIODE_DIRECTION COL2ROW

// Turn off the mode leds on the BLE module
#define ADAFRUIT_BLE_ENABLE_MODE_LEDS 0
#define ADAFRUIT_BLE_ENABLE_POWER_LED 0

/* debounce
 * set 0 if debouncing is not needed
 */
#define DEBOUNCE 0

/* mechanical locking support
 * Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap
 */
#define LOCKING_SUPPORT_ENABLE

/* locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#undef TAPPING_TOGGLE
#define TAPPING_TOGGLE 2
