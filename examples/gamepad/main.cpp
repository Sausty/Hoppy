/*
** EPITECH PROJECT, 2022
** sandbox
** File description:
** main.cpp
*/

#include "foundation/application.h"
#include "foundation/input.h"
#include "foundation/log.h"

#include <iostream>

int main()
{
    // Declare a hoppy application
    hoppy::application app;
    // Initialise hoppy with a window titled "Hoppy Sandbox" in 1280x720
    hoppy::application_init(&app, 1280, 720, "Hoppy Sandbox");
    while (hoppy::application_is_running(&app)) {
        // Check button state
        if (hoppy::input_is_gamepad_button_pressed(0, hoppy::gamepad_button::a)) {
            hoppy::log_info("A button was pressed!");
        }
        // Set vibration state
        if (hoppy::input_is_gamepad_button_pressed(0, hoppy::gamepad_button::b)) {
            hoppy::input_set_gamepad_vibration(0, 1.0f, 1.0f);
        }
        // Exit on button press
        if (hoppy::input_is_gamepad_button_pressed(0, hoppy::gamepad_button::start)) {
            hoppy::application_close(&app);
        }
        // Get trigger state (r2 and l2)
        hmm_vec2 triggers = hoppy::input_get_gamepad_triggers(0);
        // Get left joystick
        hmm_vec2 left_joystick = hoppy::input_get_gamepad_joystick(0, JOYSTICK_LEFT);
        // Get right joystick
        hmm_vec2 right_joystick = hoppy::input_get_gamepad_joystick(0, JOYSTICK_RIGHT);
        // Update the application
        hoppy::application_update(&app);
        // Reset the gamepad vibration
        hoppy::input_set_gamepad_vibration(0, 0.0f, 0.0f);
    }
    // Cleanup the application
    hoppy::application_free(&app);
}