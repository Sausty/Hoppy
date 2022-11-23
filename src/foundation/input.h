/*
** EPITECH PROJECT, 2022
** Hoppy
** File description:
** input.h
*/

#ifndef INPUT_H_
#define INPUT_H_

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
}

#endif /* !INPUT_H_ */
