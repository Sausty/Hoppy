/*
** EPITECH PROJECT, 2022
** sandbox
** File description:
** main.cpp
*/

#include "foundation/application.h"

#include <iostream>

int main()
{
    hoppy::application app;
    hoppy::application_init(&app, 1280, 720, "Hoppy Sandbox");
    while (hoppy::application_is_running(&app)) {
        hoppy::application_update(&app);
    }
    hoppy::application_free(&app);
}