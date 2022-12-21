/*
** EPITECH PROJECT, 2022
** Hoppy
** File description:
** rhi_shader
*/

#ifndef RHI_SHADER_H_
#define RHI_SHADER_H_

#include <string>
#include <cstdint>

namespace hoppy {
    /// @brief Represents the different shader types
    enum class rhi_shader_stage {
        /// @brief A vertex shader
        vertex,
        /// @brief A fragment shader
        fragment,
        /// @brief A pixel shader
        pixel = fragment,
        /// @brief A geometry shader
        geometry,
        /// @brief A compute shader
        compute,
        /// @brief A task shader
        task,
        /// @brief A mesh shader
        mesh
    };

    /// @brief Object representing a shader module
    struct rhi_shader {
        /// @brief The path of the shader
        std::string path;
        /// @brief The byte code of the shader, can be DXIL, SPIR-V or Metal byte code
        uint8_t *byte_code;
        /// @brief The size of the byte code
        uint32_t byte_code_size;
    };

    /// @brief Compiles a shader (can be HLSL, GLSL or MSL) to its respective byte code.
    /// @param shader A pointer to the sahder to compile
    /// @param path The path of the shader source
    /// @param entry_point The entry point of the shader
    /// @param stage The shader stage
    void rhi_shader_compile(rhi_shader *shader, const std::string& path, const std::string& entry_point, rhi_shader_stage stage);
    
    /// @brief Destroys the given shader
    /// @param shader The shader to destroy
    void rhi_shader_free(rhi_shader *shader);
}

#endif /* !RHI_SHADER_H_ */
