/*
** EPITECH PROJECT, 2022
** Hoppy
** File description:
** vulkan_rhi
*/

#include "rhi/rhi.h"

#include "vulkan_data.h"

namespace hoppy {
    vulkan_state v_state;

    void rhi_connect_window(window *w) 
    {
        v_state.connected_window = w;
    }

    void rhi_init()
    {
        return;
    }

    void rhi_exit()
    {
        return;
    }
}
