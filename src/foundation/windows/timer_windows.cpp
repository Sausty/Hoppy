/*
** EPITECH PROJECT, 2022
** hoppy
** File description:
** timer_windows.cpp
*/

#include "foundation/timer.h"

#include <Windows.h>

namespace hoppy {
    struct timer_win32 {
        long long start;
        long long frequency;
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

        long long now = large.QuadPart;
        long long time = now - data->start;

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