/*
** EPITECH PROJECT, 2022
** Hoppy
** File description:
** d3d12_fence
*/

#include "d3d12_fence.h"
#include "d3d12_data.h"

#include "foundation/log.h"

namespace hoppy {
    void d3d12_fence_init(d3d12_fence *fence)
    {
        fence->fence_value = 0;
        HRESULT result = d3d12.device->CreateFence(fence->fence_value, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence->fence));
        if (FAILED(result)) {
            log_crit("[ERROR] Failed to create D3D12 fence!");
        }
    }

    void d3d12_fence_free(d3d12_fence *fence)
    {
        SafeRelease(fence->fence);
    }

    uint64_t d3d12_fence_signal(d3d12_fence *fence)
    {
        fence->fence_value++;
        d3d12.cmd_queue->Signal(fence->fence, fence->fence_value);
        return fence->fence_value;
    }

    bool d3d12_fence_reached(d3d12_fence *fence, uint64_t value)
    {
        return fence->fence->GetCompletedValue() >= value;
    }

    void d3d12_fence_sync(d3d12_fence *fence, uint64_t value)
    {
        if (!d3d12_fence_reached(fence, value)) {
            fence->fence->SetEventOnCompletion(value, NULL);
        }
    }

    void d3d12_fence_flush(d3d12_fence *fence)
    {
        d3d12_fence_sync(fence, d3d12_fence_signal(fence));
    }
}
