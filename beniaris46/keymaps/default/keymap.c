// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

//layer declations
enum {
    _BASE,
    _SYMBOL,
    _FN
};

// Tap Dance declarations
enum {
    TD_Q_TAB,
    TD_1_ESC
};


// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Q, twice for tab Lock
    [TD_Q_TAB] = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_TAB),
    [TD_1_ESC] = ACTION_TAP_DANCE_DOUBLE(KC_1, KC_ESC),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT_ortho_5x10(
        TD(TD_1_ESC),  KC_2,    KC_3,     KC_4,     KC_5,                 KC_6,    KC_7,    KC_8,        KC_9,    KC_0,
        KC_Q,          KC_W,    KC_E,     KC_R,     KC_T,                 KC_Y,    KC_U,    KC_I,        KC_O,    KC_P,
        KC_A,          KC_S,    KC_D,     KC_F,     LT(_SYMBOL, KC_G),    KC_H,    KC_J,    KC_K,        KC_L,    KC_SEMICOLON,
        LSFT_T(KC_Z),          KC_X,    KC_C,     KC_V,     KC_B,                 KC_N,    KC_M,    KC_COMMA,    KC_DOT,  KC_SLASH,

        XXXXXXX, XXXXXXX, KC_LCTL, KC_SPC,  LT(_FN, KC_LGUI),          LSFT_T(KC_ENTER), KC_BSPC, MO(_FN),   XXXXXXX,    XXXXXXX
    ),
    [_SYMBOL] = LAYOUT_ortho_5x10(
        KC_TILD,  XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_MINUS,  KC_EQUAL,  KC_DEL,
        KC_TAB,   XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_LBRC,   KC_RBRC,   KC_BACKSLASH,
        XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,   KC_QUOTE,  XXXXXXX,
        KC_LSFT,  XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,   KC_LSFT,

        XXXXXXX,  XXXXXXX,  XXXXXXX, KC_LALT,  XXXXXXX,  KC_LSFT,  XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX
    ),
    [_FN] = LAYOUT_ortho_5x10(
        KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,     KC_F10,
        KC_TAB,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_UP,    XXXXXXX,   KC_DEL,
        KC_LSFT,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_LEFT,  KC_DOWN,  KC_RIGHT,  KC_ENTER,
        KC_LCTL,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_VOLD,  KC_MPLY,  KC_VOLU,   KC_LCTL,
            
        XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_LALT,  XXXXXXX,  XXXXXXX,  KC_BSPC,   XXXXXXX,  XXXXXXX,   XXXXXXX
    )
};      


uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_SPC:
            return TAPPING_TERM + 500;
        case TD(TD_Q_TAB):
            return 200;
        case LSFT_T(KC_ENTER):
            return 125;    
        case LSFT_T(KC_Z):
            return 200;
        case TD(TD_1_ESC):
            return 150;
        case LT(_SYMBOL, KC_G):
            return 175;  // hold for symbol layer, tap for G
        case LT(_FN, KC_LGUI):
            return 150;  // hold for FN layer, tap for GUI
        default:
            return TAPPING_TERM;
    }
}