/*
** EPITECH PROJECT, 2022
** Hoppy
** File description:
** application
*/

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "window.h"

namespace hoppy {
    struct application {
        window w;
    };

    void application_init(application *app, int width, int height, char const *title);
    void application_free(application *app);
    bool application_is_running(application *app);
    void application_update(application *app);
}

#endif /* !APPLICATION_H_ */
