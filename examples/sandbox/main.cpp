/*
** EPITECH PROJECT, 2022
** sandbox
** File description:
** main.cpp
*/

#include "foundation/log.h"
#include "foundation/window.h"

#include <iostream>

int main()
{
    hoppy::window window;
    hoppy::window_init(&window, 1280, 720, "Hoppy Window");

    while (hoppy::window_is_open(&window))
    {
        hoppy::window_poll_events(&window);
    }
    hoppy::window_free(&window);
}