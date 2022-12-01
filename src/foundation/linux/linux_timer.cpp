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
    struct linux_timer {
        float start; 
    };
    
    void timer_init(timer *t)
    {
        t->timer_data = new linux_timer;
        linux_timer *data = reinterpret_cast<linux_timer*>(t->timer_data);
        data->start = timer_get_elapsed_seconds(t);
    }

    void timer_free(timer *t)
    {
        linux_timer *data = reinterpret_cast<linux_timer*>(t->timer_data);
        delete data;
    }

    float timer_get_elapsed_seconds(timer *t)
    {
        linux_timer *data = reinterpret_cast<linux_timer*>(t->timer_data);
        struct timespec ts;
        clock_gettime(0, &ts);
        return (float)(data->start - ((uint64_t)ts.tv_sec * 1000000000 + (uint64_t)ts.tv_nsec));
    }

    void timer_restart(timer *t)
    {
        linux_timer *data = reinterpret_cast<linux_timer*>(t->timer_data);
        data->start = timer_get_elapsed_seconds(t);
    }
}