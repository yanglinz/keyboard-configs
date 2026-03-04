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
    'L', 'L', 'L', 'L', 'L', 'L',                       'R', 'R', 'R', 'R', 'R', 'R',
    'L', 'L', 'L', 'L', 'L', 'L',                       'R', 'R', 'R', 'R', 'R', 'R',
    'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L',   'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R',
                   'L', 'L', 'L', 'L', 'L',   'R', 'R', 'R', 'R', 'R'
  );
// clang-format on

/*
 * =========
 * Tap dance
 * =========
 */

enum tdance {
  TD_CAPS = 0,
  TD_NUM,
};

void td_caps_finished(tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    set_oneshot_mods(MOD_LSFT);
  } else if (state->count == 2) {
    caps_word_toggle();
  }
}

void td_nums_finished(tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    layer_invert(_NAV);
  } else if (state->count == 2) {
    layer_invert(_NUM);
  }
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_CAPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_caps_finished, NULL),
    [TD_NUM] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_nums_finished, NULL)};

/*
 * =========
 * Macros
 * =========
 */

enum custom_keycodes {
  MC_SEL_LINE = SAFE_RANGE,
};

const uint16_t PROGMEM line_combo[] = {KC_X, KC_DOT, COMBO_END};

combo_t key_combos[] = {
    COMBO(line_combo, MC_SEL_LINE),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case MC_SEL_LINE:
    if (record->event.pressed) {
      // https://www.reddit.com/r/ErgoMechKeyboards/comments/1c9satw/whats_your_favorite_productivity_macro/
      tap_code(KC_HOME);
      register_code(KC_LSFT);
      tap_code(KC_END);
      unregister_code(KC_LSFT);
    }
    return false;
  }
  return true;
}

/*
 * =========
 * Tap dance
 * =========
 */

bool rgb_matrix_indicators_user(void) {
  uint8_t layer = get_highest_layer(layer_state);
  // todo: get tap dance state and represent that in the led

  switch (layer) {
  case _NUM:
    rgb_matrix_sethsv(0, 255, 55);
    rgb_matrix_set_color_all(255, 100, 0); // orange
    break;
  case _ADJ:
    rgb_matrix_sethsv(0, 255, 55);
    rgb_matrix_set_color_all(255, 0, 0); // red
    break;
  case _BASE:
  case _WIN:
  case _SYM:
  case _NAV:
  default:
    rgb_matrix_sethsv(0, 0, 0);
    rgb_matrix_set_color_all(0, 0, 0); // off
    break;
  }

  // Indicate that we've handled the frame
  return true;
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // Base qwerty layer
  [_BASE] = LAYOUT(
    KC_TAB,  KC_Q, KC_W, KC_E,     KC_R,  KC_T,                                                 KC_Y,     KC_U,  KC_I,    KC_O,   KC_P,    KC_BSPC,
    KC_ESC,  HR_A, HR_S, HR_D,     HR_F,  KC_G,                                                 KC_H,     HR_J,  HR_K,    HR_L,   HR_SCLN, KC_QUOT,
    KC_LSFT, KC_Z, KC_X, KC_C,     KC_V,  KC_B,     KC_NO,  KC_NO,         KC_NO,       KC_NO,  KC_N,     KC_M,  KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
                         MO(_ADJ), KC_NO, MO(_NAV), KC_SPC, TD(TD_NUM),    TD(TD_CAPS), KC_ENT, MO(_SYM), KC_NO, TO(_BASE)
  ),

  [_WIN] = LAYOUT(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
    KC_TRNS, HRW_A,   HRW_S,   HRW_D,   HRW_F,   KC_TRNS,                                     KC_TRNS, HRW_J,   HRW_K,   HRW_L,   HRW_SCLN, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
                               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  ),

  // Symbol layer
  // todo: migrate some over from https://github.com/mmccoyd/hillside/tree/main/hillside46
  [_SYM] = LAYOUT(
    KC_TRNS, KC_GRV,     LSFT(KC_GRV),   KC_HASH,    LSFT(KC_7),     KC_PIPE,                                          LSFT(KC_6), LSFT(KC_LBRC), LSFT(KC_RBRC),  KC_LBRC,        KC_RBRC,        KC_DEL,
    KC_TRNS, LSFT(KC_1), LSFT(KC_MINUS), KC_COLON,   KC_EQUAL,       KC_DOLLAR,                                        LSFT(KC_2), LSFT(KC_9),    LSFT(KC_0),     LSFT(KC_MINUS), KC_SCLN,        KC_TRNS,
    KC_TRNS, KC_PERCENT, LSFT(KC_SLASH), LSFT(KC_8), LSFT(KC_EQUAL), KC_BSLS,   KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_SLSH,    KC_MINUS,      LSFT(KC_COMMA), LSFT(KC_DOT),   LSFT(KC_QUOTE), KC_TRNS,
                                         KC_TRNS,    KC_TRNS,        KC_TRNS,   KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  ),

  // Navigation layer
  [_NAV] = LAYOUT(
    KC_TRNS, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                           KC_6,    KC_7,    KC_8,    KC_9,     KC_0,    KC_BSPC,
    KC_TRNS, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, KC_NO,                                          KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_CAPS, KC_TRNS,
    KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,      KC_NO,   KC_NO,   KC_HOME, KC_PGDN, KC_PGUP, KC_END,   KC_INS,  KC_TRNS,
                               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  ),

  // Number pad layer
  [_NUM] = LAYOUT(
    KC_TRNS, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                           KC_6,    KC_7,    KC_8,    KC_9, KC_0,  KC_BSPC,
    KC_TRNS, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, KC_NO,                                          KC_0,    KC_4,    KC_5,    KC_6, KC_NO, KC_TRNS,
    KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,      KC_NO,   KC_NO,   KC_0,    KC_1,    KC_2,    KC_3, KC_NO, KC_TRNS,
                               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  ),

  // Adjustment layer
  [_ADJ] = LAYOUT(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                     PDF(_BASE), PDF(_WIN), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                     RM_TOGG,    RM_SATU,   RM_HUEU, RM_VALU, RM_NEXT, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    RM_SATD,   RM_HUED, RM_VALD, RM_PREV, KC_TRNS,
                               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,   KC_TRNS
  ),
};
