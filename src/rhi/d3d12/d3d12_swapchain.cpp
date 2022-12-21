/*
** EPITECH PROJECT, 2022
** Hoppy
** File description:
** d3d12_swapchain
*/

#include "d3d12_swapchain.h"
#include "d3d12_data.h"
#include "foundation/log.h"

#include "math/HandmadeMath.hpp"

namespace hoppy {
    void d3d12_swapchain_init(d3d12_swapchain *swapchain)
    {
        hmm_vec2 window_size = window_get_size(d3d12.w);
        
        DXGI_SWAP_CHAIN_DESC1 desc = {};
        desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        desc.SampleDesc.Count = 1;
        desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        desc.BufferCount = FRAMES_IN_FLIGHT;
        desc.Scaling = DXGI_SCALING_NONE;
        desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
        desc.Width = window_size.X;
        desc.Height = window_size.Y;

        IDXGISwapChain1* temp;
        HRESULT result = d3d12.factory->CreateSwapChainForHwnd(d3d12.cmd_queue, (HWND)d3d12.w->platform_handle, &desc, NULL, NULL, &temp);
        if (FAILED(result)) {
            log_crit("[ERROR] Failed to create swapchain!");
        }
        temp->QueryInterface(IID_PPV_ARGS(&swapchain->swapchain));
        SafeRelease(temp);

        for (int i = 0; i < FRAMES_IN_FLIGHT; i++) {
            result = swapchain->swapchain->GetBuffer(i, IID_PPV_ARGS(&swapchain->swapchain_buffers[i]));
            if (FAILED(result)) {
                log_crit("[ERROR] Failed to get swapchain buffer!");
            }
            swapchain->render_targets[i] = d3d12_descriptor_alloc(&d3d12.rtv_heap);
            d3d12.device->CreateRenderTargetView(swapchain->swapchain_buffers[i], NULL, d3d12_descriptor_cpu(&d3d12.rtv_heap, swapchain->render_targets[i]));
        }
    }

    void d3d12_swapchain_free(d3d12_swapchain *swapchain)
    {
        for (int i = 0; i < FRAMES_IN_FLIGHT; i++) {
            SafeRelease(swapchain->swapchain_buffers[i]);
            d3d12_descriptor_free(&d3d12.rtv_heap, swapchain->render_targets[i]);
        }
        SafeRelease(swapchain->swapchain);
    }

    void d3d12_swapchain_present(d3d12_swapchain *swapchain, bool vsync)
    {
        swapchain->swapchain->Present(vsync, 0);
    }

    uint32_t d3d12_swapchain_get_image_index(d3d12_swapchain *swapchain)
    {
        if (!swapchain->swapchain) {
            log_crit("[ERROR] Swapchain is invalid!");
        }
        return swapchain->swapchain->GetCurrentBackBufferIndex();
    }

    void d3d12_swapchain_resize(d3d12_swapchain *swapchain, uint32_t width, uint32_t height)
    {
        if (swapchain->swapchain) {
            for (int i = 0; i < FRAMES_IN_FLIGHT; i++) {
                SafeRelease(swapchain->swapchain_buffers[i]);
                d3d12_descriptor_free(&d3d12.rtv_heap, swapchain->render_targets[i]);
            }
            swapchain->swapchain->ResizeBuffers1(0, width, height, DXGI_FORMAT_UNKNOWN, 0, NULL, NULL);
            for (int i = 0; i < FRAMES_IN_FLIGHT; i++) {
                HRESULT result = swapchain->swapchain->GetBuffer(i, IID_PPV_ARGS(&swapchain->swapchain_buffers[i]));
                if (FAILED(result)) {
                    log_crit("[ERROR] Failed to get swapchain buffer!");
                }
                swapchain->render_targets[i] = d3d12_descriptor_alloc(&d3d12.rtv_heap);
                d3d12.device->CreateRenderTargetView(swapchain->swapchain_buffers[i], NULL, d3d12_descriptor_cpu(&d3d12.rtv_heap, swapchain->render_targets[i]));
            }
        }
    }
}
