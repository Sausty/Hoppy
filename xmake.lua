add_rules("mode.debug", "mode.release")

option("rhi")
    if is_plat("windows") then
        set_default("d3d12")
    elseif is_plat("linux") then
        set_default("vulkan")
    elseif is_plat("macos") then
        set_default("metal")
    end

if is_plat("linux") then
    add_requires("libx11", "libxcb")
end

target("Hoppy")
    set_kind("static")
    add_headerfiles("src/(**.h)", "src/(**.hpp)")
    add_files("src/**.cpp")
    add_includedirs("src", { public = true })

    if get_config("rhi") == "d3d12" then
        remove_files("src/rhi/d3d11/**")
        remove_files("src/rhi/metal/**")
        remove_files("src/rhi/opengl/**")
        remove_files("src/rhi/vulkan/**")
    elseif get_config("rhi") == "vulkan" then
        remove_files("src/rhi/d3d11/**")
        remove_files("src/rhi/metal/**")
        remove_files("src/rhi/opengl/**")
        remove_files("src/rhi/d3d12/**")
    elseif get_config("rhi") == "metal" then
        remove_files("src/rhi/d3d11/**")
        remove_files("src/rhi/vulkan/**")
        remove_files("src/rhi/opengl/**")
        remove_files("src/rhi/d3d12/**")
    end

    if is_plat("windows", "mingw") then
        add_syslinks("user32")
        remove_files("src/audio/alsa/**")
        remove_files("src/audio/core_audio/**")
        remove_files("src/*/linux/**")
        remove_files("src/*/macos/**")
    elseif is_plat("linux") then
        add_packages("libx11", "libxcb")
        remove_files("src/audio/core_audio/**")
        remove_files("src/audio/direct_sound/**")
        remove_files("src/*/windows/**")
        remove_files("src/*/macos/**")
    elseif is_plat("macosx") then
        add_files("src/**.mm")
        remove_files("src/audio/alsa/**")
        remove_files("src/audio/direct_sound/**")
        remove_files("src/*/linux/**")
        remove_files("src/*/macos/**")
    end

target("example_gamepad")
    add_files("examples/gamepad/**.cpp")
    add_deps("Hoppy")

target("example_sandbox")
    add_files("examples/sandbox/**.cpp")
    add_deps("Hoppy")
