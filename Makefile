##
## EPITECH PROJECT, 2022
## Makefile
## File example:
## Makefile for the Hoppy engine
##

SOURCES = src/foundation/*.cpp
CXX_STATIC_FLAGS = -D_CRT_SECURE_NO_WARNINGS
INCLUDE_FLAGS = -Isrc
NAME = hoppy

ifeq ($(OS), Windows_NT)
	SOURCES = src/foundation/*.cpp src/foundation/windows/*.cpp src/audio/direct_sound/*.cpp
	LINKS = -luser32.lib
endif

ifeq ($(OS), Linux)
	SOURCES = src/foundation/*.cpp src/foundation/linux/*.cpp src/audio/alsa/*.cpp
endif

ifeq ($(OS), Darwin)
	SOURCES = src/foundation/*.cpp src/foundation/macos/*.mm src/audio/core_audio/*.mm
endif

all: $(NAME)

$(NAME):
	g++ -c -O0 $(SOURCES) $(CXX_STATIC_FLAGS) $(INCLUDE_FLAGS)
	ar rc $(NAME).lib *.o
	rm -f *.d
	rm -f *.o

clean:
	rm -f *.d
	rm -f *.o
	rm -f *.pdb

fclean: clean
	rm -f $(NAME).lib

re: fclean all

.PHONY = all, $(NAME), clean, fclean, re