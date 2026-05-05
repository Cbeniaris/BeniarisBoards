// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Define encoder button pin
#define ENCODER_BUTTON_PIN F6

// Define layer names
enum layers {
    _MEDIA,
    _CAD,
    _NUM,
};

// Define custom keycodes if needed
enum custom_keycodes {
    LAYER_CYCLE = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_MEDIA] = LAYOUT(
        KC_MUTE, KC_MPRV, KC_MNXT,
        KC_MPLY, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX,
        KC_COPY, KC_PASTE, KC_CUT
    ),

    [_NUM] = LAYOUT(
        KC_P7,   KC_P8,   KC_P9,
        KC_P4,   KC_P5,   KC_P6,
        KC_P1,   KC_P2,   KC_P3,
        KC_P0, KC_PDOT, KC_PENT
    ),

    [_CAD] = LAYOUT(
        KC_0, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX
    )

    

};

// Track current layer
static uint8_t current_layer = 0;

// Rotary encoder - Volume control on base layer, customizable on other layers
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        switch (get_highest_layer(layer_state)) {
            case _NUM:
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
            case _MEDIA:
                // Volume control
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
                break;
            case _CAD:
                // Zoom
                if (clockwise) {
                    tap_code(MS_WHLU);
                } else {
                    tap_code(MS_WHLD);
                }
                break;
        }
    }
    return false;
}

// Handle encoder button press to cycle layers
void encoder_button_handler(void) {
    current_layer = (current_layer + 1) % 3;
    layer_clear();
    layer_on(current_layer);
}

// Matrix scan to check encoder button
// Note: You'll need to wire the encoder button to a specific pin
// Update this pin definition to match your wiring

void matrix_scan_user(void) {
    static bool button_was_pressed = false;
    bool button_pressed = !readPin(ENCODER_BUTTON_PIN);
    
    if (button_pressed && !button_was_pressed) {
        encoder_button_handler();
    }
    button_was_pressed = button_pressed;
}

void keyboard_post_init_user(void) {
    // Set encoder button pin as input with pullup
    setPinInputHigh(ENCODER_BUTTON_PIN);
}

#ifdef OLED_ENABLE

// Helper function to get layer name
const char* get_layer_name(uint8_t layer) {
    switch (layer) {
        case _MEDIA:
            return "Media";
        case _CAD:
            return "CAD";
        case _NUM:
            return "Numpad";
        default:
            return "Media";
    }
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_0;  // Change to 180 if you want to flip the display
}

bool oled_task_user(void) {
    // Display layer information
    oled_write_P(PSTR("Layer: "), false);
    oled_write_ln(get_layer_name(get_highest_layer(layer_state)), false);
    
    oled_write_ln_P(PSTR(""), false);
    oled_write_ln_P(PSTR("Press encoder"), false);
    oled_write_ln_P(PSTR("to switch"), false);
    
    return false;
}

#endif

