/*
** EPITECH PROJECT, 2022
** Hoppy
** File description:
** input.h
*/

#ifndef INPUT_H_
#define INPUT_H_

#include "math/HandmadeMath.h"

#define JOYSTICK_LEFT 0
#define JOYSTICK_RIGHT 1

namespace hoppy {
    /// @brief An enum representing all the buttons of a gamepad
    enum class gamepad_button {
        /// @brief Up direction on the d-pad
        dpad_up,
        /// @brief Down direction on the d-pad
        dpad_down,
        /// @brief Left direction on the d-pad
        dpad_left,
        /// @brief Right direction on the d-pad
        dpad_right,
        /// @brief Start button
        start,
        /// @brief Back button
        back,
        /// @brief Left thumb button
        left_thumb,
        /// @brief Right thumb button
        right_thumb,
        /// @brief Left shoulder button
        left_shoulder,
        /// @brief Right shoulder button
        right_shoulder,
        /// @brief The A button
        a,
        /// @brief The B button
        b,
        /// @brief The X button
        x,
        /// @brief The Y button
        y
    };

    /// @brief Initialises the input system
    void input_init();

    /// @brief Exits the input system
    void input_exit();

    /// @brief Updates the input system
    void input_update();

    /// @brief Checks whether or not the given gamepad button is pressed
    /// @param index The gamepad index
    /// @param button The button to check
    /// @return True if the button is pressed; otherwise false
    bool input_is_gamepad_button_pressed(int index, gamepad_button button);

    /// @brief Returns the trigger values of the given gamepad
    /// @param index The gamepad index
    /// @return A vector containing the trigger values
    hmm_v2 input_get_gamepad_triggers(int index);

    /// @brief Returns the joystick values of the given gamepad
    /// @param index The gamepad index
    /// @param joystick The joystick to check (0 is left, 1 is right)
    /// @return A vector containing the joystick values
    hmm_v2 input_get_gamepad_joystick(int index, int joystick);

    /// @brief Sets the speed of the rumble motors of the given gamepad
    /// @param index The gamepad index
    /// @param left The left speed of the motor, ranged [0, 1]
    /// @param right The right speed of the motor, ranged [0, 1]
    void input_set_gamepad_vibration(int index, float left, float right);
}

#endif /* !INPUT_H_ */
