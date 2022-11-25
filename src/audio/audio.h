/*
** EPITECH PROJECT, 2022
** Hoppy
** File description:
** audio
*/

#ifndef AUDIO_H_
#define AUDIO_H_

#include "foundation/window.h"

namespace hoppy {
    /// @brief Initialises the audio system
    void audio_init(window *w);
    
    /// @brief Exits the audio system
    void audio_exit();
}

#endif /* !AUDIO_H_ */
