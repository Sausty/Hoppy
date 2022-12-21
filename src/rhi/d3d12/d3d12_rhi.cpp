/*
** EPITECH PROJECT, 2022
** Hoppy
** File description:
** d3d12_rhi
*/

#include "d3d12_data.h"
#include "d3d12_dynamic_lib.h"
#include "foundation/log.h"

#include <string>

#define D3D12CreateDevice d3d12CreateDevice_
#define D3D12GetDebugInterface d3d12GetDebugInterface_
#define CreateDXGIFactory createDXGIFactory_
#define D3D12SerializeRootSignature d3d12SerializeRootSignature_
#define D3DCompile d3dCompile_

namespace hoppy {
    D3D12_CREATE_DEVICE(D3D12CreateDeviceStub) { return S_FALSE; }
    D3D12_GET_DEBUG_INTERFACE(D3D12GetDebugInterfaceStub) { return S_FALSE; }
    CREATE_DXGI_FACTORY(CreateDXGIFactoryStub) { return S_FALSE; }
    D3D12_SERIALIZE_ROOT_SIGNATURE(D3D12SerializeRootSignatureStub) { return S_FALSE; }
    D3D_COMPILE(D3DCompileStub) { return S_FALSE; }

    static d3d12_create_device *d3d12CreateDevice_ = D3D12CreateDeviceStub;
    static d3d12_get_debug_interface *d3d12GetDebugInterface_ = D3D12GetDebugInterfaceStub;
    static create_dxgi_factory *createDXGIFactory_ = CreateDXGIFactoryStub;
    static d3d12_serialize_root_signature *d3d12SerializeRootSignature_ = D3D12SerializeRootSignatureStub;
    static d3d_compile *d3dCompile_ = D3DCompileStub;

    d3d12_state d3d12;

    void get_hardware_adapter(IDXGIFactory3* factory, IDXGIAdapter1** ret_adapter, bool request_high_performance_adapter)
    {
        *ret_adapter = NULL;
        IDXGIAdapter1* adapter = 0;
        IDXGIFactory6* factory6;
        
        if (SUCCEEDED(factory->QueryInterface(IID_PPV_ARGS(&factory6)))) {
            for (uint32_t adapter_index = 0; SUCCEEDED(factory6->EnumAdapterByGpuPreference(adapter_index, request_high_performance_adapter == true ? DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE : DXGI_GPU_PREFERENCE_UNSPECIFIED, IID_PPV_ARGS(&adapter))); ++adapter_index) {
                DXGI_ADAPTER_DESC1 desc1;
                adapter->GetDesc1(&desc1);
    
                if (desc1.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
                    continue;
    
                if (SUCCEEDED(D3D12CreateDevice((IUnknown*)adapter, D3D_FEATURE_LEVEL_11_0, __uuidof(ID3D12Device*), NULL)))
                    break;
            }
        }
        
        if (adapter == NULL) {
            for (uint32_t adapter_index = 0; SUCCEEDED(factory->EnumAdapters1(adapter_index, &adapter)); ++adapter_index) {
                DXGI_ADAPTER_DESC1 desc1;
                adapter->GetDesc1(&desc1);

                if (desc1.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
                    continue;

                if (SUCCEEDED(D3D12CreateDevice((IUnknown*)adapter, D3D_FEATURE_LEVEL_11_0, __uuidof(ID3D12Device*), NULL)))
                    break;
            }
        }
        
        *ret_adapter = adapter;
    }

    void init_libs(void)
    {
        dynamic_library_load(&d3d12.d3d_lib, "d3d12.dll");
        D3D12CreateDevice = (d3d12_create_device*)dynamic_library_get_proc_addr(&d3d12.d3d_lib, "D3D12CreateDevice");
        D3D12GetDebugInterface = (d3d12_get_debug_interface*)dynamic_library_get_proc_addr(&d3d12.d3d_lib, "D3D12GetDebugInterface");
        D3D12SerializeRootSignature = (d3d12_serialize_root_signature*)dynamic_library_get_proc_addr(&d3d12.d3d_lib, "D3D12SerializeRootSignature");

        dynamic_library_load(&d3d12.dxgi_lib, "dxgi.dll");
        CreateDXGIFactory = (create_dxgi_factory*)dynamic_library_get_proc_addr(&d3d12.dxgi_lib, "CreateDXGIFactory");

        dynamic_library_load(&d3d12.d3dc_lib, "d3dcompiler_47.dll");
        D3DCompile = (d3d_compile*)dynamic_library_get_proc_addr(&d3d12.d3dc_lib, "D3DCompile");
    }

    void init_device(void)
    {
        HRESULT result = D3D12GetDebugInterface(IID_PPV_ARGS(&d3d12.debug));
        if (FAILED(result)) {
            log_crit("[ERROR] Failed to acquire D3D12 debug interface!");
        }
        d3d12.debug->EnableDebugLayer();

        result = CreateDXGIFactory(IID_PPV_ARGS(&d3d12.factory));
        if (FAILED(result)) {
            log_crit("[ERROR] Failed to create DXGI factory!");
        }
        get_hardware_adapter(d3d12.factory, &d3d12.adapter, true);

        result = D3D12CreateDevice(d3d12.adapter, D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&d3d12.device));
        if (FAILED(result)) {
            log_crit("[ERROR] Failed to create D3D12 device!");
        }

        result = d3d12.device->QueryInterface(IID_PPV_ARGS(&d3d12.debug_device));
        if (FAILED(result)) {
            log_crit("[ERROR] Failed to create debug device!");
        }

        ID3D12InfoQueue* info_queue = 0;
        d3d12.device->QueryInterface(IID_PPV_ARGS(&info_queue));

        info_queue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, TRUE);
        info_queue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, TRUE);

