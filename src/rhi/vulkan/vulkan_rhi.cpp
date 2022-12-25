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

    rhi_backend rhi_get_backend()
    {
        return rhi_backend::vulkan;
    }

    void rhi_connect_window(window *w) 
    {
        v_state.connected_window = w;
    }

    void rhi_init(rhi_feature_request *requests)
    {
        return;
    }

    void rhi_exit()
    {
        return;
    }
}
