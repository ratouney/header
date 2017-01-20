/*
** header for stringlib in /home/ratouney/libarray
**
** Made by ratouney ratouney
** Login   <ratouney@epitech.net>
**
** Started on  Thu Oct  6 13:49:57 2016 ratouney ratouney
** Last update Wed Nov 30 18:19:49 2016 ratouney
*/

#include <stdio.h>
#include "ratarray.h"

t_charray *newcharray(int size)
{
    t_charray *new;

    new = malloc(sizeof(t_charray));
    new->data = charray(size);
    new->fill = fillgen(size);
    new->size = size;
    return (new);
}
