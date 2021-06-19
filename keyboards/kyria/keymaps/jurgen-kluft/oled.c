// [OLED Configuration] ---------------------------------------------//
#include QMK_KEYBOARD_H
#include "oled.h"
#include "layers.h"

// Draw
//static const char PROGMEM skeeb_logo[] = {    
//0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
//0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
//0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,
//0x95,0x96,0x97,0x98,0x99,0x9a,0x9b,0xb5,0xb6,0xb7,0xb8,0xb9,0xba,0xbb,0xd5,0xd6,0xd7,0xd8,0xd9,0xda,0xdb,0};

static const char PROGMEM oled_header[] = {    
0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
0xc0,0};

static const char PROGMEM oled_layer_keylog_separator[] = { 0xc8,0xff,0};
        
static const char PROGMEM oled_layer_line_end[] = { 0xd4,0};

static const char PROGMEM oled_layer_keylog_bottom[] = {    
0xc1,0xc7,0xc7,0xc7,0xc7,0xc7,0xc7,0xc7,0xc7,0xc3,0xc7,0xc7,0xc7,0xc7,0xc7,0xc7,0xc7,0xc7,0xc7,0xc7,0xc2,0};

static const char PROGMEM oled_line_start[] = { 0xc0,0};

static const char PROGMEM oled_mods_bottom[] = {    
0xc1,0xc7,0xc7,0xc7,0xc7,0xc7,0xc7,0xc7,0xc7,0xc7,0xc7,0xc7,0xc7,0xc7,0xc7,0xc7,0xc7,0xc7,0xc7,0xc7,0xc2,0};

static const char PROGMEM oled_footer[] = {    
0xc4,0xc5,0xc5,0xc9,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xcb,0xc5,0xc5,0xc6,0};


static bool s_display_clear = false;
static bool s_display_enabled = false;
void toggle_display_oled(void) {
    s_display_enabled = !s_display_enabled;
    if (!s_display_enabled) {
        s_display_clear = true;
    }
}

void render_skeeb_logo(void) {
    static const char PROGMEM skeeb_logo[] = {
        // 'slave', 128x64px
        0x00, 0xc0, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 
        0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfc, 0xf8, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x60, 0x60, 0x98, 0x98, 0x06, 0x06, 0x00, 0x00, 0x1e, 
        0x1e, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0xfe, 0xfe, 0x00, 0x00, 0xfe, 0xfe, 0x18, 0x18, 0x06, 
        0x06, 0x06, 0x06, 0x18, 0x18, 0x00, 0x00, 0x06, 0x06, 0xfe, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x80, 
        0x80, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0xf8, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0xf8, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x3f, 0x1f, 0x0f, 0x07, 
        0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0xc0, 0x00, 
        0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0f, 0x0f, 0x0f, 0x08, 0x08, 0x08, 0x08, 
        0x08, 0x08, 0x08, 0x08, 0x08, 0x0f, 0x0f, 0x08, 0x08, 0x09, 0x09, 0x0e, 0x0e, 0x08, 0x08, 0x08, 
        0x08, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x09, 0x09, 0x08, 0x08, 0x0f, 0x0f, 0x08, 0x08, 0x08, 
        0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0e, 0x0e, 0x0f, 0x0f, 0x0e, 0x0e, 0x08, 0x08, 0x09, 
        0x09, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0f, 0x0f, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 
        0x08, 0x08, 0x08, 0x08, 0x0f, 0x0f, 0x0f, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 
        0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0x60, 0x30, 0x30, 0x18, 0x98, 0x88, 0x88, 0x88, 0x88, 0x88, 
        0x88, 0x88, 0x88, 0x98, 0x18, 0x30, 0x30, 0x20, 0x60, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 
        0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 
        0xf0, 0x1c, 0x06, 0x83, 0xe1, 0x78, 0xec, 0x66, 0xa3, 0xa3, 0x21, 0x21, 0x78, 0x86, 0x01, 0xff, 
        0x01, 0xc6, 0x38, 0x21, 0xa1, 0xa3, 0x66, 0x6c, 0xf8, 0x70, 0xc1, 0x03, 0x0e, 0x78, 0xe0, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 
        0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 
        0xff, 0x00, 0x00, 0x3f, 0xff, 0xc0, 0xb1, 0x4e, 0x44, 0x24, 0x25, 0x15, 0xd6, 0x3f, 0x0e, 0xff, 
        0x0f, 0x3e, 0xd5, 0x25, 0x24, 0x44, 0x44, 0x9b, 0xe0, 0xc0, 0xff, 0x00, 0x00, 0x80, 0xff, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 
        0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x03, 0x0f, 0x1c, 0x30, 0x61, 0xc3, 0x87, 0x8d, 0x19, 0x31, 0x31, 0x21, 0x63, 0x6c, 0x70, 0x7f, 
        0x70, 0x6c, 0x63, 0x21, 0x31, 0x11, 0x19, 0x8d, 0xc7, 0x63, 0x70, 0x38, 0x0e, 0x07, 0x01, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 
        0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x03, 0x02, 0x06, 0x06, 0x06, 0x06, 0x06, 
        0x06, 0x06, 0x06, 0x02, 0x02, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 
        0x00, 0x03, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xc0, 0xe0, 
        0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 
        0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 
        0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 
        0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 
        0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 
        0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 
        0xe0, 0xc0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x03, 0x00,0
    };
    oled_write_raw_P(skeeb_logo, sizeof(skeeb_logo));
}
	
