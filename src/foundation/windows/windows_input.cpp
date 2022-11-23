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
#include <map>

namespace hoppy {
    struct gamepad_state {
        XINPUT_STATE state;
        bool connected;
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
                i_state.pads[i].buttons[gamepad_button::a] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0;
                i_state.pads[i].buttons[gamepad_button::b] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_B) != 0;
                i_state.pads[i].buttons[gamepad_button::x] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_X) != 0;
                i_state.pads[i].buttons[gamepad_button::y] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) != 0;
                i_state.pads[i].buttons[gamepad_button::dpad_up] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) != 0;
                i_state.pads[i].buttons[gamepad_button::dpad_down] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) != 0;
                i_state.pads[i].buttons[gamepad_button::dpad_left] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) != 0;
                i_state.pads[i].buttons[gamepad_button::dpad_right] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0;
                i_state.pads[i].buttons[gamepad_button::start] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_START) != 0;
                i_state.pads[i].buttons[gamepad_button::back] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) != 0;
                i_state.pads[i].buttons[gamepad_button::left_thumb] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) != 0;
                i_state.pads[i].buttons[gamepad_button::left_shoulder] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) != 0;
                i_state.pads[i].buttons[gamepad_button::right_thumb] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) != 0;
                i_state.pads[i].buttons[gamepad_button::right_shoulder] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) != 0;
            }
        }
    }

    bool input_is_gamepad_button_pressed(int index, gamepad_button button)
    {
        return i_state.pads[index].buttons[button];
    }
}
