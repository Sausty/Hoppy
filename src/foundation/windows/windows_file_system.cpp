/*
** EPITECH PROJECT, 2022
** hoppy
** File description:
** file_system_windows.cpp
*/

#include "foundation/file_system.h"
#include "foundation/log.h"

#include <Windows.h>

namespace hoppy {
    bool does_file_exist(char const *filepath) 
    {
        DWORD attrib = GetFileAttributesA(filepath);
        return (attrib != INVALID_FILE_ATTRIBUTES);
    }
    
    int get_file_size(char const *filepath)
    {
        HANDLE file = CreateFileA(filepath, 
                                  GENERIC_READ, 
                                  FILE_SHARE_READ | FILE_SHARE_WRITE, 
                                  nullptr, 
                                  OPEN_EXISTING, 
                                  FILE_ATTRIBUTE_NORMAL, 
                                  nullptr);
        if (file == INVALID_HANDLE_VALUE)
            return -1;

        LARGE_INTEGER size;
        if (!GetFileSizeEx(file, &size)) {
            log_err("[ERROR] Failed to get file size! (Path: %s)", filepath);
            CloseHandle(file);
            return -1;
        }
        CloseHandle(file);
        return size.QuadPart;
    }

    char *read_file(char const *filepath)
    {
        int file_size = get_file_size(filepath);
        if (file_size == -1)
            return nullptr;

        char* buffer = new char[file_size + 1];
        HANDLE file = CreateFileA(filepath, 
                                  GENERIC_READ, 
                                  FILE_SHARE_READ | FILE_SHARE_WRITE, 
                                  nullptr, 
                                  OPEN_EXISTING, 
                                  FILE_ATTRIBUTE_NORMAL, 
                                  nullptr);
        if (!ReadFile(file, buffer, file_size, nullptr, nullptr)) {
            log_err("[ERROR] Failed to read entire file! (Path: %s)", filepath);
            CloseHandle(file);
            return nullptr;
        }
        buffer[file_size] = '\0';
        return buffer;
    }
}