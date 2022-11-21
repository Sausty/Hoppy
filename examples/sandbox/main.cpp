/*
** EPITECH PROJECT, 2022
** sandbox
** File description:
** main.cpp
*/

#include "foundation/log.h"
#include "foundation/window.h"

int main()
{
    hoppy::window window;
    hoppy::window_init(&window, 1280, 720, "Hoppy Window");

    while (hoppy::window_is_open(&window))
    {
        hoppy::window_poll_events(&window, nullptr);
    }
    hoppy::window_free(&window);
}