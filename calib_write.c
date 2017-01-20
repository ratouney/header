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

void calib_write(t_charray *array, char *str, int spot, int mode)
{
    if (spot >= array->size || spot < 0)
        write(1, "Out of reach\n", 13);
    else
    {
        if ((mode - (mode % 10)) < 10)
        {
            if (array->fill[spot] == '0')
            {
                array->data[spot] = stp(str, mode % 10);
                array->fill[spot] = '1';
            }
            else
            {
                write(1, "Line is already occupied : ", 27);
                calib_nbr(spot);
                write(1, "\nTo overwrite, use the appropriate macro\n", 40);
            }
        }
        else
        {
            if (array->fill[spot] == '1')
                free(array->data[spot]);
            array->data[spot] = stp(str, mode % 10);
        }
    }
}