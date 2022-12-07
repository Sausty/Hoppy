/*
** EPITECH PROJECT, 2022
** Hoppy
** File description:
** application
*/

#include "foundation/application.h"

#include "audio/audio.h"
#include "foundation/input.h"
#include "rhi/rhi.h"

namespace hoppy {
    void application_init(application *app, int width, int height, char const *title) {
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
