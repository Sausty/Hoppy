/*
** EPITECH PROJECT, 2022
** Hoppy
** File description:
** input
*/

#include "foundation/input.h"
#include "foundation/dynamic_library.h"
#include "foundation/log.h"
#include "foundation/event.h"

#include <Windows.h>
#include <Xinput.h>
#include <math.h>
#include <map>

namespace hoppy {
    struct gamepad_state {
        XINPUT_STATE state;
        bool connected;
        float vibration[2];
        hmm_v2 joysticks[2];
        std::map<gamepad_button, bool> buttons;
    };

    struct input_state {
        gamepad_state pads[4];
    };

    typedef DWORD (WINAPI* PFN_XINPUT_GET_STATE)(DWORD dwUserIndex, XINPUT_STATE* pState);
    typedef DWORD (WINAPI* PFN_XINPUT_SET_STATE)(DWORD dwUserIndex, XINPUT_VIBRATION* pVibration);

    PFN_XINPUT_GET_STATE XIGetState;
    PFN_XINPUT_SET_STATE XISetState;

    static dynamic_library xinput_library;
    static input_state i_state;

    float normalize(float input, float min, float max)
    {
        float average = (min + max) / 2;
        float range = (max - min) / 2;
        return (input - average) / range;
    }

    float apply_deadzone(float value, float max_value, float deadzone)
    {
        if (value < -deadzone)
            value += deadzone;
        else if (value > deadzone)
            value -= deadzone;
        else
            return 0;
        float NormValue = value / (max_value - deadzone);
        return std::max(-1.0f, std::min(NormValue, 1.0f));
    }

    void input_init()
    {
        dynamic_library_load(&xinput_library, "xinput1_4.dll");
        XIGetState = (PFN_XINPUT_GET_STATE)dynamic_library_get_proc_addr(&xinput_library, "XInputGetState");
        XISetState = (PFN_XINPUT_SET_STATE)dynamic_library_get_proc_addr(&xinput_library, "XInputSetState");
    }

    void input_exit()
    {
        dynamic_library_free(&xinput_library);
    }

    void input_update()
    {
        for (int i = 0; i < 4; i++) {
            XINPUT_STATE state;
        
            DWORD result = XIGetState(i, &state);
            bool connected = result == ERROR_SUCCESS;

            if (connected != i_state.pads[i].connected) {
                event e;
                e.payload.i32[0] = i;
                if (connected)
                    event_system_fire(event_type::gamepad_connect, nullptr, e);
                else
                    event_system_fire(event_type::gamepad_disconnect, nullptr, e);
            }

            i_state.pads[i].connected = connected;
            if (connected) {
                i_state.pads[i].buttons[gamepad_button::a] =              (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0;
                i_state.pads[i].buttons[gamepad_button::b] =              (state.Gamepad.wButtons & XINPUT_GAMEPAD_B) != 0;
                i_state.pads[i].buttons[gamepad_button::x] =              (state.Gamepad.wButtons & XINPUT_GAMEPAD_X) != 0;
                i_state.pads[i].buttons[gamepad_button::y] =              (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) != 0;
                i_state.pads[i].buttons[gamepad_button::dpad_up] =        (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) != 0;
                i_state.pads[i].buttons[gamepad_button::dpad_down] =      (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) != 0;
                i_state.pads[i].buttons[gamepad_button::dpad_left] =      (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) != 0;
                i_state.pads[i].buttons[gamepad_button::dpad_right] =     (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0;
                i_state.pads[i].buttons[gamepad_button::start] =          (state.Gamepad.wButtons & XINPUT_GAMEPAD_START) != 0;
                i_state.pads[i].buttons[gamepad_button::back] =           (state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) != 0;
                i_state.pads[i].buttons[gamepad_button::left_thumb] =     (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) != 0;
                i_state.pads[i].buttons[gamepad_button::left_shoulder] =  (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) != 0;
                i_state.pads[i].buttons[gamepad_button::right_thumb] =    (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) != 0;
                i_state.pads[i].buttons[gamepad_button::right_shoulder] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) != 0;
            
                XINPUT_VIBRATION vibration;
                vibration.wLeftMotorSpeed = i_state.pads[i].vibration[0] * 65335.0f;
                vibration.wRightMotorSpeed = i_state.pads[i].vibration[1] * 65335.0f;
                XISetState(i, &vibration);

                i_state.pads[i].state = state;

                hmm_v2 norm_left;
                norm_left.X = normalize(state.Gamepad.sThumbLX, -32767, 32767);
                norm_left.Y = normalize(state.Gamepad.sThumbLY, -32767, 32767);

                hmm_v2 norm_right;
                norm_right.X = normalize(state.Gamepad.sThumbRX, -32767, 32767);
                norm_right.Y = normalize(state.Gamepad.sThumbRY, -32767, 32767);
                
                hmm_v2 left;
                left.X = apply_deadzone(norm_left.X, 1.0f, normalize(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE, SHRT_MIN, SHRT_MAX));
                left.Y = apply_deadzone(norm_left.Y, 1.0f, normalize(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE, SHRT_MIN, SHRT_MAX));

                hmm_v2 right;
                right.X = apply_deadzone(norm_right.X, 1.0f, normalize(XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE, SHRT_MIN, SHRT_MAX));
                right.Y = apply_deadzone(norm_right.Y, 1.0f, normalize(XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE, SHRT_MIN, SHRT_MAX));

                i_state.pads[i].joysticks[JOYSTICK_LEFT] = left;
                i_state.pads[i].joysticks[JOYSTICK_RIGHT] = right;
            }
        }
    }

    bool input_is_gamepad_button_pressed(int index, gamepad_button button)
    {
        return i_state.pads[index].buttons[button];
    }

    hmm_v2 input_get_gamepad_joystick(int index, int joystick)
    {
        return i_state.pads[index].joysticks[joystick];
    }

    void input_set_gamepad_vibration(int index, float left, float right)
    {
        i_state.pads[index].vibration[0] = left;
        i_state.pads[index].vibration[1] = right;
    }
}
