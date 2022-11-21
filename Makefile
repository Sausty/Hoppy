##
## EPITECH PROJECT, 2022
## Makefile
## File example:
## Makefile for the Hoppy engine
##

SOURCES = src/foundation/*.cpp \
		  src/foundation/windows/*.cpp
CXX_FLAGS = -g -MD -static -fdeclspec
INCLUDE_FLAGS = -Isrc
DISABLED_WARNINGS = -Wno-microsoft-cast
LINKS = -luser32.lib
NAME = hoppy

all: $(NAME)

$(NAME):
	clang -c $(SOURCES) $(CXX_FLAGS) $(INCLUDE_FLAGS) $(DISABLED_WARNINGS)
	llvm-ar rc $(NAME).lib *.o
	rm -f *.d
	rm -f *.o
	rm -f *.pdb

clean:
	rm -f *.d
	rm -f *.o
	rm -f *.pdb

fclean: clean
	rm -f $(NAME).lib

re: fclean all

.PHONY = all, $(NAME), clean, fclean, re