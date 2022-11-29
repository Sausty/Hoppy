/*
** EPITECH PROJECT, 2022
** Hoppy
** File description:
** macos_dynamic_library
*/

#include "foundation/dynamic_library.h"
#include "foundation/log.h"

#include <fcntl.h>
#include <dlfcn.h>

namespace hoppy {
    void dynamic_library_load(dynamic_library *library, char const* filepath)
    {
        library->platform_handle = dlopen(filepath, RTLD_NOW);
        if (!library->platform_handle) {
            log_err("[ERROR] Failed to load dynamic library! (Path: %s)", filepath);
        }
    }

    void dynamic_library_free(dynamic_library *library)
    {
        dlclose(library->platform_handle);
    }

    void *dynamic_library_get_proc_addr(dynamic_library *library, char const *name)
    {
        return dlsym(library->platform_handle, name);
    }
}