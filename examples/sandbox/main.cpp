/*
** EPITECH PROJECT, 2022
** sandbox
** File description:
** main.cpp
*/

#include "foundation/application.h"
#include "foundation/input.h"

#include <iostream>

int main()
{
    hoppy::application app;
    hoppy::application_init(&app, 1280, 720, "Hoppy Sandbox");
    while (hoppy::application_is_running(&app)) {
        if (hoppy::input_is_gamepad_button_pressed(0, hoppy::gamepad_button::a)) {
            hoppy::input_set_gamepad_vibration(0, 1.0f, 1.0f);
        }
        if (hoppy::input_is_gamepad_button_pressed(0, hoppy::gamepad_button::start)) {
            hoppy::application_close(&app);
        }
        hoppy::application_update(&app);
        hoppy::input_set_gamepad_vibration(0, 0.0f, 0.0f);
    }
    hoppy::application_free(&app);
}