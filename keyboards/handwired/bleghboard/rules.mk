MCU_FAMILY = STM32
MCU_SERIES = STM32F0xx
MCU_LDSCRIPT = STM32F042x6
MCU_STARTUP = stm32f0xx
BOARD = GENERIC_STM32_F042X6
MCU = cortex-m0
F_CPU = 48000000
F_USB = $(F_CPU)
ARMV = 6
ARCH = AVR8
USE_FPU = yes

ADAFRUIT_BLE_ENABLE ?= yes
BLUETOOTH ?= AdafruitBLE
BACKLIGHT_ENABLE ?= no              # enable keyboard backlight functionality
BOOTMAGIC_ENABLE ?= no              # virtual DIP switch configuration
MOUSEKEY_ENABLE ?= yes              # mouse keys
EXTRAKEY_ENABLE ?= yes              # audio and system control
CONSOLE_ENABLE ?= yes               # console for debug
COMMAND_ENABLE ?= yes               # commands for debug and configuration
SLEEP_LED_ENABLE ?= no              # breathing sleep LED during USB suspend
NKRO_ENABLE ?= yes                  # USB nkey rollover
AUDIO_ENABLE ?= no                  # audio output on port C6
NO_USB_STARTUP_CHECK ?= no          # disable initialization only on usb

RAW_ENABLE ?= yes
DYNAMIC_KEYMAP_ENABLE ?= yes
CIE1931_CURVE ?= yes
