/*
** EPITECH PROJECT, 2022
** Hoppy
** File description:
** application
*/

#include "foundation/application.h"

#include "audio/audio.h"
#include "foundation/event.h"
#include "foundation/input.h"
#include "foundation/log.h"
#include "rhi/rhi.h"

namespace hoppy {
    bool application_resize(event_type type, void *sender, void *listener_inst, event data) {
        uint32_t width = data.payload.u32[0];
        uint32_t height = data.payload.u32[1];
        if (type == event_type::resize) {
            rhi_resize(width, height);
        }
        log_info("[INFO] Resized application with dimensions (%d, %d)", width, height);
        return true;
    }

    void application_init(application *app, int width, int height, char const *title) {
        log_info("[INFO] Created application with window (%d, %d) named %s", width, height, title);

        event_system_init();
        event_system_register(event_type::resize, nullptr, application_resize);
        window_init(&app->w, width, height, title);
        input_init();
        audio_init(&app->w);
        rhi_connect_window(&app->w);
        rhi_init();
    }

    void application_close(application *app)
    {
        if (!app->was_closed) {
            application_free(app);
            app->was_closed = true;
        }
    }

    void application_free(application *app)
    {
        if (!app->was_closed) {
            rhi_exit();
            audio_exit();
            input_exit();
            window_free(&app->w);
            event_system_unregister(event_type::resize, nullptr, application_resize);
            event_system_exit();
        }
    }

    bool application_is_running(application *app)
    {
        return window_is_open(&app->w);
    }

    void application_update(application *app)
    {
        input_update();
        window_poll_events(&app->w);
    }
}
