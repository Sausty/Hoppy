/*
** EPITECH PROJECT, 2022
** Hoppy
** File description:
** input
*/

#include "foundation/input.h"
#include "foundation/dynamic_library.h"
#include "foundation/log.h"

#include <Windows.h>
#include <Xinput.h>

namespace hoppy {
    typedef DWORD (WINAPI* PFN_XINPUT_GET_STATE)(DWORD dwUserIndex, XINPUT_STATE* pState);
    typedef DWORD (WINAPI* PFN_XINPUT_SET_STATE)(DWORD dwUserIndex, XINPUT_VIBRATION* pVibration);

    PFN_XINPUT_GET_STATE XIGetState;
    PFN_XINPUT_SET_STATE XISetState;
    static dynamic_library xinput_library;

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
}
