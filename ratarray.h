/*
** header for stringlib in /home/ratouney/libarray
**
** Made by ratouney ratouney
** Login   <ratouney@epitech.net>
**
** Started on  Thu Oct  6 13:49:57 2016 ratouney ratouney
** Last update Wed Nov 30 18:19:49 2016 ratouney
*/

#ifndef RAT_ARRAY_H_
# define RAT_ARRAY_H_

# include <stdlib.h>
# include <unistd.h>
# include <string.h>

# define LA_SN 0
# define LA_SF 1
# define LA_BN 10
# define LA_BF 11

# define la_write(x, y, z, a) calib_write(x, y, z, a)
# define la_rem(x, y, z, a) y = calib_rem(x, z, a)
# define la_add(x, y, z, a, b) y = calib_add(x, z, a, b)
# define la_copy(x, y) y = calib_copy(x)
# define la_free(x) destroy_charray(x)
# define la_show(x) calib_show(x)
# define la_imp(x, y) calib_import(x, y)
# define la_exp(x, y) calib_export(x, y)

struct s_charray;

typedef struct s_charray t_charray;

struct s_charray
{
    char **data;
    char *fill;
    int size;
};

void calib_char(char c);
int calib_nbr(int a);
char *stp(char *,int);
char *fillgen(int size);
char **charray(int size);
t_charray *newcharray(int size);
void destroy_charray(t_charray *data);
void calib_write(t_charray *array, char *str, int spot, int mode);
void calib_show(t_charray *data);
t_charray *calib_add(t_charray *data, char *str, int pos, int mode);
t_charray *calib_rem(t_charray *data, int pos, int mode);
t_charray *calib_copy(t_charray *data);
t_charray *calib_import(char **data, int given);
char **calib_export(t_charray *data, int mode);

#endif  /* !RAT_ARRAY_H_ */