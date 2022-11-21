##
## EPITECH PROJECT, 2022
## examples/sandbox/Makefile
## File example:
## Makefile for the sanbdox example
##

NAME = sandbox
SOURCES = *.cpp
CXX_FLAGS = -g -MD -fdeclspec
INCLUDE_FLAGS = -I../../src
LINKER_FLAGS = -L../../ -lhoppy.lib -luser32.lib

all: $(NAME)

$(NAME):
	clang $(SOURCES) $(CXX_FLAGS) -o $(NAME).exe $(INCLUDE_FLAGS) $(LINKER_FLAGS)

clean:
	rm -f $(NAME).d
	rm -f $(NAME).ilk
	rm -f $(NAME).pdb
	
fclean: clean
	rm -f $(NAME).exe

re: fclean all

.PHONY: all, $(NAME), clean, fclean, re
