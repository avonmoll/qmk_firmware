OLED_ENABLE = yes
OLED_DRIVER = SSD1306   # Enables the use of OLED displays
ENCODER_ENABLE = yes       # Enables the use of one or more encoders
RGBLIGHT_ENABLE = yes      # Enable keyboard RGB underglow


# Disable unused features
VIA_ENABLE = no
NKRO_ENABLE = no
AUDIO_ENABLE = no
MIDI_ENABLE = no
STENO_ENABLE = no
LEADER_ENABLE = no
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
TERMINAL_ENABLE = no
KEY_LOCK_ENABLE = no
BOOTMAGIC_ENABLE = no
SLEEP_LED_ENABLE = no
TAP_DANCE_ENABLE = no
VELOCIKEY_ENABLE = no
SWAP_HANDS_ENABLE = no
RGB_MATRIX_ENABLE = no
SPACE_CADET_ENABLE = no
WPM_ENABLE = no

KEY_OVERRIDE_ENABLE = yes
UNICODE_ENABLE      = yes

SRC += oneshot.c
