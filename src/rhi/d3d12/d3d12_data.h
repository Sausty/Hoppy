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

#include "foundation/window.h"
#include "foundation/dynamic_library.h"

#include "rhi/rhi.h"

#include "d3d12_fence.h"

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

        d3d12_fence device_fence;
    };

    // PRIVATE: DO NOT ACCESS ANY MEMBER OF THIS STRUCTURE
    extern d3d12_state d3d12;
}

#endif /* !D3D12_DATA_H_ */
