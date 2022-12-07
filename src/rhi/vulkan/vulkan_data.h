/*
** EPITECH PROJECT, 2022
** Hoppy
** File description:
** vulkan_data
*/

#ifndef VULKAN_DATA_H_
#define VULKAN_DATA_H_

#include "foundation/window.h"

namespace hoppy {
    struct vulkan_state {
        window *connected_window;
        int swapchain_image_count;
    };

    extern vulkan_state v_state;
}

#endif /* !VULKAN_DATA_H_ */
