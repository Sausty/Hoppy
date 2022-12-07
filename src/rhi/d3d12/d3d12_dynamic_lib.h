/*
** EPITECH PROJECT, 2022
** Hoppy
** File description:
** d3d12_dynamic_lib
*/

#ifndef D3D12_DYNAMIC_LIB_H_
#define D3D12_DYNAMIC_LIB_H_

#include <d3d12.h>

#define SafeRelease(obj) if (obj) { obj->lpVtbl->Release(obj); }

#define D3D12_CREATE_DEVICE(name) HRESULT name(IUnknown *pAdapter, D3D_FEATURE_LEVEL MinimumFeatureLevel, REFIID riid, void **ppDevice)
#define D3D12_GET_DEBUG_INTERFACE(name) HRESULT name(REFIID riid, void **ppvDebug)
#define CREATE_DXGI_FACTORY(name) HRESULT name(REFIID riid, void **ppFactory)
#define D3D12_SERIALIZE_ROOT_SIGNATURE(name) HRESULT name(const D3D12_ROOT_SIGNATURE_DESC* pRootSignature, D3D_ROOT_SIGNATURE_VERSION Version, ID3DBlob **ppBlob, ID3DBlob **ppErrorBlob)
#define D3D_COMPILE(name) HRESULT name(LPCVOID pSrcData, SIZE_T SrcDataSize, LPCSTR pSourceName, const D3D_SHADER_MACRO *pDefines, ID3DInclude *pInclude, LPCSTR pEntrypoint, LPCSTR pTarget, UINT Flags1, UINT Flags2, ID3DBlob **ppCode, ID3DBlob **ppErrorMsgs)

namespace hoppy {
    typedef D3D12_CREATE_DEVICE(d3d12_create_device);
    typedef D3D12_GET_DEBUG_INTERFACE(d3d12_get_debug_interface);
    typedef CREATE_DXGI_FACTORY(create_dxgi_factory);
    typedef D3D12_SERIALIZE_ROOT_SIGNATURE(d3d12_serialize_root_signature);
    typedef D3D_COMPILE(d3d_compile);
}

#endif /* !D3D12_DYNAMIC_LIB_H_ */
