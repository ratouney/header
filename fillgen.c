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

char *fillgen(int size)
{
    char *new;
    int i;

    i = 0;
    new = malloc(sizeof(char) * (size + 1));
    while (i < size)
    {
        new[i] = '0';
        i++;
    }
    new[i] = '\0';
    return (new);
}