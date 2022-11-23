/*
** EPITECH PROJECT, 2022
** Hoppy
** File description:
** input.h
*/

#ifndef INPUT_H_
#define INPUT_H_

namespace hoppy {
    enum class gamepad_button {
        dpad_up,
        dpad_down,
        dpad_left,
        dpad_right,
        start,
        back,
        left_thumb,
        right_thumb,
        left_shoulder,
        right_shoulder,
        a,
        b,
        x,
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
