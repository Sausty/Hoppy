/*
** EPITECH PROJECT, 2022
** Hoppy
** File description:
** rhi
*/

#ifndef RHI_H_
#define RHI_H_

#include "foundation/window.h"

namespace hoppy {
    /// @brief Connects the render hardware interface to the given window
    /// @param w The window to connect to
    void rhi_connect_window(window *w);

    /// @brief Initialises the render hardware interface
    void rhi_init();

    /// @brief Exits the render hardware interface
    void rhi_exit();
}

#endif /* !RHI_H_ */
