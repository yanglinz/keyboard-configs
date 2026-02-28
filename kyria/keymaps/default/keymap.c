#include QMK_KEYBOARD_H

enum layers {
    _BASE = 0,
    _SYM,
    _NAV,
    _NUM,
    _ADJ,
};

// Left-hand home row mods
#define HR_A LGUI_T(KC_A)
#define HR_S LALT_T(KC_S)
#define HR_D LCTL_T(KC_D)
#define HR_F LSFT_T(KC_F)

// Right-hand home row mods
#define HR_J RSFT_T(KC_J)
#define HR_K RCTL_T(KC_K)
#define HR_L LALT_T(KC_L)
#define HR_SCLN RGUI_T(KC_SCLN)

const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    LAYOUT(
        'L', 'L', 'L', 'L', 'L', 'L',                       'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L',                       'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L',   'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R',
                       'L', 'L', 'L', 'L', 'L',   'R', 'R', 'R', 'R', 'R'
    );

// todo:
// 1. port base layer
// -. port hmr
// -. port tap dance
// 2. port symbol layer
// 3. port nav layer
// 4. implement image gen
// 5. implement auto formatting
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
    KC_TAB,  KC_Q, KC_W, KC_E, KC_R,     KC_T                                                         KC_Y,        KC_U,  KC_I,    KC_O,   KC_P,    KC_BSPC,
    KC_ESC,  HR_A, HR_S, HR_D, HR_F,     KC_G                                                         KC_H,        HR_J,  HR_K,    HR_L,   HR_SCLN, KC_QUOT,
    KC_LSFT, KC_Z, KC_X, KC_C, KC_V,     KC_B,  KC_NO,      KC_NO,                  KC_NO,  KC_NO,    KC_N,        KC_M,  KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
                               MO(_ADJ), KC_NO, TD(TD_NUM), MO(_NAV), KC_SPC        KC_ENT, MO(_SYM), TD(TD_CAPS), KC_NO, KC_NO
    ),

    /*
    [_SYM] = LAYOUT(
    // Symbol layer
    KC_GRV ,   KC_1 ,   KC_2 ,   KC_3 ,   KC_4 ,   KC_5 ,                                      KC_6 ,   KC_7 ,   KC_8 ,   KC_9 ,   KC_0 , KC_EQL ,
    KC_TILD , KC_EXLM,  KC_AT , KC_HASH,  KC_DLR, KC_PERC,                                     KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PLUS,
    KC_PIPE , KC_BSLS, KC_COLN, KC_SCLN, KC_MINS, KC_LBRC, KC_LCBR, _______, _______, KC_RCBR, KC_RBRC, KC_UNDS, KC_COMM,  KC_DOT, KC_SLSH, KC_QUES,
                                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_NAV] = LAYOUT(
    // Navigation layer
    _______, _______, _______, _______, _______, _______,                                     KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_VOLU, KC_DEL,
    _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______,                                     KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_VOLD, KC_INS,
    _______, _______, _______, _______, _______, _______, _______, KC_SCRL, _______, _______,KC_PAUSE, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_PSCR,
                               _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_ADJ] = LAYOUT(
    // Adjustment layer
    _______, _______, _______, _______, _______, _______,                                    _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,                                    RM_TOGG, RM_SATU, RM_HUEU, RM_VALU, RM_NEXT, _______,
    _______, _______, _______, _______, _______, _______,_______, _______, _______, _______, _______, RM_SATD, RM_HUED, RM_VALD, RM_PREV, _______,
                               _______, _______, _______,_______, _______, _______, _______, _______, _______, _______
    ),
    */

};
