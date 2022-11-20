/*
** EPITECH PROJECT, 2022
** hoppy
** File description:
** file_system.h
*/

#ifndef FILE_SYSTEM_H_
#define FILE_SYSTEM_H_

namespace hoppy {
    /// @brief Returns whether or not a file exists.
    /// @param filepath The path of the file to check.
    /// @return True if the file exists, otherwise false
    bool does_file_exist(char const *filepath);

    /// @brief Gets the size of the given file
    /// @param filepath THe filepath of the file
    /// @return The size of the file
    int get_file_size(char const *filepath);

    /// @brief Allocates and returns a buffer containing the given file's contents
    /// @param filepath The filepath of the file to read
    /// @return An allocated buffer containing the contents of the file
    char *read_file(char const *filepath);
}

#endif /* !FILE_SYSTEM_H_ */
