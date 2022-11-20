/*
** EPITECH PROJECT, 2022
** hoppy
** File description:
** dynamic_library.h
*/

#ifndef DYNAMIC_LIBRARY_H_
#define DYNAMIC_LIBRARY_H_

namespace hoppy {
    struct dynamic_library {
        void* platform_handle;
        const char* filepath;
    };

    void dynamic_library_load(dynamic_library *library, char const* filepath);
    void dynamic_library_free(dynamic_library *library);
    void *dynamic_library_get_proc_addr(dynamic_library *library, char const *name);
}

#endif /* !DYNAMIC_LIBRARY_H_ */