// Mods Status
void render_mod_status(uint8_t modifiers) {
	oled_write_P(PSTR(" "), false);	
	oled_write_P(PSTR("-"), false);
    oled_write_P(PSTR("SHF"), (modifiers & MOD_MASK_SHIFT));
	oled_write_P(PSTR("-"), false);
    oled_write_P(PSTR("CTR"), (modifiers & MOD_MASK_CTRL));
	oled_write_P(PSTR("-"), false);
	oled_write_P(PSTR("WIN"), (modifiers & MOD_MASK_GUI));
	oled_write_P(PSTR("-"), false);
    oled_write_P(PSTR("ALT"), (modifiers & MOD_MASK_ALT));
    oled_write_P(PSTR("-"), false);
	oled_write_P(PSTR(" "), false);	
}

// Layer State
void render_layer_state(void){
    uint16_t layers = (default_layer_state);
	switch (get_highest_layer(layers)) {
        case _QWERTY:     oled_write_P(PSTR(" QWERTY "), false); break;
        case _RSTHD:      oled_write_P(PSTR(" RSTHD  "), false); break;
		default:          oled_write_P(PSTR(" ?????? "), false); 
	}
}

// Keylock State			
void render_keylock_status(uint8_t led_usb_state) {
	//oled_write_P(led_usb_state & (1<<USB_LED_NUM_LOCK) ? PSTR("-NUML") : PSTR("-----"), false);
	//oled_write_P(PSTR(" "), false);
	//oled_write_P(led_usb_state & (1<<USB_LED_CAPS_LOCK) ? PSTR("-CAPS") : PSTR("-----"), false);
	//oled_write_P(PSTR(" "), false);
	//oled_write_P(led_usb_state & (1<<USB_LED_SCROLL_LOCK) ? PSTR("-SCRL") : PSTR("-----"), false);	
	//oled_write_P(PSTR(" "), false);	

    oled_write_P(PSTR(" "), false);
    // Host Keyboard Layer Status
    uint16_t layers = (layer_state | default_layer_state);
    uint16_t count = 0;
    for (int i = 0; i < 16; i++)
    {
        if ((layers & 1) != 0)
        {
            const uint16_t layer = i;
            if (layer == _RSTHD_CAPS || layer == _QWERTY_CAPS)
            {
                oled_write_P(PSTR("-CAPS "), false);
                count += 1;
            }
            else if (layer == _SYM)
            {
                oled_write_P(PSTR("-SYMB "), false);
                count += 1;
            }
            else if (layer == _NUM)
            {
                oled_write_P(PSTR("-NUMB "), false);
                count += 1;
            }
            else if (layer == _NAV)
            {
                oled_write_P(PSTR("-NAVI "), false);
                count += 1;
            }
            else if (layer == _FNC)
            {
                oled_write_P(PSTR("-FUNC "), false);
                count += 1;
            }
            else if (layer == _MOUS)
            {
                oled_write_P(PSTR("-MOUS "), false);
                count += 1;
            }
            else if (layer == _RAISE)
            {
                oled_write_P(PSTR("-RAIS "), false);
                count += 1;
            }
        }
        layers = layers >> 1;
        if (count == 3)
            break;
    }

    for ( ; count < 3; count++)
    {
	    oled_write_P(PSTR("----- "), false);	
    }
}

