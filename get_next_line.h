/*
** main.c for CPE_2016_getnextline in /home/ratouney/CPE_2016_getnextline
**
** Made by ratouney
** Login   <ratouney@epitech.net>
**
** Started on  Sun Dec 11 10:09:24 2016 ratouney
** Last update Sun Dec 11 13:02:27 2016 ratouney
*/

#ifndef GET_NEXT_LINE_H_
# define GET_NEXT_LINE_H_

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>

# ifndef READ_SIZE
#  define READ_SIZE 4
# endif  /* !READ_SIZE */

char *get_next_line(int);
char *my_strncat(char *str1, char *str2, int s, char n);
int get_space(char *str, int mode);

#endif /* !GET_NEXT_LINE_H */
