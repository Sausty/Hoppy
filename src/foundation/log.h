/*
** EPITECH PROJECT, 2022
** Hoppy
** File description:
** log.h
*/

#ifndef LOG_H_
#define LOG_H_

namespace hoppy {
    void console_output(const char *color, const char *message);
    void log_info(const char* fmt, ...);
    void log_warn(const char* fmt, ...);
    void log_err(const char* fmt, ...);
    void log_crit(const char* fmt, ...);
}

#endif
