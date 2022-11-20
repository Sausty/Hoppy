/*
** EPITECH PROJECT, 2022
** hoppy
** File description:
** timer.h
*/

#ifndef TIMER_H_
#define TIMER_H_

namespace hoppy {
    /// @brief A timer
    struct timer {
        /// @brief The platform handle of a timerr
        void *timer_data;
    };

    /// @brief Initialises a timer
    /// @param t The timer to initialise
    void timer_init(timer *t);

    /// @brief Frees a timer
    /// @param t The timer to free
    void timer_free(timer *t);

    /// @brief Get the number of elapsed seconds ever since the timer's creation
    /// @param t A pointer to the timer
    /// @return The number of elapsed seconds
    float timer_get_elapsed_seconds(timer *t);

    /// @brief Restarts the given timer
    /// @param t A pointer to the timer
    void timer_restart(timer *t);
}

#endif /* !TIMER_H_ */
