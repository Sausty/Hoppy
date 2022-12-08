/*
** EPITECH PROJECT, 2022
** Hoppy
** File description:
** d3d12_swapchain
*/

#ifndef D3D12_SWAPCHAIN_H_
#define D3D12_SWAPCHAIN_H_

#include <d3d12.h>
#include <dxgi1_6.h>
#include <cstdint>

#include "rhi/rhi.h"
#include "d3d12_descriptor_heap.h"

namespace hoppy {
    struct d3d12_swapchain {
        IDXGISwapChain3 *swapchain;
        ID3D12Resource *swapchain_buffers[FRAMES_IN_FLIGHT];
        uint32_t render_targets[FRAMES_IN_FLIGHT];
        uint32_t frame_index;
    };

    void d3d12_swapchain_init(d3d12_swapchain *swapchain);
    void d3d12_swapchain_free(d3d12_swapchain *swapchain);
    void d3d12_swapchain_present(d3d12_swapchain *swapchain, bool vsync);
}

#endif /* !D3D12_SWAPCHAIN_H_ */
