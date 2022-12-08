/*
** EPITECH PROJECT, 2022
** Hoppy
** File description:
** d3d12_descriptor_heap
*/

#include "d3d12_descriptor_heap.h"
#include "d3d12_data.h"
#include "foundation/log.h"

namespace hoppy {
    void d3d12_descriptor_heap_init(d3d12_descriptor_heap *heap, D3D12_DESCRIPTOR_HEAP_TYPE type, uint32_t count)
    {
        heap->type = type;
        heap->descriptor_count = count;
        heap->descriptor_lut = std::vector<bool>(count, false);

        D3D12_DESCRIPTOR_HEAP_DESC desc = {};
        desc.Type = type;
        desc.NumDescriptors = count;
        desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
        if (type == D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV  || type == D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER)
            desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
        
        HRESULT result = d3d12.device->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&heap->heap));
        if (FAILED(result)) {
            log_crit("[ERROR] Failed to create D3D12 descriptor heap!");
        }

        heap->increment_size = d3d12.device->GetDescriptorHandleIncrementSize(type);
    }

    void d3d12_descriptor_heap_free(d3d12_descriptor_heap *heap)
    {
        heap->descriptor_lut.clear();
        SafeRelease(heap->heap);
    }

    D3D12_CPU_DESCRIPTOR_HANDLE d3d12_descriptor_cpu(d3d12_descriptor_heap *heap, uint32_t offset)
    {
        D3D12_CPU_DESCRIPTOR_HANDLE handle = heap->heap->GetCPUDescriptorHandleForHeapStart();
        handle.ptr += offset * heap->increment_size;
        return (handle);
    }

    D3D12_GPU_DESCRIPTOR_HANDLE d3d12_descriptor_gpu(d3d12_descriptor_heap *heap, uint32_t offset)
    {
        D3D12_GPU_DESCRIPTOR_HANDLE handle = heap->heap->GetGPUDescriptorHandleForHeapStart();
        handle.ptr += offset * heap->increment_size;
        return (handle);
    }

    uint32_t d3d12_descriptor_alloc(d3d12_descriptor_heap *heap)
    {
        for (int i = 0; i < heap->descriptor_count; i++) {
            if (heap->descriptor_lut[i] == false) {
                heap->descriptor_lut[i] = true;
                return i;
            }
        }
        return -1;
    }

    void d3d12_descriptor_free(d3d12_descriptor_heap *heap, uint32_t descriptor)
    {
        heap->descriptor_lut[descriptor] = false;
    }
}
