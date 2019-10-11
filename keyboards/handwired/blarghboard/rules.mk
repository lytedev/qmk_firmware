MCU = atmega32u4
ARCH = AVR8
F_CPU = 8000000
F_USB = $(F_CPU)
USE_FPU = yes
BOOTLOADER = caterina
OPT_DEFS += -DINTERRUPT_CONTROL_ENDPOINT

BLUETOOTH_ENABLE ?= yes
ADAFRUIT_BLE_ENABLE ?= yes
BLUETOOTH ?= AdafruitBLE

BACKLIGHT_ENABLE ?= no              # enable keyboard backlight functionality
BOOTMAGIC_ENABLE ?= no              # virtual DIP switch configuration
MOUSEKEY_ENABLE ?= no               # mouse keys
EXTRAKEY_ENABLE ?= yes              # audio and system control
CONSOLE_ENABLE ?= no                # console for debug
COMMAND_ENABLE ?= no                # commands for debug and configuration
SLEEP_LED_ENABLE ?= no              # breathing sleep LED during USB suspend
NKRO_ENABLE ?= no                   # USB nkey rollover
AUDIO_ENABLE ?= no                  # audio output on port C6
NO_USB_STARTUP_CHECK ?= no          # disable initialization only on usb
