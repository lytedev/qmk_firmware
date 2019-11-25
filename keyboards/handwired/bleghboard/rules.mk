MCU = atmega32u4
F_CPU = 8000000
F_USB = $(F_CPU)
ARCH = AVR8
USE_FPU = yes
# BOOTLOADER = atmel-dfu
BOOTLOADER = caterina

# ADAFRUIT_BLE_ENABLE ?= yes
# BLUETOOTH ?= AdafruitBLE
# BLUETOOTH_ENABLE ?= yes
# TAP_DANCE_ENABLE ?= yes
# BACKLIGHT_ENABLE ?= no              # enable keyboard backlight functionality
# BOOTMAGIC_ENABLE ?= no              # virtual DIP switch configuration
# MOUSEKEY_ENABLE ?= yes              # mouse keys
# EXTRAKEY_ENABLE ?= yes              # audio and system control
# CONSOLE_ENABLE ?= yes               # console for debug
# COMMAND_ENABLE ?= yes               # commands for debug and configuration
# SLEEP_LED_ENABLE ?= no              # breathing sleep LED during USB suspend
# NKRO_ENABLE ?= yes                  # USB nkey rollover
# AUDIO_ENABLE ?= no                  # audio output on port C6
# NO_USB_STARTUP_CHECK ?= no          # disable initialization only on usb

# RAW_ENABLE ?= yes
# DYNAMIC_KEYMAP_ENABLE ?= no
# CIE1931_CURVE ?= yes
