/*
** headergen.c for CPE_2016_BSQ_bootstrap in /home/ratouney/CPE_2016_BSQ_bootstrap
**
** Made by ratouney
** Login   <ratouney@epitech.net>
**
** Started on  Sun Dec 11 09:59:08 2016 ratouney
** Last update Sun Dec 11 11:45:49 2016 John Doe
*/

#include "ratarray.h"

int	rec_calib_nbr(int nb)
{
  if (nb <= 9)
    {
      calib_char('0' + nb);
    }
  else
    {
      calib_nbr(nb / 10);
      calib_char ('0' + (nb % 10));
    }
}

int	calib_nbr(int nb)
{
  if (nb < 0)
    {
      calib_char('-');
      nb = nb * (-1);
    }
  rec_calib_nbr(nb);
}
