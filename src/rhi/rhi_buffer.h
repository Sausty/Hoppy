/*
** EPITECH PROJECT, 2022
** Hoppy
** File description:
** rhi_buffer
*/

#ifndef RHI_BUFFER_H_
#define RHI_BUFFER_H_

#include <cstdint>

namespace hoppy {
    /// @brief Represents the different types of a buffer
    enum class rhi_buffer_type {
        /// @brief A vertex buffer
        vertex,
        /// @brief An index buffer
        index,
        /// @brief A uniform or constant buffer
        uniform,
        /// @brief A storage or unordered access buffer, used in compute shaders
        storage
    };

    /// @brief A structure representing a buffer stored in GPU memory
    struct rhi_buffer {
        /// @brief The type of the buffer
        rhi_buffer_type type;
        /// @brief The size of the buffer
        uint64_t size;
        /// @brief The stride of the buffer
        uint64_t stride;
        /// @brief The RHI backend of the buffer
        void *reserved;
    };

    /// @brief Creates a GPU buffer with the given size and type
    /// @param buffer A pointer to the buffer to create
    /// @param stride The stride of the buffer
    /// @param size The size of the buffer
    /// @param type The type of the buffer
    void rhi_buffer_init(rhi_buffer *buffer, uint64_t stride, uint64_t size, rhi_buffer_type type);

    /// @brief Destroys a GPU buffer
    /// @param buffer The buffer to destroy
    void rhi_buffer_free(rhi_buffer *buffer);

    /// @brief Uploads memory to the GPU
    /// @param buffer A pointer to the buffer to upload to
    /// @param data The data to upload
    /// @param size The size of the data
    void rhi_buffer_upload(rhi_buffer *buffer, const void *data, uint64_t size);
}

#endif /* !RHI_BUFFER_H_ */
