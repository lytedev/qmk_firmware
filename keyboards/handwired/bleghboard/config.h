#pragma once

#include "config_common.h"

#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x1337
#define DEVICE_VER      0x0001
#define MANUFACTURER    lytedev
#define PRODUCT         bleghboard
#define DESCRIPTION     Bleghboard

#define MATRIX_ROWS 2
#define MATRIX_COLS 2

// TODO: IO expander?

/* keyboard matrix assignments
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 */
#define MATRIX_ROW_PINS { A0, A1 }
#define MATRIX_COL_PINS { A2, A3 }
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
#define DEBOUNCE 5

/* mechanical locking support
 * Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap
 */
#define LOCKING_SUPPORT_ENABLE

/* locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#undef TAPPING_TOGGLE
#define TAPPING_TOGGLE 2
