##
## EPITECH PROJECT, 2022
## Makefile
## File example:
## Makefile for the Hoppy engine
##

SOURCES = src/foundation/*.cpp
EXTENSION = lib
CXX_STATIC_FLAGS = -D_CRT_SECURE_NO_WARNINGS
INCLUDE_FLAGS = -Isrc
NAME = hoppy

ifeq ($(OS), Windows_NT)
	SOURCE_FOUNDATION = src/foundation/*.cpp src/foundation/windows/*cpp
	SOURCE_AUDIO = src/audio/direct_sound/*.cpp
	SOURCE_RHI = src/rhi/d3d12/*.cpp
	SOURCES = $(SOURCE_FOUNDATION) $(SOURCE_AUDIO) $(SOURCE_RHI)
	LINKS = -luser32.lib
	OUTPUT = hoppy.lib
else
	UNAME_S = $(shell uname -s)
	ifeq ($(UNAME_S), Linux)
		SOURCE_FOUNDATION = src/foundation/*.cpp src/foundation/linux/*.cpp
		SOURCE_AUDIO = src/audio/alsa/*.cpp
		SOURCE_RHI = src/rhi/vulkan/*.cpp
		SOURCES = $(SOURCE_FOUNDATION) $(SOURCE_AUDIO) $(SOURCE_RHI)
		LINKS = -lX11 -lX11-xcb -lxcb -L/usr/X11R6/lib
		OUTPUT = libhoppy.a
	endif
	ifeq ($(UNAME_S), Darwin)
		SOURCE_FOUNDATION = src/foundation/*.cpp src/foundation/macos/*.mm
		SOURCE_AUDIO = src/audio/core_audio/*.mm
		SOURCE_RHI = src/rhi/vulkan/*.cpp
		SOURCES = $(SOURCE_FOUNDATION) $(SOURCE_AUDIO) $(SOURCE_RHI)
		OUTPUT = libhoppy.a
	endif
endif

all: $(NAME)

$(NAME):
	clang -c -O0 $(SOURCES) $(CXX_STATIC_FLAGS) $(INCLUDE_FLAGS)
	ar rc $(OUTPUT) *.o
	rm -f *.d
	rm -f *.o

clean:
	rm -f *.d
	rm -f *.o
	rm -f *.pdb

fclean: clean
	rm -f $(OUTPUT)

re: fclean all

.PHONY = all, $(NAME), clean, fclean, re
