##
## Makefile for Headergen in /home/ratouney/header
## 
## Made by 
## Login   <ratouney >
## 
## Started on  Thu May 18 13:02:10 2017 Jean Pignouf
## Last update Thu May 18 14:26:14 2017 
##

SRC	=	main.c

OBJ	=	$(SRC:.c=.o)

NAME	=	header-generator

CFLAGS	+=	-I./include -I./lib/include -W -Wall -Wextra -g

all:		$(NAME)

$(NAME):	$(OBJ)
	make -C./lib
	gcc -o $(NAME) $(OBJ) -L./ -lrat

clean:
	make clean -C./lib
	rm -f $(OBJ)

fclean:		clean
	make fclean -C./lib
	rm -f $(NAME)

re:		fclean all

opti:		$(OBJ)
	make -C./lib
	gcc -Ofast -o $(NAME) $(OBJ) -L./ -lrat

.PHONY: all clean fclean re
