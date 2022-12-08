/*
** EPITECH PROJECT, 2022
** Hoppy
** File description:
** d3d12_descriptor_heap
*/

#ifndef D3D12_DESCRIPTOR_HEAP_H_
#define D3D12_DESCRIPTOR_HEAP_H_

#include <cstdint>
#include <d3d12.h>
#include <vector>

namespace hoppy {
    struct d3d12_descriptor_heap {
        ID3D12DescriptorHeap *heap;
        uint32_t increment_size;
        uint32_t descriptor_count;
        D3D12_DESCRIPTOR_HEAP_TYPE type;
        std::vector<bool> descriptor_lut;
    };

    void d3d12_descriptor_heap_init(d3d12_descriptor_heap *heap, D3D12_DESCRIPTOR_HEAP_TYPE type, uint32_t count);
    void d3d12_descriptor_heap_free(d3d12_descriptor_heap *heap);
    D3D12_CPU_DESCRIPTOR_HANDLE d3d12_descriptor_cpu(d3d12_descriptor_heap *heap, uint32_t offset);
    D3D12_GPU_DESCRIPTOR_HANDLE d3d12_descriptor_gpu(d3d12_descriptor_heap *heap, uint32_t offset);
    uint32_t d3d12_descriptor_alloc(d3d12_descriptor_heap *heap);
    void d3d12_descriptor_free(d3d12_descriptor_heap *heap, uint32_t descriptor);
}

#endif /* !D3D12_DESCRIPTOR_HEAP_H_ */
