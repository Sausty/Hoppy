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

namespace hoppy {
    struct gamepad_state {
        XINPUT_STATE state;
        bool connected;
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
        }
    }
}
