/*
** EPITECH PROJECT, 2022
** hoppy
** File description:
** timer_windows.cpp
*/

#include "foundation/timer.h"

#include <Windows.h>
#include <stdint.h>

namespace hoppy {
    struct timer_win32 {
        int64_t start;
        int64_t frequency;
    };

    void timer_init(timer *t)
    {
        t->timer_data = new timer_win32;
        timer_win32* data = reinterpret_cast<timer_win32*>(t->timer_data);

        LARGE_INTEGER large;
        QueryPerformanceCounter(&large);
        data->start = large.QuadPart;

        QueryPerformanceFrequency(&large);
        data->frequency = large.QuadPart;
    }

    void timer_free(timer *t)
    {
        delete reinterpret_cast<timer_win32*>(t->timer_data);
    }

    float timer_get_elapsed_seconds(timer *t)
    {
        timer_win32* data = reinterpret_cast<timer_win32*>(t->timer_data);

        LARGE_INTEGER large;
        QueryPerformanceCounter(&large);

        int64_t now = large.QuadPart;
        int64_t time = now - data->start;

        return (float)((double)time / data->frequency);
    }

    void timer_restart(timer *t)
    {
        timer_win32* data = reinterpret_cast<timer_win32*>(t->timer_data);

        LARGE_INTEGER large;
        QueryPerformanceCounter(&large);
        data->start = large.QuadPart;

        QueryPerformanceFrequency(&large);
        data->frequency = large.QuadPart;   
    }
}