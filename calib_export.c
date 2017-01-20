/*
** header for stringlib in /home/ratouney/libarray
**
** Made by ratouney ratouney
** Login   <ratouney@epitech.net>
**
** Started on  Thu Oct  6 13:49:57 2016 ratouney ratouney
** Last update Wed Nov 30 18:19:49 2016 ratouney
*/

#include "ratarray.h"

char **calib_export(t_charray *data, int mode)
{
    char **new;
    int count;

    new = charray(data->size);
    count = 0;
    while (count < data->size)
    {
        if (data->fill[count] == '1')
            new[count] = stp(data->data[count], 0);
        else
            new[count] = NULL;
        count++;
    }
    if (mode == 1)
        destroy_charray(data);
    return (new);
}