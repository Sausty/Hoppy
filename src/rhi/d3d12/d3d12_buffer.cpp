/*
** EPITECH PROJECT, 2022
** Hoppy
** File description:
** d3d12_buffer
*/

#include "rhi/rhi_buffer.h"

#include "d3d12_data.h"

#include "foundation/log.h"

namespace hoppy {
    struct d3d12_buffer {
        ID3D12Resource *resource;

        uint32_t heap_index;
        D3D12_VERTEX_BUFFER_VIEW vbv;
        D3D12_INDEX_BUFFER_VIEW ibv;
        D3D12_CONSTANT_BUFFER_VIEW_DESC cbv;
        D3D12_UNORDERED_ACCESS_VIEW_DESC uav;
    };

    void rhi_buffer_init(rhi_buffer *buffer,  uint64_t stride, uint64_t size, rhi_buffer_type type)
    {
        buffer->size = size;
        buffer->stride = stride;
        buffer->type = type;
        buffer->reserved = (void*)(new d3d12_buffer);

        d3d12_buffer *data = (d3d12_buffer*)buffer->reserved;

        D3D12_HEAP_PROPERTIES heap_properties = {};
        heap_properties.Type = D3D12_HEAP_TYPE_UPLOAD;
        heap_properties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
        heap_properties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
        heap_properties.CreationNodeMask = 0;
        heap_properties.VisibleNodeMask = 0;

        D3D12_RESOURCE_DESC resource_desc = {};
        resource_desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
        resource_desc.Alignment = D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT;
        resource_desc.Width = size;
        resource_desc.Height = 1;
        resource_desc.DepthOrArraySize = 1;
        resource_desc.MipLevels = 1;
        resource_desc.Format = DXGI_FORMAT_UNKNOWN;
        resource_desc.SampleDesc.Count = 1;
        resource_desc.SampleDesc.Quality = 0;
        resource_desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
        resource_desc.Flags = D3D12_RESOURCE_FLAG_NONE;

        HRESULT result = d3d12.device->CreateCommittedResource(&heap_properties, D3D12_HEAP_FLAG_NONE, &resource_desc, D3D12_RESOURCE_STATE_GENERIC_READ, NULL, IID_PPV_ARGS(&data->resource));
        if (FAILED(result)) {
            log_crit("[ERROR] Failed to create ID3D12Resource in rhi_buffer!");
        }

        switch (type)
        {
            case rhi_buffer_type::vertex: {
                data->vbv.BufferLocation = data->resource->GetGPUVirtualAddress();
                data->vbv.SizeInBytes = size;
                data->vbv.StrideInBytes = stride;
            } break;
            case rhi_buffer_type::index: {
                data->ibv.BufferLocation = data->resource->GetGPUVirtualAddress();
                data->ibv.SizeInBytes = size;
                data->ibv.Format = DXGI_FORMAT_R32_UINT;
            } break;
            case rhi_buffer_type::uniform: {
                data->cbv.BufferLocation = data->resource->GetGPUVirtualAddress();
                data->cbv.SizeInBytes = size;
                data->heap_index = d3d12_descriptor_alloc(&d3d12.cbv_srv_uav_heap);
                d3d12.device->CreateConstantBufferView(&data->cbv, d3d12_descriptor_cpu(&d3d12.cbv_srv_uav_heap, data->heap_index));
            } break;
            case rhi_buffer_type::storage: {
                log_warn("[WARN] D3D12 storage buffers aren't supported yet!");
            } break;
        }
    }

    void rhi_buffer_free(rhi_buffer *buffer)
    {
        d3d12_buffer *data = (d3d12_buffer*)buffer->reserved;
        SafeRelease(data->resource);
        delete data;
    }

    void rhi_buffer_upload(rhi_buffer *buffer, const void *data, uint64_t size)
    {
        d3d12_buffer *reserved = (d3d12_buffer*)buffer->reserved;
        void *pointer;
        HRESULT result = reserved->resource->Map(0, NULL, &pointer);
        if (FAILED(result)) {
            log_crit("[ERROR] Failed to map D3D12 buffer!");
        }
        memcpy(pointer , data, size);
        reserved->resource->Unmap(0, NULL);
    }
}
