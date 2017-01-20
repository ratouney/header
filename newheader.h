/*
** Header for project in /home/ratouney/cpp/header
**
** Made by Pipo
** Login  <maxime.de-la-fouchardiere@epitech.eu>
**
** Started on  Wed Nov 18 13:37:42 1998 Pipo
** Last update Fri Jan 20 21:40:50 2017
*/

#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


/*
** calib_add.c
*/

t_charray *calib_add_inter(t_charray *data, char **new, char *nf);
t_charray *calib_add_mid(t_charray *data, char *str, int pos);
t_charray *calib_add_end(t_charray *data, char *str);
t_charray *calib_add(t_charray *data, char *str, int pos, int mode);

/*
** calib_char.c
*/

void calib_char(char c);

/*
** calib_copy.c
*/

t_charray *calib_copy(t_charray *data);

/*
** calib_export.c
*/

char **calib_export(t_charray *data, int mode);

/*
** calib_import.c
*/

t_charray *calib_import(char **data, int given);

/*
** calib_nbr.c
*/

int	rec_calib_nbr(int nb);
int	calib_nbr(int nb);

/*
** calib_rem.c
*/

t_charray *calib_rem_inter(t_charray *data, char **new, char *nf);
t_charray *calib_rem(t_charray *data, int pos, int mode);

/*
** calib_show.c
*/

void calib_show(t_charray *data);

/*
** calib_write.c
*/

void calib_write(t_charray *array, char *str, int spot, int mode);

/*
** fillgen.c
*/

char *fillgen(int size);

/*
** my_strpaste.c
*/

char *stp(char *str, int mode);

/*
** newcharray.c
*/

t_charray *newcharray(int size);

/*
** charray.c
*/

char **charray(int size);

/*
** destroy_charray.c
*/

void destroy_charray(t_charray *data);

/*
** get_next_line.c
*/

int get_space(char *str, int mode);
char *my_strncat(char *str1, char *str2, int s, char null_end);
char *get_next_line(int fd);
