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

void calib_show(t_charray *data)
{
    int i;

    i = 0;
    printf("[Content of Charray]\n");
    printf("Status : [%s]\n\n", data->fill);
    while (i < data->size)
    {
        if (data->fill[i] == '1')
            printf("\t[%d] = [%s]\n", i, data->data[i]);
        else
            printf("\t[%d] = Undefined\n", i);
        i++;
    }
    printf("[End of Array]\n");
}