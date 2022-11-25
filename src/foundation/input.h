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

    enum class keyboard_key {
        /** @brief The backspace key. */
        backspace = 0x08,
        /** @brief The enter key. */
        enter = 0x0D,
        /** @brief The tab key. */
        tab = 0x09,
        /** @brief The shift key. */
        shift = 0x10,
        /** @brief The Control/Ctrl key. */
        control = 0x11,

        /** @brief The pause key. */
        pause = 0x13,
        /** @brief The Caps Lock key. */
        capital = 0x14,

        /** @brief The Escape key. */
        escape = 0x1B,

        convert = 0x1C,
        nonconvert = 0x1D,
        accept = 0x1E,
        modechange = 0x1F,

        /** @brief The spacebar key. */
        space = 0x20,
        prior = 0x21,
        next = 0x22,
        /** @brief The end key. */
        end = 0x23,
        /** @brief The home key. */
        home = 0x24,
        /** @brief The left arrow key. */
        left = 0x25,
        /** @brief The up arrow key. */
        up = 0x26,
        /** @brief The right arrow key. */
        right = 0x27,
        /** @brief The down arrow key. */
        down = 0x28,
        select = 0x29,
        print = 0x2A,
        execute = 0x2B,
        snapshot = 0x2C,
        /** @brief The insert key. */
        insert = 0x2D,
        /** @brief The delete key. */
        del = 0x2E,
        help = 0x2F,

        /** @brief The 0 key */
        zero = 0x30,
        /** @brief The 1 key */
        one = 0x31,
        /** @brief The 2 key */
        two = 0x32,
        /** @brief The 3 key */
        three = 0x33,
        /** @brief The 4 key */
        four = 0x34,
        /** @brief The 5 key */
        five = 0x35,
        /** @brief The 6 key */
        six = 0x36,
        /** @brief The 7 key */
        seven = 0x37,
        /** @brief The 8 key */
        eight = 0x38,
        /** @brief The 9 key */
        nine = 0x39,

        /** @brief The A key. */
        a = 0x41,
        /** @brief The B key. */
        b = 0x42,
        /** @brief The C key. */
        c = 0x43,
        /** @brief The D key. */
        d = 0x44,
        /** @brief The E key. */
        e = 0x45,
        /** @brief The F key. */
        f = 0x46,
        /** @brief The G key. */
        g = 0x47,
        /** @brief The H key. */
        h = 0x48,
        /** @brief The I key. */
        i = 0x49,
        /** @brief The J key. */
        j = 0x4A,
        /** @brief The K key. */
        k = 0x4B,
        /** @brief The L key. */
        l = 0x4C,
        /** @brief The M key. */
        m = 0x4D,
        /** @brief The N key. */
        n = 0x4E,
        /** @brief The O key. */
        o = 0x4F,
        /** @brief The P key. */
        p = 0x50,
        /** @brief The Q key. */
        q = 0x51,
        /** @brief The R key. */
        r = 0x52,
        /** @brief The S key. */
        s = 0x53,
        /** @brief The T key. */
        t = 0x54,
        /** @brief The U key. */
        u = 0x55,
        /** @brief The V key. */
        v = 0x56,
        /** @brief The W key. */
        w = 0x57,
        /** @brief The X key. */
        x = 0x58,
        /** @brief The Y key. */
        y = 0x59,
        /** @brief The Z key. */
        z = 0x5A,

        /** @brief The left Windows/Super key. */
        lwin = 0x5B,
        /** @brief The right Windows/Super key. */
        rwin = 0x5C,
        apps = 0x5D,

        /** @brief The sleep key. */
        sleep = 0x5F,

        /** @brief The numberpad 0 key. */
        numpad0 = 0x60,
        /** @brief The numberpad 1 key. */
        numpad1 = 0x61,
        /** @brief The numberpad 2 key. */
        numpad2 = 0x62,
        /** @brief The numberpad 3 key. */
        numpad3 = 0x63,
        /** @brief The numberpad 4 key. */
        numpad4 = 0x64,
        /** @brief The numberpad 5 key. */
        numpad5 = 0x65,
        /** @brief The numberpad 6 key. */
        numpad6 = 0x66,
        /** @brief The numberpad 7 key. */
        numpad7 = 0x67,
        /** @brief The numberpad 8 key. */
        numpad8 = 0x68,
        /** @brief The numberpad 9 key. */
        numpad9 = 0x69,
        /** @brief The numberpad multiply key. */
        multiply = 0x6A,
        /** @brief The numberpad add key. */
        add = 0x6B,
        /** @brief The numberpad separator key. */
        separator = 0x6C,
        /** @brief The numberpad subtract key. */
        subtract = 0x6D,
        /** @brief The numberpad decimal key. */
        decimal = 0x6E,
        /** @brief The numberpad divide key. */
        divide = 0x6F,

        /** @brief The F1 key. */
        f1 = 0x70,
        /** @brief The F2 key. */
        f2 = 0x71,
        /** @brief The F3 key. */
        f3 = 0x72,
        /** @brief The F4 key. */
        f4 = 0x73,
        /** @brief The F5 key. */
        f5 = 0x74,
        /** @brief The F6 key. */
        f6 = 0x75,
        /** @brief The F7 key. */
        f7 = 0x76,
        /** @brief The F8 key. */
        f8 = 0x77,
        /** @brief The F9 key. */
        f9 = 0x78,
        /** @brief The F10 key. */
        f10 = 0x79,
        /** @brief The F11 key. */
        f11 = 0x7A,
        /** @brief The F12 key. */
        f12 = 0x7B,
        /** @brief The F13 key. */
        f13 = 0x7C,
        /** @brief The F14 key. */
        f14 = 0x7D,
        /** @brief The F15 key. */
        f15 = 0x7E,
        /** @brief The F16 key. */
        f16 = 0x7F,
        /** @brief The F17 key. */
        f17 = 0x80,
        /** @brief The F18 key. */
        f18 = 0x81,
        /** @brief The F19 key. */
        f19 = 0x82,
        /** @brief The F20 key. */
        f20 = 0x83,
        /** @brief The F21 key. */
        f21 = 0x84,
        /** @brief The F22 key. */
        f22 = 0x85,
        /** @brief The F23 key. */
        f23 = 0x86,
        /** @brief The F24 key. */
        f24 = 0x87,

        /** @brief The number lock key. */
        numlock = 0x90,

        /** @brief The scroll lock key. */
        scroll = 0x91,

        /** @brief The numberpad equal key. */
        numpad_equal = 0x92,

        /** @brief The left shift key. */
        lshift = 0xA0,
        /** @brief The right shift key. */
        rrshift = 0xA1,
        /** @brief The left control key. */
        lcontrol = 0xA2,
        /** @brief The right control key. */
        rcontrol = 0xA3,
        /** @brief The left alt key. */
        lalt = 0xA4,
        /** @brief The right alt key. */
        ralt = 0xA5,

        /** @brief The semicolon key. */
        semicolon = 0xBA,
        /** @brief The plus key. */
        plus = 0xBB,
        /** @brief The comma key. */
        comma = 0xBC,
        /** @brief The minus key. */
        minus = 0xBD,
        /** @brief The period key. */
        period = 0xBE,
        /** @brief The slash key. */
        slash = 0xBF,
        /** @brief The grave key. */
        grave = 0xC0,
    };


    /// @brief Initialises the input system
    void input_init();

    /// @brief Exits the input system
    void input_exit();

    /// @brief Updates the input system
    void input_update();

    /// @briefs Checks whether or not the given key is pressed
    bool input_is_key_pressed(keyboard_key key);

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