        D3D12_MESSAGE_SEVERITY supress_severities[] = {
            D3D12_MESSAGE_SEVERITY_INFO
        };

        D3D12_MESSAGE_ID supress_ids[] = {
            D3D12_MESSAGE_ID_CLEARRENDERTARGETVIEW_MISMATCHINGCLEARVALUE,
            D3D12_MESSAGE_ID_CLEARDEPTHSTENCILVIEW_MISMATCHINGCLEARVALUE,
            D3D12_MESSAGE_ID_MAP_INVALID_NULLRANGE,
            D3D12_MESSAGE_ID_UNMAP_INVALID_NULLRANGE,
        };

        D3D12_INFO_QUEUE_FILTER filter = {0};
        filter.DenyList.NumSeverities = ARRAYSIZE(supress_severities);
        filter.DenyList.pSeverityList = supress_severities;
        filter.DenyList.NumIDs = ARRAYSIZE(supress_ids);
        filter.DenyList.pIDList = supress_ids;

        info_queue->PushStorageFilter(&filter);
        info_queue->Release();

        DXGI_ADAPTER_DESC desc;
        d3d12.adapter->GetDesc(&desc);
        std::wstring w_device_name = desc.Description;
        std::string device_name = std::string(w_device_name.begin(), w_device_name.end());
        log_info("[INFO] Using GPU %s for D3D12", device_name.c_str());
    }

    void init_cmd_queue(void)
    {
        D3D12_COMMAND_QUEUE_DESC queue_desc = {};
        HRESULT result = d3d12.device->CreateCommandQueue(&queue_desc, IID_PPV_ARGS(&d3d12.cmd_queue));
        if (FAILED(result)) {
            log_crit("[ERROR] Failed to create D3D12 command queue!");
        }
    }

    void init_cmds(void)
    {
        HRESULT result;
        for (int i = 0; i < FRAMES_IN_FLIGHT; i++) {
            result = d3d12.device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&d3d12.cmd_allocators[i]));
            if (FAILED(result)) {
                log_crit("[ERROR] Failed to create D3D12 command allocator!");
            }
            result = d3d12.device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, d3d12.cmd_allocators[i], nullptr, IID_PPV_ARGS(&d3d12.cmd_lists[i]));
            if (FAILED(result)) {
                log_crit("[ERROR] Failed to create D3D12 command list!");
            }
            result = d3d12.cmd_lists[i]->Close();
            if (FAILED(result)) {
                log_crit("[ERROR] Failed to close D3D12 command list!");
            }
        }
    }

    rhi_backend rhi_get_backend()
    {
        return rhi_backend::d3d12;
    }

    void wait_device()
    {
        d3d12_fence_flush(&d3d12.device_fence);
    }

    void rhi_connect_window(window *w)
    {
        d3d12.w = w;
    }

    void rhi_init()
    {
        init_libs();
        init_device();
        init_cmd_queue();
        d3d12_fence_init(&d3d12.device_fence);
        d3d12_descriptor_heap_init(&d3d12.rtv_heap, D3D12_DESCRIPTOR_HEAP_TYPE_RTV, 512);
        d3d12_descriptor_heap_init(&d3d12.cbv_srv_uav_heap, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, 1'000'000);
        init_cmds();
        d3d12_swapchain_init(&d3d12.swapchain);
    }

    void rhi_exit()
    {
        d3d12_fence_flush(&d3d12.device_fence);

        d3d12_swapchain_free(&d3d12.swapchain);
        for (int i = 0; i < FRAMES_IN_FLIGHT; i++) {
            SafeRelease(d3d12.cmd_lists[i]);
            SafeRelease(d3d12.cmd_allocators[i]);
        }
        d3d12_descriptor_heap_free(&d3d12.cbv_srv_uav_heap);
        d3d12_descriptor_heap_free(&d3d12.rtv_heap);
        d3d12_fence_free(&d3d12.device_fence);
        SafeRelease(d3d12.cmd_queue);
        SafeRelease(d3d12.device);
        SafeRelease(d3d12.factory);
        SafeRelease(d3d12.adapter);
        d3d12.debug_device->ReportLiveDeviceObjects(D3D12_RLDO_IGNORE_INTERNAL | D3D12_RLDO_DETAIL);
        SafeRelease(d3d12.debug_device);
        SafeRelease(d3d12.debug);
        dynamic_library_free(&d3d12.d3dc_lib);
        dynamic_library_free(&d3d12.d3d_lib);
        dynamic_library_free(&d3d12.dxgi_lib);
    }

    void rhi_begin()
    {
        hmm_vec2 window_size = window_get_size(d3d12.w);
        if (window_size.X <= 0 || window_size.Y <= 0)
            return;

        d3d12.frame_index = d3d12_swapchain_get_image_index(&d3d12.swapchain);
        d3d12_fence_sync(&d3d12.device_fence, d3d12.frame_sync[d3d12.frame_index]);

        auto allocator = d3d12.cmd_allocators[d3d12.frame_index];
        auto list = d3d12.cmd_lists[d3d12.frame_index];

        allocator->Reset();
        list->Reset(allocator, NULL);

        D3D12_VIEWPORT viewport = {};
        viewport.Width = window_size.Width;
        viewport.Height = window_size.Height;
        viewport.TopLeftX = 0;
        viewport.TopLeftY = 0;

        D3D12_RECT scissor = {};
        scissor.left = 0;
        scissor.top = 0;
        scissor.right = window_size.Width;
        scissor.bottom = window_size.Height;

        D3D12_RESOURCE_BARRIER barrier = {};
        barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
        barrier.Transition.pResource = d3d12.swapchain.swapchain_buffers[d3d12.frame_index];
        barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
        barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
        list->ResourceBarrier(1, &barrier);

        list->RSSetViewports(1, &viewport);
        list->RSSetScissorRects(1, &scissor);

        const float clear[4] = { 0.3f, 0.4f, 0.8f, 1.0f };

        auto cpu_handle = d3d12_descriptor_cpu(&d3d12.rtv_heap, d3d12.swapchain.render_targets[d3d12.frame_index]);
        list->OMSetRenderTargets(1, &cpu_handle, false, NULL);
        list->ClearRenderTargetView(cpu_handle, clear, 0, NULL);
    }

    void rhi_end()
    {
        hmm_vec2 window_size = window_get_size(d3d12.w);
        if (window_size.X <= 0 || window_size.Y <= 0)
            return;

        auto list = d3d12.cmd_lists[d3d12.frame_index];
        
        D3D12_RESOURCE_BARRIER barrier = {};
        barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
        barrier.Transition.pResource = d3d12.swapchain.swapchain_buffers[d3d12.frame_index];
        barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
        barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
        list->ResourceBarrier(1, &barrier);
        list->Close();

        ID3D12CommandList* command_lists[] = { list };
        d3d12.cmd_queue->ExecuteCommandLists(1, command_lists);

        d3d12_swapchain_present(&d3d12.swapchain, true);
        d3d12.frame_sync[d3d12.frame_index] = d3d12_fence_signal(&d3d12.device_fence);
    }

    void rhi_resize(uint32_t width, uint32_t height)
    {
        d3d12_swapchain_resize(&d3d12.swapchain, width, height);
    }
}