// Keylogger
#    define KEYLOGGER_LENGTH 8
static char     keylog_str[KEYLOGGER_LENGTH + 1] = {0};

static const char PROGMEM code_to_name[0xFF] = {
//   0    1    2    3    4    5    6    7    8    9    A    B    c    D    E    F
    182, ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',  // 0x
    'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2',  // 1x
    '3', '4', '5', '6', '7', '8', '9', '0',  20,  19,  17,  29,  22, '-', '=', '[',  // 2x
    ']','\\', '#', ';','\'', '`', ',', '.', '/', 188, 149, 150, 151, 152, 153, 154,  // 3x
    155, 156, 157, 158, 159, 181, 191, 190, ' ', ' ', 185, 183,  16, 186, 184,  26,  // 4x
     27,  25,  24, 189, '/', '*', '-', '+', ' ', '1', '2', '3', '4', '5', '6', '7',  // 5x
    '8', '9', '0', '.', ' ', 187, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 6x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 7x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 8x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 9x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 214, 215, 216, 217, 218, 219, 220, 221,  // Ax
    ' ', ' ', 213, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Bx
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Cx
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Dx
    'C', 'S', 'A', 'W', ' ', 'S', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Ex
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '        // Fx
};

void add_keylog(uint16_t keycode) {
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX) || (keycode >= QK_MODS && keycode <= QK_MODS_MAX)) {
        keycode = keycode & 0xFF;
    } else if (keycode > 0xFF) {
        keycode = 0;
    }

    for (uint8_t i = 1; i < KEYLOGGER_LENGTH; i++) {
        keylog_str[i-1] = keylog_str[i];
    }

    if (keycode < (sizeof(code_to_name) / sizeof(char))) {
        keylog_str[(KEYLOGGER_LENGTH - 1)] = pgm_read_byte(&code_to_name[keycode]);
    }
}

bool process_record_oled(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        add_keylog(keycode);
    }
    return true;
}

void render_keylogger_status(void) {
    oled_write(keylog_str, false);
}

// [OLED Init] ------------------------------------------------------//

// Rotate Screen
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	return OLED_ROTATION_180;
	}

// {OLED Task} ------------------------------------------------------//
void oled_task_user(void) {
    if (!s_display_enabled) {
        if (s_display_clear) {
            for (uint8_t i=0; i<11; i++) {
                oled_write_P(PSTR("                "), false);
            }
            s_display_clear = false;
        }
        return;
    }

    if (is_keyboard_master()) {    // MASTER SIDE
        oled_write_P(oled_header, false);
        render_layer_state();
        oled_write_P(oled_layer_keylog_separator, false);
        render_keylogger_status();	
        oled_set_cursor(20, 2);
        oled_write_P(oled_layer_line_end, false);
        oled_write_P(oled_layer_keylog_bottom, false);
        oled_write_P(oled_line_start, false);
        render_keylock_status(host_keyboard_leds());
        oled_write_P(oled_layer_line_end, false);	
        oled_write_P(oled_mods_bottom, false);
        oled_write_P(oled_line_start, false);
        render_mod_status(get_mods() | get_oneshot_mods()); 
        oled_write_P(oled_layer_line_end, false);
        oled_write_P(oled_footer, false);	
    } else {    // SLAVE SIDE
        render_skeeb_logo();
    } 
}
