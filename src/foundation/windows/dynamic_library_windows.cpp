/*
** EPITECH PROJECT, 2022
** hoppy
** File description:
** dynamic_library_windows.cpp
*/

#include "foundation/dynamic_library.h"

#include <Windows.h>

namespace hoppy {
    void dynamic_library_load(dynamic_library *library, char const* filepath)
    {
        library->platform_handle = LoadLibraryA(filepath);
        library->filepath = filepath;
    }

    void dynamic_library_free(dynamic_library *library)
    {
        FreeLibrary((HMODULE)library->platform_handle);
    }

    void *dynamic_library_get_proc_addr(dynamic_library *library, char const *name)
    {
        return reinterpret_cast<void*>(GetProcAddress((HMODULE)library->platform_handle, name));
    }
}