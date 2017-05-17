##
## Makefile for Headergen in /home/ratouney/header
## 
## Made by 
## Login   <ratouney >
## 
## Started on  Wed May 17 14:20:56 2017 Jean Pignouf
## Last update Wed May 17 14:25:51 2017 
##

CC	=	gcc

NAME	=	header-generator

SRC	=	main.c

OBJ	=	$(SRC:.c=.o)

INCLUDE	=	-I./include -I./lib/include

CFLAGS	+=	$(INCLUDE) -g

$(NAME):	$(OBJ)
	make -C./lib
	cp lib/librat.a .
	$(CC) -o $(NAME) $(OBJ)	-L./ -lrat

all:	$(NAME)

clean:
	make clean -C./lib
	rm -f $(OBJ)

fclean:	clean
	make fclean -C./lib
	rm -f librat.a
	rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
