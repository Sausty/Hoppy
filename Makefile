##
## EPITECH PROJECT, 2022
## Makefile
## File example:
## Makefile for the Hoppy engine
##

SOURCES = src/foundation/*.cpp
CXX_FLAGS = -g -MD -static -fdeclspec
NAME = hoppy

all: $(NAME)

$(NAME):
	clang -c $(SOURCES) $(CXX_FLAGS) -o $(NAME).o
	llvm-ar rc $(NAME).lib $(NAME).o

clean:
	rm -f $(NAME).d
	rm -f $(NAME).o

fclean: clean
	rm -f $(NAME).lib

re: fclean all

.PHONY = all, $(NAME), clean, fclean, re