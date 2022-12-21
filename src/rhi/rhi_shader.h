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
    enum class rhi_shader_stage {
        vertex,
        fragment,
        pixel = fragment,
        geometry,
        compute,
        task,
        mesh
    };

    struct rhi_shader {
        std::string path;
        uint8_t *byte_code;
        uint32_t byte_code_size;
    };

    void rhi_shader_compile(rhi_shader *shader, const std::string& path, const std::string& entry_point, rhi_shader_stage stage);
    void rhi_shader_free(rhi_shader *shader);
}

#endif /* !RHI_SHADER_H_ */
