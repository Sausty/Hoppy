/*
** EPITECH PROJECT, 2022
** hoppy
** File description:
** window.h
*/

#ifndef WINDOW_H_
#define WINDOW_H_

#include <cstdint>

namespace hoppy {
    /// @brief A window handle
    struct window {
        /// @brief The width of the window
        uint32_t width;
        /// @brief The height of the window
        uint32_t height;
        /// @brief The title of the window
        char const *title;
        /// @brief Whether or not the window is open
        bool is_open;
        /// @brief The native platform handle of the window
        void* platform_handle;
    };

    void window_init(window *w, uint32_t width, uint32_t height, const char *title);
    void window_free(window *w);
    void window_poll_events(window *w);
    bool window_is_open(window *w);
}

#endif