##
## EPITECH PROJECT, 2022
## Makefile
## File example:
## Makefile for the Hoppy engine
##

SOURCES = src/foundation/*.cpp \
		  src/foundation/windows/*.cpp
CXX_STATIC_FLAGS = -D_CRT_SECURE_NO_WARNINGS
INCLUDE_FLAGS = -Isrc
DISABLED_WARNINGS = -Wno-microsoft-cast
LINKS = -luser32.lib
NAME = hoppy

all: $(NAME)

$(NAME):
	g++ -c -O0 $(SOURCES) $(CXX_STATIC_FLAGS) $(INCLUDE_FLAGS) $(DISABLED_WARNINGS)
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