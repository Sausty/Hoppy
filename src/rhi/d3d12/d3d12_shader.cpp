/*
** EPITECH PROJECT, 2022
** Hoppy
** File description:
** d3d12_shader
*/

#include "d3d12_data.h"

#include <d3dcompiler.h>

#include "rhi/rhi_shader.h"
#include "foundation/file_system.h"
#include "foundation/log.h"

namespace hoppy {
    std::string get_shader_profile(rhi_shader_stage stage)
    {
        switch (stage)
        {
            case rhi_shader_stage::vertex: {
                return "vs_5_1";
            }
            case rhi_shader_stage::fragment: {
                return "ps_5_1";
            }
            case rhi_shader_stage::geometry: {
                return "gs_5_1";
            }
            case rhi_shader_stage::compute: {
                return "cs_5_1";
            }
            case rhi_shader_stage::task: {
                return "as_5_1";
            }
            case rhi_shader_stage::mesh: {
                return "ms_5_1";
            }
        }
    }

    void rhi_shader_compile(rhi_shader *shader, const std::string& path, const std::string& entry_point, rhi_shader_stage stage)
    {
        shader->path = path;
        
        std::string profile = get_shader_profile(stage);
        char* buffer = read_file(path.c_str());
        if (!buffer) {
            log_err("[ERROR] Shader %s doesn't exist!", path.c_str());
            return;
        }
        int size = get_file_size(path.c_str());

        ID3DBlob *blob;
        ID3DBlob *message;
        D3DCompile(buffer, size, NULL, NULL, NULL, entry_point.c_str(), profile.c_str(), D3DCOMPILE_DEBUG, 0, &blob, &message);
        if (message) {
            log_err("[ERROR] Failed to compile shader!");
            log_err("%s", message->GetBufferPointer());
            message->Release();
            return;
        }
        shader->byte_code_size = blob->GetBufferSize();
        shader->byte_code = new uint8_t[shader->byte_code_size];
        memcpy(shader->byte_code, blob->GetBufferPointer(), shader->byte_code_size);
        blob->Release();

        delete buffer;
    }

    void rhi_shader_free(rhi_shader *shader)
    {
        delete shader->byte_code;
    }
}
