/*
** EPITECH PROJECT, 2022
** Hoppy
** File description:
** d3d12_data
*/

#ifndef D3D12_DATA_H_
#define D3D12_DATA_H_

#include <d3d12.h>
#include <dxgi1_6.h>

#include "math/HandmadeMath.hpp"

#include "foundation/window.h"
#include "foundation/dynamic_library.h"

#include "rhi/rhi.h"

#include "d3d12_fence.h"
#include "d3d12_descriptor_heap.h"
#include "d3d12_swapchain.h"

#define SafeRelease(obj) if (obj) { obj->Release(); }

namespace hoppy {
    struct d3d12_state {
        dynamic_library d3d_lib;
        dynamic_library dxgi_lib;
        dynamic_library d3dc_lib;
        window *w;

        IDXGIDevice* dxgi_device;
        IDXGIFactory3* factory;
        IDXGIAdapter1* adapter;
        ID3D12Device* device;
        ID3D12Debug1* debug;
        ID3D12DebugDevice* debug_device;

        ID3D12CommandQueue* cmd_queue;
        ID3D12CommandAllocator *cmd_allocators[FRAMES_IN_FLIGHT];
        ID3D12GraphicsCommandList1 *cmd_lists[FRAMES_IN_FLIGHT];

        d3d12_fence device_fence;

        d3d12_descriptor_heap rtv_heap;
        d3d12_descriptor_heap cbv_srv_uav_heap;

        d3d12_swapchain swapchain;
        uint64_t frame_sync[FRAMES_IN_FLIGHT];
        uint32_t frame_index;
    };

    // PRIVATE: DO NOT ACCESS ANY MEMBER OF THIS STRUCTURE
    extern d3d12_state d3d12;
}

#endif /* !D3D12_DATA_H_ */
