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

void destroy_charray(t_charray *data)
{
    int i;

    i = 0;
    while (i < data->size)
    {
        if (data->fill[i] == '1' && data->data[i] != NULL)
            free(data->data[i]);
        i++;
    }
    free(data->data);
    free(data->fill);
    free(data);
}