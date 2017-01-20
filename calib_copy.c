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

t_charray *calib_copy(t_charray *data)
{
    int count;
    t_charray *new;

    new = malloc(sizeof(t_charray));
    new->data = charray(data->size);
    new->fill = fillgen(data->size);
    new->size = data->size;
    count = 0;
    while (count < data->size)
    {
        if (data->fill[count] == '1')
        {
            new->data[count] = stp(data->data[count], 0);
            new->fill[count] = '1';
        }
        else
        {
            new->data[count] = NULL;
            new->fill[count] = '0';
        }
        count++;
    }
    return (new);
}