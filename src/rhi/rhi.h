/*
** EPITECH PROJECT, 2022
** Hoppy
** File description:
** rhi
*/

#ifndef RHI_H_
#define RHI_H_

#define FRAMES_IN_FLIGHT 3

#include "foundation/window.h"

namespace hoppy {
    /// @brief Represents the RHI backend
    enum class rhi_backend {
        /// @brief D3D11 (UNSUPPORTED)
        d3d11,
        /// @brief D3D12
        d3d12,
        /// @brief METAL (UNSUPPORTED)
        metal,
        /// @brief OPENGL (UNSUPPORTED)
        opengl,
        /// @brief VULKAN (UNSUPPORTED)
        vulkan
    };

    /// @brief Represents the feature requests for the RHI
    struct rhi_feature_request {
        /// @brief Request mesh shaders
        bool mesh_shaders;
        /// @brief Request raytracing
        bool raytracing;
    };

    /// @brief Connects the render hardware interface to the given window
    /// @param w The window to connect to
    void rhi_connect_window(window *w);

    /// @brief Returns the current RHI backend
    /// @return See rhi_backend
    rhi_backend rhi_get_backend();

    /// @brief Initialises the render hardware interface
    /// @param requests The features of the RHI. Can be NULL
    void rhi_init(rhi_feature_request *requests);

    /// @brief Exits the render hardware interface
    void rhi_exit();

    /// @brief Sets up the rendering process
    void rhi_begin();

    /// @brief Finishes the rendering process
    void rhi_end();

    /// @brief Resizes the render hardware interface
    void rhi_resize(uint32_t width, uint32_t height);
}

#endif /* !RHI_H_ */
