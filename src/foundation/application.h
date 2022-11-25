/*
** EPITECH PROJECT, 2022
** Hoppy
** File description:
** application
*/

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "window.h"

namespace hoppy {
    /// @brief Represents an application
    struct application {
        window w;
    };

    /// @brief Initialises the application and all of the engine's submodules
    /// @param app A pointer to the application
    /// @param width The width of the application window
    /// @param height The height of the application window
    /// @param title The title of the application window
    void application_init(application *app, int width, int height, char const *title);

    /// @brief Destroys the given application and shuts down the engine
    /// @param app A pointer to the application to destroy
    void application_free(application *app);

    /// @brief Returns whether or not the given application is running
    /// @param app The application to update
    /// @return True if it's running; otherwise false
    bool application_is_running(application *app);

    /// @brief Updates the given application and all of the engine's submodules
    /// @param app The application to update
    void application_update(application *app);
}

#endif /* !APPLICATION_H_ */
