/*
** EPITECH PROJECT, 2022
** sandbox
** File description:
** main.cpp
*/

#include "foundation/log.h"
#include "foundation/window.h"
#include "foundation/input.h"

#include <iostream>

int main()
{
    hoppy::window window;
    hoppy::window_init(&window, 1280, 720, "Hoppy Window");
    hoppy::input_init();

    while (hoppy::window_is_open(&window))
    {
        hoppy::input_update();
        hoppy::window_poll_events(&window);
    }
    hoppy::input_exit();
    hoppy::window_free(&window);
}