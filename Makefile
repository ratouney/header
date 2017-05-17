##
## Makefile for Headergen in /home/ratouney/header
## 
## Made by 
## Login   <ratouney >
## 
## Started on  Wed May 17 14:20:56 2017 Jean Pignouf
## Last update Wed May 17 14:21:41 2017 
##

CC	=	gcc

NAME	=	header-generator

SRC	=	main.c

OBJ	=	$(SRC:.c=.o)

INCLUDE	=	-I./include

CFLAGS	+=	$(INCLUDE) -g

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ)

all:	$(NAME)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
