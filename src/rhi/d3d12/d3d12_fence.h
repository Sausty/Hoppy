/*
** EPITECH PROJECT, 2022
** Hoppy
** File description:
** d3d12_fence
*/

#ifndef D3D12_FENCE_H_
#define D3D12_FENCE_H_

#include <cstdint>
#include <d3d12.h>

namespace hoppy {
    struct d3d12_fence {
        ID3D12Fence* fence;
        uint64_t fence_value;
    };

    void d3d12_fence_init(d3d12_fence *fence);
    void d3d12_fence_free(d3d12_fence *fence);
    uint64_t d3d12_fence_signal(d3d12_fence *fence);
    bool d3d12_fence_reached(d3d12_fence *fence, uint64_t value);
    void d3d12_fence_sync(d3d12_fence *fence, uint64_t value);
    void d3d12_fence_flush(d3d12_fence *fence);
}

#endif /* !D3D12_FENCE_H_ */
