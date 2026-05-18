// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
  _BASE = 0,
  _WIN,
  _SYM,
  _NAV,
  _NUM,
  _ADJ,
};

/*
 * =============
 * Home row mods
 * =============
 */

// Left-hand home row mods (MacOS)
#define HR_A LCTL_T(KC_A)
#define HR_S LALT_T(KC_S)
#define HR_D LGUI_T(KC_D)
#define HR_F LSFT_T(KC_F)

// Right-hand home row mods (MacOS)
#define HR_J RSFT_T(KC_J)
#define HR_K RGUI_T(KC_K)
#define HR_L LALT_T(KC_L)
#define HR_SCLN RCTL_T(KC_SCLN)

// Left-hand home row mods (Windows)
#define HRW_A LGUI_T(KC_A)
#define HRW_S LALT_T(KC_S)
#define HRW_D LCTL_T(KC_D)
#define HRW_F LSFT_T(KC_F)

// Right-hand home row mods (Windows)
#define HRW_J RSFT_T(KC_J)
#define HRW_K RCTL_T(KC_K)
#define HRW_L LALT_T(KC_L)
#define HRW_SCLN RGUI_T(KC_SCLN)

// clang-format off
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
  LAYOUT(
    'L', 'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R', 'R',
    'L', 'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R', 'R',
    'L', 'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R', 'R',
    'L', 'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R', 'R',
                   'L', 'L', 'L',  'R', 'R', 'R'
  );
// clang-format on

/*
 * =========
 * Tap dance
 * =========
 */

enum {
  TD_CAPS,
  TD_NUMS,
};

void td_caps_finished(tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    set_oneshot_mods(MOD_LSFT);
  } else if (state->count >= 2) {
    caps_word_toggle();
  }
}

void td_nums_finished(tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    set_oneshot_mods(MOD_LSFT);
  } else if (state->count >= 2) {
    layer_invert(3);
  }
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_CAPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_caps_finished, NULL),
    [TD_NUMS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_nums_finished, NULL)};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // Base qwerty layer
  [_BASE] = LAYOUT(
    MO(_ADJ), KC_1, KC_2, KC_3, KC_4,        KC_5,                       KC_6,     KC_7, KC_8,    KC_9,   KC_0,    KC_EQUAL,
    KC_TAB,   KC_Q, KC_W, KC_E, KC_R,        KC_T,                       KC_Y,     KC_U, KC_I,    KC_O,   KC_P,    KC_BSPC,
    KC_ESC,   HR_A, HR_S, HR_D, HR_F,        KC_G,                       KC_H,     HR_J, HR_K,    HR_L,   HR_SCLN, KC_QUOT,
    KC_LSFT,  KC_Z, KC_X, KC_C, KC_V,        KC_B,                       KC_N,     KC_M, KC_COMM, KC_DOT, KC_SLSH, TD(TD_CAPS),
                                TD(TD_NUMS), MO(_NAV), KC_SPC,   KC_ENT, MO(_SYM), KC_NO
  ),

  [_WIN] = LAYOUT(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
    KC_TRNS, HRW_A,   HRW_S,   HRW_D,   HRW_F,   KC_TRNS,                     KC_TRNS, HRW_J,   HRW_K,   HRW_L,   HRW_SCLN, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
                                        KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS
  ),

  // Symbol Layer
  [_SYM] = LAYOUT(
    KC_TRNS, KC_F1,      KC_F2,          KC_F3,      KC_F4,          KC_F5,                       KC_F6,      KC_F7,         KC_F8,          KC_F9,          KC_F10,         KC_F11,
    KC_TRNS, KC_GRV,     LSFT(KC_GRV),   KC_HASH,    LSFT(KC_7),     KC_PIPE,                     LSFT(KC_6), LSFT(KC_LBRC), LSFT(KC_RBRC),  LSFT(KC_MINUS), LSFT(KC_QUOTE), KC_DEL,
    KC_TRNS, LSFT(KC_1), LSFT(KC_MINUS), KC_LBRC,    KC_RBRC,        KC_DOLLAR,                   LSFT(KC_2), LSFT(KC_9),    LSFT(KC_0),     KC_EQUAL,       KC_COLON,       KC_TRNS,
    KC_TRNS, KC_PERCENT, LSFT(KC_SLASH), LSFT(KC_8), LSFT(KC_EQUAL), KC_BSLS,                     KC_SLSH,    KC_MINUS,      LSFT(KC_COMMA), LSFT(KC_DOT),   KC_QUOTE,       KC_TRNS,
                                                     KC_TRNS,        KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS,    KC_TRNS
  ),

  // Nav Layer
  [_NAV] = LAYOUT(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,
    KC_TRNS, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                        KC_6,    KC_7,    KC_8,    KC_9,     KC_0,    KC_BSPC,
    KC_TRNS, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, KC_NO,                       KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_CAPS, KC_TRNS,
    KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                       KC_HOME, KC_PGDN, KC_PGUP, KC_END,   KC_INS,  KC_TRNS,
                                        KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS
  ),

  // Number Layer
  [_NUM] = LAYOUT(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    KC_TRNS, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, KC_NO,                       KC_0,    KC_4,    KC_5,    KC_6,    KC_NO,   KC_TRNS,
    KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                       KC_0,    KC_1,    KC_2,    KC_3,    KC_NO,   KC_TRNS,
                                        KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS
  ),

  // Adjustment Layer
  [_ADJ] = LAYOUT(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                     KC_TRNS,    KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                     PDF(_BASE), PDF(_WIN), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                     RM_TOGG,    RM_SATU,   RM_HUEU, RM_VALU, RM_NEXT, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                     KC_TRNS,    RM_SATD,   RM_HUED, RM_VALD, RM_PREV, KC_TRNS,
                                        KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS,    KC_TRNS
  )
};
