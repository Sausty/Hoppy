/*
** EPITECH PROJECT, 2022
** Hoppy
** File description:
** log.h
*/

#ifndef LOG_H_
#define LOG_H_

namespace hoppy {
    /// @brief Outputs a message to stdout.
    /// @param color The color of the message given in ansi
    /// @param message The message to write
    void console_output(const char *color, const char *message);

    /// @brief Writes a blue message in the console.
    /// @param fmt The format of the string to print
    /// @param ... 
    void log_info(const char* fmt, ...);

    /// @brief Writes a yellow message in the console.
    /// @param fmt The format of the string to print
    /// @param ... 
    void log_warn(const char* fmt, ...);

    /// @brief Writes a red message in the console.
    /// @param fmt The format of the string to print
    /// @param ... 
    void log_err(const char* fmt, ...);

    /// @brief Writes a red message in the console and stops the application.
    /// @param fmt The format of the string to print
    /// @param ... 
    void log_crit(const char* fmt, ...);
}

#endif
