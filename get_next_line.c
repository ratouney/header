/*
** advanced.h for adv_wireframe in /home/ratouney/bswireframe
**
** Made by ratouney
** Login   <ratouney@epitech.net>
**
** Started on  Sun Nov 20 11:37:31 2016 ratouney
** Last update Mon Dec 12 10:46:43 2016 John Doe
*/

#include "get_next_line.h"

int get_space(char *str, int mode)
{
    int count;

    count = 0;
    if (str == NULL)
        return (0);
    while (str[count] != '\0')
    {
        if (mode == 1 && str[count] == '\n')
            return (count);
        count++;
    }
    return (count);
}

char *my_strncat(char *str1, char *str2, int s, char null_end)
{
    int size;
    char *new;
    int count;
    int cunt;

    size = get_space(str1, 0) + get_space(str2, 0);
    if (size > s && s >= 0)
        size = s;
    if (size == 0 && null_end)
        return (NULL);
    if ((new = malloc(sizeof(char) * (size + 1))) == NULL)
        return (NULL);
    new[size] = '\0';
    count = 0;
    while (str1 && str1[count] && count < size)
    {
        new[count] = str1[count];
        count++;
    }
    cunt = -1;
    while (str2 && str2[++cunt] && count + cunt < size)
        new[count + cunt] = str2[cunt];
    return (new);
}

char *get_next_line(int fd)
{
    static char *save = NULL;
    char buffer[READ_SIZE + 1];
    char *line[2];
    int end[2];

    *end = 0;
    while (42)
    {
        if ((end[1] = get_space(save, 1)) != get_space(save, 0) || *end)
        {
            line[0] = my_strncat((line[1] = save), NULL, end[1], *end);
            save = (save && save[end[1]] ? my_strncat(&save[end[1] + 1], NULL, -1, 0) : NULL);
            free(line[1]);
            return (line[0]);
        }
        else
        {
            if ((end[1] = read(fd, buffer, READ_SIZE)) < 0)
                return (NULL);
            else if (end[1] < READ_SIZE)
                *end = 1;
            buffer[end[1]] = '\0';
            save = my_strncat((line[1] = save), buffer, -1, 0);
            free(line[1]);
        }
    }
}