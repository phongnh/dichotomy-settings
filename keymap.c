#include "dichotomy.h"

enum dichotomy_layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
    _MOUSE,
};

enum dichotomy_keycodes {
    QWERTY = SAFE_RANGE,
    MOUSE,
};

#define LOWER   MO(_LOWER)
#define RAISE   MO(_RAISE)
#define LWR_TAB LT(_LOWER, KC_TAB)  // Turn on _LOWER layer when held, Tab when tapped
#define RSE_BSP LT(_RAISE, KC_TAB)  // Turn on _RAISE layer when held, Tab when tapped
#define CAG_GRV LCAG_T(KC_GRV)      // Left Control+Alt+Gui when held, ` when tapped
#define CAG_TAB LCAG_T(KC_TAB)      // Left Control+Alt+Gui when held, Tab when tapped
#define SFT_GRV LSFT_T(KC_GRV)      // Left Shift when held, ` when tapped
#define CTL_ESC LCTL_T(KC_ESC)      // Left Control when held, Esc when tapped
#define CTL_Z   LCTL_T(KC_Z)        // Left Control when held, z when tapped
#define CTL_SLS LCTL_T(KC_SLSH)     // Left Control when held, / when tapped
#define GUI_QUO RGUI_T(KC_QUOT)     // Right Gui when held, " when tapped
#define MOU_SCL LT(_MOUSE, KC_SCLN) // Turn on _MOUSE layer when held, ; when tapped
#define GUI_EQL LGUI_T(KC_EQL)      // Left Gui when held, = when tapped
#define GUI_MIN RGUI_T(KC_MINS)     // Right Gui when held, - when tapped

#define BACKLIGHT_LEVELS 1
#define RED_BRIGHTNESS   1
#define GREEN_BRIGHTNESS 1
#define BLUE_BRIGHTNESS  1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = LAYOUT(
    CAG_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,           KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
    CTL_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,           KC_H,    KC_J,    KC_K,    KC_L,    MOU_SCL, GUI_QUO,
    SFT_GRV,  CTL_Z,   KC_X,    KC_C,    KC_V,    KC_B,           KC_N,    KC_M,    KC_COMM, KC_DOT,  CTL_SLS, KC_RSFT,
                                KC_LALT, GUI_EQL, LOWER,          RAISE,   GUI_MIN, KC_RALT,
                       KC_BTN3, KC_FN1,  LWR_TAB, KC_SPC,         KC_ENT,  RSE_BSP, KC_FN1,  KC_BTN3
),

[_LOWER] = LAYOUT(
    KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
    KC_GRV,  _______, KC_LEFT, KC_RGHT, KC_UP,   KC_LBRC,        KC_RBRC, KC_MINS, KC_EQL,  KC_LPRN, KC_RPRN, KC_EQL,
    _______, _______, _______, _______, KC_DOWN, KC_LCBR,        KC_RCBR, KC_UNDS, KC_PLUS, _______, _______, _______,
                               _______, _______, _______,        _______, _______, _______,
                      _______, _______, LOWER,   _______,        KC_DEL,  RAISE,   _______, _______
),

[_RAISE] = LAYOUT(
    KC_PLUS, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,        KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS,
    KC_TILD, _______, _______, _______, KC_PGUP, KC_UNDS,        KC_EQL,  KC_HOME, _______, KC_LBRC, KC_RBRC, KC_PIPE,
    _______, _______, _______, _______, KC_PGDN, KC_MINS,        KC_PLUS, KC_END,  _______, KC_LCBR, KC_RCBR, _______,
                               _______, _______, _______,        _______, _______, _______,
                      _______, _______, LOWER,   _______,        _______, RAISE,   _______, _______
),

[_ADJUST] = LAYOUT(
    KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,          KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    _______, _______, _______, _______, _______, QWERTY,         MOUSE,   _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, AG_NORM,        AG_SWAP, _______, _______, _______, _______, _______,
                               _______, _______, _______,        _______, _______, _______,
                      _______, _______, _______, _______,        _______, _______, _______, _______
),

[_MOUSE] = LAYOUT(
    _______, QWERTY,  KC_BTN3, KC_MS_U, KC_BTN2, _______,        _______, KC_BTN1, KC_WH_U, KC_BTN1, _______, _______,
    _______, KC_BTN1, KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN1,        KC_BTN1, KC_WH_L, KC_WH_D, KC_WH_R, _______, _______,
    _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______,
                               _______, _______, _______,        _______, KC_UP,   _______,
                      _______, _______, _______, _______,        KC_LEFT, KC_DOWN, KC_RGHT, _______
)

};

const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_TAP_TOGGLE(_MOUSE),  // FN1 - Momentary Layer Symbols (_MOUSE)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case QWERTY:
        if (record->event.pressed) {
            set_single_persistent_default_layer(_QWERTY);
        }
        return false;
        break;
    case MOUSE:
        if (record->event.pressed) {
            set_single_persistent_default_layer(_MOUSE);
        }
        return false;
        break;
    }
    return true;
}

// Runs whenever there is a layer state change.
uint32_t layer_state_set_user(uint32_t state) {
    uint32_t new_state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);

#ifdef ENABLE_LAYER_LEDS
    uint8_t layer = biton32(new_state);

    switch (layer) {
    case _QWERTY:
        set_led_off();
        break;
    case _LOWER:
        set_led_red();
        break;
    case _RAISE:
        set_led_green();
        break;
    case _ADJUST:
        set_led_yellow();
        break;
    case _MOUSE:
        set_led_blue();
        break;
    default:
        break;
    }
#endif

    return new_state;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
    set_led_off();
}

// Runs constantly in the background, in a loop.
// void matrix_scan_user(void) {
// }
