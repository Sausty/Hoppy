/*
** EPITECH PROJECT, 2022
** Hoppy
** File description:
** macos_file_system
*/

#include "foundation/file_system.h"

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

namespace hoppy {
    bool does_file_exist(char const *filepath) 
    {
        struct stat s;
        if (!stat(filepath, &s) == -1) {
            return false;
        }
        return true;
    }
    
    int get_file_size(char const *filepath)
    {
        struct stat s;
        if (stat(filepath, &s) == -1) {
            log_crit("[ERROR] File doesn't exist! (Path: %s)", filepath);
        }
        return s.st_size;
    }

    char *read_file(char const *filepath)
    {
        int size = get_file_size(filepath);
        if (size == -1) {
            return nullptr;
        }
        char *buffer = new char[size];
        int fd = open(filepath, O_RDONLY);
        read(fd, buffer, size);
        close(fd);
        return buffer;
    }
}
