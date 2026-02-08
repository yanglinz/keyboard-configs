// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Left-hand home row mods
#define HOME_A LGUI_T(KC_A)
#define HOME_S LALT_T(KC_S)
#define HOME_D LCTL_T(KC_D)
#define HOME_F LSFT_T(KC_F)

// Right-hand home row mods
#define HOME_J RSFT_T(KC_J)
#define HOME_K RCTL_T(KC_K)
#define HOME_L LALT_T(KC_L)
#define HOME_SCLN RGUI_T(KC_SCLN)

// Tap dance
enum {
    TD_CAPS,
    TD_NUMS,
};

void td_caps_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        set_oneshot_mods(MOD_LSFT);
        oneshot_mods_changed_key(KC_LSFT, MOD_LSFT);
    } else if (state->count >= 2) {
        caps_word_toggle();
    }
}

void td_nums_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        set_oneshot_mods(MOD_LSFT);
        oneshot_mods_changed_key(KC_LSFT, MOD_LSFT);
    } else if (state->count >= 2) {
        layer_invert(3);
    }
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_CAPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_caps_finished, NULL),
    [TD_NUMS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_nums_finished, NULL)
};

const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    LAYOUT(
        'L', 'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R', 'R',
                       'L', 'L', 'L',  'R', 'R', 'R'
    );

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Base Layer
    [0] = LAYOUT(
        KC_GRAVE, KC_1,   KC_2,   KC_3,   KC_4,        KC_5,                             KC_6,  KC_7,        KC_8,    KC_9,   KC_0,      KC_EQUAL,
        KC_TAB,   KC_Q,   KC_W,   KC_E,   KC_R,        KC_T,                             KC_Y,  KC_U,        KC_I,    KC_O,   KC_P,      KC_BSPC,
        KC_ESC,   HOME_A, HOME_S, HOME_D, HOME_F,      KC_G,                             KC_H,  HOME_J,      HOME_K,  HOME_L, HOME_SCLN, KC_QUOT,
        KC_LSFT,  KC_Z,   KC_X,   KC_C,   KC_V,        KC_B,                             KC_N,  KC_M,        KC_COMM, KC_DOT, KC_SLSH,   TD(TD_CAPS),
                                          TD(TD_CAPS), LT(2, KC_TAB), KC_SPC,    KC_ENT, MO(1), TD(TD_NUMS)
    ),

    // Symbol Layer
    [1] = LAYOUT(
        KC_TRNS, KC_F1,      KC_F2,          KC_F3,      KC_F4,          KC_F5,                               KC_F6,      KC_F7,         KC_F8,          KC_F9,          KC_F10,         KC_F11,
        KC_TRNS, KC_GRV,     LSFT(KC_GRV),   KC_HASH,    LSFT(KC_7),     KC_PIPE,                             LSFT(KC_6), LSFT(KC_LBRC), LSFT(KC_RBRC),  KC_LBRC,        KC_RBRC,        KC_DEL,
        KC_TRNS, LSFT(KC_1), LSFT(KC_MINUS), KC_COLON,   KC_EQUAL,       KC_DOLLAR,                           LSFT(KC_2), LSFT(KC_9),    LSFT(KC_0),     LSFT(KC_MINUS), KC_SCLN,        KC_TRNS,
        KC_TRNS, KC_PERCENT, LSFT(KC_SLASH), LSFT(KC_8), LSFT(KC_EQUAL), KC_BSLS,                             KC_SLSH,    KC_MINUS,      LSFT(KC_COMMA), LSFT(KC_DOT),   LSFT(KC_QUOTE), KC_TRNS,
                                                         KC_TRNS,        LT(3, KC_TAB), KC_TRNS,     KC_TRNS, KC_TRNS,    KC_TRNS
    ),

    // Nav and Media Layer
    [2] = LAYOUT(
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                    KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS, TT(4),
        KC_TRNS,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                      KC_AGAIN, KC_PASTE, KC_COPY, KC_CUT,   KC_UNDO, KC_DEL,
        KC_TRNS,  KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, KC_NO,                      KC_LEFT,  KC_DOWN,  KC_UP,   KC_RIGHT, KC_CAPS, KC_TRNS,
        KC_TRNS,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                      KC_HOME,  KC_PGDN,  KC_PGUP, KC_END,   KC_INS,  KC_TRNS,
                                             KC_TRNS, KC_TRNS, KC_SPC,    KC_ENT, MO(3),    KC_TRNS
    ),

    // Number Layer
    [3] = LAYOUT(
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,                    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,  KC_NO,   KC_NO,   KC_NO,   KC_NO,     KC_NO,                      KC_NO,   KC_7,    KC_8,    KC_9,    KC_UNDO, KC_TRNS,
        KC_TRNS,  KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT,   KC_NO,                      KC_0,    KC_4,    KC_5,    KC_6,    KC_CAPS, KC_TRNS,
        KC_TRNS,  KC_NO,   KC_NO,   KC_NO,   KC_NO,     KC_NO,                      KC_NO,   KC_1,    KC_2,    KC_3,    KC_INS,  KC_TRNS,
                                             KC_TRNS,   KC_TRNS, KC_SPC,    KC_ENT, KC_TRNS, KC_TRNS
    ),

    // Gaming Layer
    [4] = LAYOUT(
        KC_ESC,  KC_1, KC_2, KC_3, KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,   KC_0,    TT(4),
        KC_TAB,  KC_Q, KC_W, KC_E, KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,    KC_TRNS,
        KC_LSFT, KC_A, KC_S, KC_D, KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,   KC_SCLN, KC_QUOT,
        KC_LCTL, KC_Z, KC_X, KC_C, KC_V,    KC_B,                      KC_N,    KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
                                   KC_TRNS, KC_SPC, KC_SPC,    KC_ENT, KC_TRNS, KC_TRNS
    )
};
