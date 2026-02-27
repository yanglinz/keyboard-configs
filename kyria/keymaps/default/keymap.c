#include QMK_KEYBOARD_H

enum layers {
    _BASE = 0,
    _SYM,
    _NAV,
    _NUM,
    _ADJUST,
};

// todo:
// 1. port base layer
// 2. port symbol layer
// 3. port nav layer
// 4. implement image gen
// 5. implement auto formatting

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT(
    // Base qwerty layer
    KC_TAB,  KC_Q ,  KC_W   ,  KC_E  ,   KC_R ,   KC_T ,                                        KC_Y,   KC_U ,  KC_I ,   KC_O ,  KC_P , KC_BSPC,
    KC_ESC,  KC_A ,  KC_S   ,  KC_D  ,   KC_F ,   KC_G ,                                        KC_H,   KC_J ,  KC_K ,   KC_L ,KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z ,  KC_X   ,  KC_C  ,   KC_V ,   KC_B , KC_NO ,KC_NO,     KC_NO, KC_NO, KC_N,   KC_M ,KC_COMM, KC_DOT ,KC_SLSH, KC_RSFT,
                               MO(_ADJUST) , KC_LGUI, KC_ENT, KC_SPC , MO(_NAV)   ,     MO(_SYM)    , KC_SPC ,KC_RALT, KC_RGUI, KC_APP
    ),

    [_NAV] = LAYOUT(
    // Navigation layer
    _______, _______, _______, _______, _______, _______,                                     KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_VOLU, KC_DEL,
    _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______,                                     KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_VOLD, KC_INS,
    _______, _______, _______, _______, _______, _______, _______, KC_SCRL, _______, _______,KC_PAUSE, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_PSCR,
                               _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_SYM] = LAYOUT(
    // Navigation layer
    KC_GRV ,   KC_1 ,   KC_2 ,   KC_3 ,   KC_4 ,   KC_5 ,                                       KC_6 ,   KC_7 ,   KC_8 ,   KC_9 ,   KC_0 , KC_EQL ,
    KC_TILD , KC_EXLM,  KC_AT , KC_HASH,  KC_DLR, KC_PERC,                                     KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PLUS,
    KC_PIPE , KC_BSLS, KC_COLN, KC_SCLN, KC_MINS, KC_LBRC, KC_LCBR, _______, _______, KC_RCBR, KC_RBRC, KC_UNDS, KC_COMM,  KC_DOT, KC_SLSH, KC_QUES,
                                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_ADJUST] = LAYOUT(
    // Adjustment layer
    _______, _______, _______, _______, _______, _______,                                    _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,                                    RM_TOGG, RM_SATU, RM_HUEU, RM_VALU, RM_NEXT, _______,
    _______, _______, _______, _______, _______, _______,_______, _______, _______, _______, _______, RM_SATD, RM_HUED, RM_VALD, RM_PREV, _______,
                               _______, _______, _______,_______, _______, _______, _______, _______, _______, _______
    ),
};
