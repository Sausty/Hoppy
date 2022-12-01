/*
** EPITECH PROJECT, 2022
** Hoppy
** File description:
** macos_input
*/

#include "foundation/input.h"

#include <sstream>
#include <unordered_map>

#include <linux/joystick.h>
#include <fcntl.h>
#include <unistd.h>

#define JOYSTICK_AXIS_LEFT_THUMB_X      0
#define JOYSTICK_AXIS_LEFT_THUMB_Y      1
#define JOYSTICK_AXIS_RIGHT_THUMB_X     2
#define JOYSTICK_AXIS_RIGHT_THUMB_Y     3
#define JOYSTICK_AXIS_RIGHT_TRIGGER     4
#define JOYSTICK_AXIS_LEFT_TRIGGER      5
#define JOYSTICK_AXIS_DPAD_X            6
#define JOYSTICK_AXIS_DPAD_Y            7

#define JOYSTICK_BUTTON_A               0
#define JOYSTICK_BUTTON_B               1
#define JOYSTICK_BUTTON_X               2
#define JOYSTICK_BUTTON_Y               3
#define JOYSTICK_BUTTON_LEFT_SHOULDER   4
#define JOYSTICK_BUTTON_RIGHT_SHOULDER  5
#define JOYSTICK_BUTTON_BACK            6
#define JOYSTICK_BUTTON_START           7
#define JOYSTICK_BUTTON_XBOX            8
#define JOYSTICK_BUTTON_LEFT_THUMB      9
#define JOYSTICK_BUTTON_RIGHT_THUMB     10


namespace hoppy {
    struct linux_gamepad_state {
        char id;
        int file_descriptor;
        int ed;
        struct ff_effect effect;

        hmm_vec2 triggers;
        hmm_vec2 joysticks[2];
        std::unordered_map<gamepad_button, bool> buttons;
    };

    struct linux_input_state {
        linux_gamepad_state pads[4];
    };

    linux_input_state li_state;

    void input_init()
    {        
        return;
    }

    void input_exit()
    {
        return;
    }

    void input_update()
    {
        return;
    }

    bool input_is_key_pressed(keyboard_key key)
    {
        return false;
    }

    bool input_is_mouse_button_pressed(mouse_buttons button)
    {
        return false;
    }

    bool input_is_gamepad_button_pressed(int index, gamepad_button button)
    {
        return li_state.pads[index].buttons[button];
    }

    hmm_v2 input_get_gamepad_triggers(int index)
    {
        return li_state.pads[index].triggers;
    }

    hmm_v2 input_get_gamepad_joystick(int index, int joystick)
    {
        return li_state.pads[index].joysticks[index];
    }

    void input_set_gamepad_vibration(int index, float left, float right)
    {
        return;
    }
}
