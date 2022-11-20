/*
** EPITECH PROJECT, 2022
** hoppy
** File description:
** dynamic_library.h
*/

#ifndef DYNAMIC_LIBRARY_H_
#define DYNAMIC_LIBRARY_H_

namespace hoppy {
    /// @brief A structure representing a dynamic library
    struct dynamic_library {
        /// @brief The native handle of the dynamic library
        void* platform_handle;
        /// @brief The filepath of the library
        const char* filepath;
    };

    /// @brief Loads a dynamic library from the given filepath.
    /// @param library A pointer to the dynamic library.
    /// @param filepath The filepath of the library to load.
    void dynamic_library_load(dynamic_library *library, char const* filepath);
    
    /// @brief Frees a loaded dynamic library.
    /// @param library A pointer to the dynamic library.
    void dynamic_library_free(dynamic_library *library);

    /// @brief Loads a function from the given dynamic library
    /// @param library A pointer to the dynamic library
    /// @param name The name of the function to load
    void *dynamic_library_get_proc_addr(dynamic_library *library, char const *name);
}

#endif /* !DYNAMIC_LIBRARY_H_ */
