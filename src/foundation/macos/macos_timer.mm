/*
** EPITECH PROJECT, 2022
** Hoppy
** File description:
** macos_timer
*/

#include "foundation/timer.h"

#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <cstdint>

namespace hoppy {
    struct macos_timer {
        float start; 
    };

    void timer_init(timer *t)
    {
        t->timer_data = new macos_timer;
        macos_timer *data = reinterpret_cast<macos_timer*>(t->timer_data);
        data->start = timer_get_elapsed_seconds(t);
    }

    void timer_free(timer *t)
    {
        macos_timer *data = reinterpret_cast<macos_timer*>(t->timer_data);
        delete data;
    }

    float timer_get_elapsed_seconds(timer *t)
    {
        macos_timer *data = reinterpret_cast<macos_timer*>(t->timer_data);
        struct timespec ts;
        clock_gettime(0, &ts);
        return (float)(data->start - ((uint64_t)ts.tv_sec * 1000000000 + (uint64_t)ts.tv_nsec));
    }

    void timer_restart(timer *t)
    {
        macos_timer *data = reinterpret_cast<macos_timer*>(t->timer_data);
        data->start = timer_get_elapsed_seconds(t);
    }
}