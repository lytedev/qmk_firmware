SRC = \
	twi.c \
	matrix.c \
	expander.c \

# MCU: Feather 32u4 Bluefruit LE
# IO Expander: MCP23017

MCU ?= atmega32u4
ARCH ?= AVR8

F_CPU ?= 8000000
F_USB ?= $(F_CPU)

USE_FPU ?= yes

BOOTLOADER ?= caterina

OPT_DEFS += -DINTERRUPT_CONTROL_ENDPOINT

CUSTOM_MATRIX     ?= yes # Custom matrix file for the ErgoDone
BOOTMAGIC_ENABLE  ?= no  # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE   ?= no  # Mouse keys(+4700)
EXTRAKEY_ENABLE   ?= yes # Audio control and System control(+450)
CONSOLE_ENABLE    ?= no  # Console for debug(+400)
COMMAND_ENABLE    ?= no  # Commands for debug and configuration
SLEEP_LED_ENABLE  ?= no  # Breathing sleep LED during USB suspend
NKRO_ENABLE       ?= yes # USB Nkey Rollover
BACKLIGHT_ENABLE  ?= no  # Enable keyboard backlight functionality
RGBLIGHT_ENABLE   ?= no  # Enable keyboard RGB underglow
MIDI_ENABLE       ?= no  # MIDI support (+2400 to 4200, depending on config)
UNICODE_ENABLE    ?= no  # Unicode
BLUETOOTH_ENABLE  ?= yes # Enable Bluetooth with the Adafruit EZ-Key HID
AUDIO_ENABLE      ?= no  # TODO: Audio output on port C6
FAUXCLICKY_ENABLE ?= no  # Use buzzer to emulate clicky switches
HD44780_ENABLE    ?= no  # Enable support for HD44780 based LCDs (+400)

ADAFRUIT_BLE_ENABLE ?= yes
BLUETOOTH ?= AdafruitBLE

SPLIT_KEYBOARD ?= yes

LAYOUTS = splyte
