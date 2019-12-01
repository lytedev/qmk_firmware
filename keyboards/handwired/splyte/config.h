#pragma once

#include "config_common.h"

/* USB device identification parameters */
#define VENDOR_ID 0xFEED
#define PRODUCT_ID 0x0000
#define DEVICE_VER 0x0001
#define MANUFACTURER lytedev
#define PRODUCT Splyteboard
#define DESCRIPTION "Splyteboard"

#define MATRIX_ROWS 5 * 2
#define MATRIX_COLS 6

// TODO: custom matrix
#define MATRIX_ROW_PINS { D6, B7, B6, B5, D7 }
#define MATRIX_COL_PINS { F0, F1, F4, F5, F6, F7 }

#define DIODE_DIRECTION ROW2COL
#define UNUSED_PINS

#define SOFT_SERIAL_PIN D0

#define DEBOUNCE 5

#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE

#define MIDI_ADVANCED
#define MIDI_BASIC

#define MIDI_TONE_KEYCODE_OCTAVES 5

/*
Copyright 2019 Daniel Flanagan

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

