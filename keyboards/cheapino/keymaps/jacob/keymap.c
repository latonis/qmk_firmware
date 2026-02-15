/* SPDX-License-Identifier: GPL-2.0-or-later */
#include QMK_KEYBOARD_H

#if __has_include("keymap.h")
#    include "keymap.h"
#endif

uint8_t get_hue(uint8_t layer) {
    switch (layer) {
        case 0:
            return 43;   // Yellow
        case 1:
            return 170;  // Blue
        case 2:
            return 85;    // Red
        default:
            return 0;    // Default to off/black (hue doesn't matter if sat/val are 0)
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t hue = get_hue(get_highest_layer(state));
    rgblight_sethsv(hue, 255, 60);
    return state;
}

// Custom macro definitions
enum custom_keycodes {
    M0 = SAFE_RANGE,  // LCtrl+LGui+Left
    M1                 // LCtrl+LGui+Right
};

// Layer declarations
enum layers {
    L_BASE = 0,
    L_1,
    L_2,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case M0:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                register_code(KC_LGUI);
                register_code(KC_LEFT);
            } else {
                unregister_code(KC_LCTL);
                unregister_code(KC_LGUI);
                unregister_code(KC_LEFT);
            }
            return false;

        case M1:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                register_code(KC_LGUI);
                register_code(KC_RIGHT);
            } else {
                unregister_code(KC_LCTL);
                unregister_code(KC_LGUI);
                unregister_code(KC_RIGHT);
            }
            return false;
    }
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x5_3(KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P,
                             KC_A, KC_S, KC_D, KC_F, MT(MOD_LSFT, KC_G), MT(MOD_LSFT, KC_H), KC_J, KC_K, KC_L, KC_SCLN,
                             KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_ENT,
                             MO(1), KC_BSPC, KC_LGUI, KC_RCTL, KC_SPC, MO(2)),
    [1] = LAYOUT_split_3x5_3(KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0,
                             M0, KC_NO, KC_NO, M1, KC_LSFT, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_DQUO,
                             KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_QUES,
                             KC_LGUI, KC_SPC, KC_TRNS, MO(3), KC_ENT, KC_RALT),
    [2] = LAYOUT_split_3x5_3(KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
                             KC_TAB, KC_NO, KC_NO, KC_DQUO, KC_SLSH, KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,
                             KC_ESC, KC_NO, KC_NO, KC_NO, KC_NO, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_LGUI, KC_SPC, MO(3), KC_TRNS, KC_ENT, KC_RALT),
};




#ifdef OTHER_KEYMAP_C
#    include OTHER_KEYMAP_C
#endif // OTHER_KEYMAP_C
