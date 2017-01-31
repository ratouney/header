CC	=	gcc

NAME	=	header

SRC	=	calib_add.c             \
                calib_char.c            \
                calib_copy.c            \
                calib_export.c          \
                calib_import.c          \
                calib_nbr.c     \
                calib_rem.c     \
                calib_show.c            \
                calib_write.c          \
                charray.c          \
                destroy_charray.c          \
                fillgen.c          \
                get_next_line.c          \
                headergen.c          \
                my_strpaste.c          \
                newcharray.c 

OBJ		=	$(SRC:.c=.o)

INCLUDE	=

CFLAGS	+=	$(INCLUDE) -g

LDFLAGS	+=

$(NAME):	$(OBJ)
	$(CC) -Ofast -o $(NAME) $(OBJ)

all:	$(NAME)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
