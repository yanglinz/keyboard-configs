#include QMK_KEYBOARD_H

enum layers {
    _BASE = 0,
    _SYM,
    _NAV,
    _NUM,
    _ADJ,
};

// Left-hand home row mods
#define HR_A LCTL_T(KC_A)
#define HR_S LALT_T(KC_S)
#define HR_D LGUI_T(KC_D)
#define HR_F LSFT_T(KC_F)

// Right-hand home row mods
#define HR_J RSFT_T(KC_J)
#define HR_K RGUI_T(KC_K)
#define HR_L LALT_T(KC_L)
#define HR_SCLN RCTL_T(KC_SCLN)

// clang-format off
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    LAYOUT(
    'L', 'L', 'L', 'L', 'L', 'L',                       'R', 'R', 'R', 'R', 'R', 'R',
    'L', 'L', 'L', 'L', 'L', 'L',                       'R', 'R', 'R', 'R', 'R', 'R',
    'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L',   'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R',
                   'L', 'L', 'L', 'L', 'L',   'R', 'R', 'R', 'R', 'R'
    );
// clang-format on

// todo:
// implement image gen
// implement auto formatting
// layer led
// implement macos vs windows
// https://www.reddit.com/r/ErgoMechKeyboards/comments/1c9satw/whats_your_favorite_productivity_macro/

enum tdance {
    TD_CAPS = 0,
    TD_NUM,
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
        layer_invert(_NAV);
    } else if (state->count >= 2) {
        layer_invert(_NUM);
    }
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_CAPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_caps_finished, NULL),
    [TD_NUM] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_nums_finished, NULL)
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT(
    // Base qwerty layer
    KC_TAB,  KC_Q, KC_W, KC_E,     KC_R,  KC_T,                                                 KC_Y,     KC_U,  KC_I,    KC_O,   KC_P,    KC_BSPC,
    KC_ESC,  HR_A, HR_S, HR_D,     HR_F,  KC_G,                                                 KC_H,     HR_J,  HR_K,    HR_L,   HR_SCLN, KC_QUOT,
    KC_LSFT, KC_Z, KC_X, KC_C,     KC_V,  KC_B,     KC_NO,  KC_NO,         KC_NO,       KC_NO,  KC_N,     KC_M,  KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
                         MO(_ADJ), KC_NO, MO(_NAV), KC_SPC, TD(TD_NUM),    TD(TD_CAPS), KC_ENT, MO(_SYM), KC_NO, KC_NO
    ),

    [_SYM] = LAYOUT(
    // Symbol layer
    KC_TRNS, KC_GRV,     LSFT(KC_GRV),   KC_HASH,    LSFT(KC_7),     KC_PIPE,                                          LSFT(KC_6), LSFT(KC_LBRC), LSFT(KC_RBRC),  KC_LBRC,        KC_RBRC,        KC_DEL,
    KC_TRNS, LSFT(KC_1), LSFT(KC_MINUS), KC_COLON,   KC_EQUAL,       KC_DOLLAR,                                        LSFT(KC_2), LSFT(KC_9),    LSFT(KC_0),     LSFT(KC_MINUS), KC_SCLN,        KC_TRNS,
    KC_TRNS, KC_PERCENT, LSFT(KC_SLASH), LSFT(KC_8), LSFT(KC_EQUAL), KC_BSLS,   KC_TRNS, KC_TRNS,    KC_TRNS, KC_RCBR, KC_SLSH,    KC_MINUS,      LSFT(KC_COMMA), LSFT(KC_DOT),   LSFT(KC_QUOTE), KC_TRNS,
                                         KC_TRNS,    KC_TRNS,        KC_TRNS,   KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),

    [_NAV] = LAYOUT(
    // Navigation layer
    KC_TRNS, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                           KC_6,    KC_7,    KC_8,    KC_9,     KC_0,    KC_DEL,
    KC_TRNS, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, KC_NO,                                          KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_CAPS, KC_TRNS,
    KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,      KC_NO,   KC_NO,   KC_HOME, KC_PGDN, KC_PGUP, KC_END,   KC_INS,  KC_TRNS,
                               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),

    [_NUM] = LAYOUT(
    // Number pad layer
    KC_TRNS, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                           KC_6,    KC_7,    KC_8,    KC_9, KC_0,  KC_DEL,
    KC_TRNS, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, KC_NO,                                          KC_0,    KC_4,    KC_5,    KC_6, KC_NO, KC_TRNS,
    KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,      KC_NO,   KC_NO,   KC_0,    KC_1,    KC_2,    KC_3, KC_NO, KC_TRNS,
                               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),

    [_ADJ] = LAYOUT(
    // Adjustment layer
    _______, _______, _______, _______, _______, _______,                                    _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,                                    RM_TOGG, RM_SATU, RM_HUEU, RM_VALU, RM_NEXT, _______,
    _______, _______, _______, _______, _______, _______,_______, _______, _______, _______, _______, RM_SATD, RM_HUED, RM_VALD, RM_PREV, _______,
                               _______, _______, _______,_______, _______, _______, _______, _______, _______, _______
    ),

};
