/*
** EPITECH PROJECT, 2022
** Hoppy
** File description:
** d3d12_rhi
*/

#include "d3d12_data.h"
#include "d3d12_dynamic_lib.h"

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

    void rhi_connect_window(window *w)
    {
        d3d12.w = w;
    }

    void rhi_init()
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

    void rhi_exit()
    {
        dynamic_library_free(&d3d12.d3dc_lib);
        dynamic_library_free(&d3d12.d3d_lib);
        dynamic_library_free(&d3d12.dxgi_lib);
    }
}
