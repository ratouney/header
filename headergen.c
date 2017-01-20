/*
** headergen.c for CPE_2016_BSQ_bootstrap in /home/ratouney/CPE_2016_BSQ_bootstrap
**
** Made by ratouney
** Login   <ratouney@epitech.net>
**
** Started on  Sun Dec 11 09:59:08 2016 ratouney
** Last update Sun Dec 11 11:45:49 2016 John Doe
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include "ratarray.h"

typedef struct s_include
{
  int stdio;
  int unistd;
  int stdlib;
  int fcntl;
  int sys_types;
  int sys_stat;
  int dirent;
  int wait;
  int signl;
} t_inc;

char *get_next_line(int);

char *namecheck(char *str)
{
  int count = 0;
  int len = strlen(str);

  if (str[len - 1] == 'c' && str[len - 2] == '.')
    return (str);
  else
    return (NULL);
}

t_charray *show_include(t_inc data, t_charray *buffer)
{
  char *line;

  buffer = calib_add(buffer, "", 1, 0);
  //printf("\n\n/*\n** Don't forget to add these !\n**\n");
  if (data.stdio == 1)
  {
    buffer = calib_add(buffer, "#include <stdio.h>", 1, 0);
    //printf("**\t#include <stdio.h>\n");
  }
  if (data.unistd == 1)
  {
    buffer = calib_add(buffer, "#include <unistd.h>", 1, 0);
    //printf("**\t#include <unistd.h>\n");
  }
  if (data.stdlib == 1)
  {
    buffer = calib_add(buffer, "#include <stdlib.h>", 1, 0);
    //printf("**\t#include <stdlib.h>\n");
  }
  if (data.sys_types == 1)
  {
    buffer = calib_add(buffer, "#include <sys/types.h>", 1, 0);
    //printf("**\t#include <sys/types.h>\n");
  }
  if (data.sys_stat == 1)
  {
    buffer = calib_add(buffer, "#include <sys/stat.h>", 1, 0);
    //printf("**\t#include <sys/stat.h>\n");
  }
  if (data.fcntl == 1)
  {
    buffer = calib_add(buffer, "#include <fcntl.h>", 1, 0);
    //printf("**\t#include <fcntl.h>\n");
  }
  if (data.dirent == 1)
  {
    buffer = calib_add(buffer, "#include <dirent.h>", 1, 0);
    //printf("**\t#include <dirent.h>\n");
  }
  if (data.wait == 1)
  {
    buffer = calib_add(buffer, "#include <sys/wait.h>", 1, 0);
    //printf("**\t#include <sys/wait.h>\n");
  }
  if (data.signl == 1)
  {
    buffer = calib_add(buffer, "#include <signal.h>", 1, 0);
    //printf("**\t#include <signal.h>\n");
  }
  //printf("*/\n");
  return (buffer);
}

char *slinstr(char *str, int from, int to)
{
  char *res;
  int i;
  int j;

  i = 0;
  j = from;
  res = malloc(sizeof(char) * (j - i + 2));
  while (j <= to)
  {
    res[i] = str[j];
    i++;
    j++;
  }
  res[i] = '\0';
  return (res);
}

int my_strncmp(char *str, char *cmp, int size)
{
  int count;

  count = 0;
  while (str[count] != '\0' && cmp[count] != '\0' && count < size)
  {
    if (str[count] == '\0' && cmp[count] != '\0')
      return (1);
    else if (str[count] == '\0' && cmp[count] != '\0')
      return (2);
    else if (str[count] > cmp[count])
      return (1);
    else if (str[count] < cmp[count])
      return (2);
    else
      count++;
  }
  return (0);
}

int isdeclar(char *str)
{
  int count;
  int found;

  count = 0;
  found = 0;
  while (str[count] != '\0')
  {
    if (found == 0 && str[count] == '(')
      found = 1;
    else if (found == 1 && str[count] == ')')
      found = 2;
    else if (str[count] == '=')
      return (-1);
    count++;
  }
  return (found);
}

t_inc initdata(t_inc data)
{
  data.stdio = 0;
  data.unistd = 0;
  data.stdlib = 0;
  data.fcntl = 0;
  data.sys_types = 0;
  data.sys_stat = 0;
  data.dirent = 0;
  data.wait = 0;
  data.signl = 0;

  return (data);
}

char *concat(char *str, char *fuse)
{
  int count;
  int cunt;
  char *new;

  new = malloc(sizeof(char *) * (strlen(str) + strlen(fuse) + 1));
  count = -1;
  while (str[++count] != '\0')
    new[count] = str[count];
  cunt = -1;
  while (fuse[++cunt] != '\0')
    new[count + cunt] = fuse[cunt];
  new[count + cunt] = '\0';
  return (new);
}

t_charray *epihead(t_charray *buffer, char *user)
{
  char *line;
  char *data;
  time_t mytime;
  mytime = time(NULL);
  data = ctime(&mytime);

  buffer = calib_add(buffer, "", 1, 0);
  buffer = calib_add(buffer, "*/", 1, 0);
  line = concat("** Last update ", data);
  line[strlen(line) - 1] = '\0';
  buffer = calib_add(buffer, line, 1, 0);
  line = concat("** Started on  Wed Nov 18 13:37:42 1998 ", getenv("USER"));
  buffer = calib_add(buffer, line, 1, 0);
  buffer = calib_add(buffer, "**", 1, 0);
  line = concat("** Login  <", user);
  line = concat(line, "@epitech.eu>");
  buffer = calib_add(buffer, line, 1, 0);
  line = concat("** Made by ", getenv("USER"));
  buffer = calib_add(buffer, line, 1, 0);
  buffer = calib_add(buffer, "**", 1, 0);
  line = concat("** Header for project in ", getenv("PWD"));
  buffer = calib_add(buffer, line, 1, 0);
  buffer = calib_add(buffer, "/*", 1, 0);
  return (buffer);
}

void write_to_file(t_charray *buffer, char *filename)
{
  unlink(filename);
  FILE *data = fopen(filename, "w");
  int count;

  count = 1;
  while (count < buffer->size)
  {
    printf("%s\n", buffer->data[count]);
    fprintf(data, "%s\n", buffer->data[count]);
    count++;
  }
}

int main(int argc, char **argv)
{
  char *username;
  if (argc == 3)
    username = argv[2];
  else
    username = getenv("USER");

  char *filename;
  if (argc == 2)
    filename = argv[1];
  else
    filename = "newheader.h";

  t_inc data = initdata(data);
  t_charray *buffer = newcharray(1);
  DIR *directory;
  char *path;
  char *temp;
  char *file;
  struct dirent *current_folder;
  FILE *stream;
  char *line = NULL;
  int fd;
  int count;
  size_t len = 0;
  ssize_t read;

  directory = opendir(".");
  while ((current_folder = readdir(directory)) != NULL)
  {
    file = current_folder->d_name;
    if (strcmp(file, "headergen.c") == 0)
      continue ;
    if (file[strlen(file) - 1] == 'c' && file[strlen(file) - 2] == '.')
    {
      buffer = calib_add(buffer, "", -1, 0);
      buffer = calib_add(buffer, "/*", -1, 0);
      line = concat("** ", file);
      buffer = calib_add(buffer, line, -1, 0);
      free(line);
      buffer = calib_add(buffer, "*/", -1, 0);
      buffer = calib_add(buffer, "", -1, 0);
    }
    else
      continue;
    fd = open(file, O_RDONLY);
    while ((line = get_next_line(fd)) != NULL)
    {
      count = 0;
      while (line[count] == ' ')
        line = line + 1;
      if (my_strncmp(line, "char", 4) == 0 && isdeclar(line) == 2)
      {
        temp = concat(line, ";");
        buffer = calib_add(buffer, temp, -1, 0);
        //printf("%s;\n", line);
      }
      else if (my_strncmp(line, "double", 6) == 0 && isdeclar(line) == 2)
      {
        temp = concat(line, ";");
        buffer = calib_add(buffer, temp, -1, 0);
        //printf("%s;\n", line);
      }
      else if (my_strncmp(line, "void", 4) == 0 && isdeclar(line) == 2)
      {
        temp = concat(line, ";");
        buffer = calib_add(buffer, temp, -1, 0);
        //printf("%s;\n", line);
      }
      else if (my_strncmp(line, "t_", 2) == 0 && isdeclar(line) == 2)
      {
        temp = concat(line, ";");
        buffer = calib_add(buffer, temp, -1, 0);
        //printf("%s;\n", line);
      }
      else if (my_strncmp(line, "int", 3) == 0 && isdeclar(line) == 2)
      {
        temp = concat(line, ";");
        buffer = calib_add(buffer, temp, -1, 0);
        //printf("%s;\n", line);
      }
      else if (my_strncmp(line, "unsigned ", 9) == 0 && isdeclar(line) == 2)
      {
        temp = concat(line, ";");
        buffer = calib_add(buffer, temp, -1, 0);
        //printf("%s;\n", line);
      }
      else if (my_strncmp(line, "write", 5) == 0 || my_strncmp(line, "chdir", 5) == 0 || my_strncmp(line, "read", 5) == 0 || my_strncmp(line, "getcwd", 6) == 0)
        data.unistd = 1;
      else if (my_strncmp(line, "malloc", 6) == 0 || my_strncmp(line, "free", 4) == 0)
        data.stdlib = 1;
      else if (my_strncmp(line, "printf", 6) == 0)
        data.stdio = 1;
      else if (my_strncmp(line, "signal", 6) == 0)
        data.signl = 1;
      else if (my_strncmp(line, "open", 4) == 0)
      {
        data.fcntl = 1;
        data.sys_types = 1;
        data.sys_stat = 1;
      }
      else if (my_strncmp(line, "getpid", 6) == 0)
      {
        data.sys_types = 1;
        data.unistd = 1;
      }
      else if (my_strncmp(line, "wait", 4) == 0)
      {
        data.sys_types = 1;
        data.wait = 1;
      }
      else if (my_strncmp(line, "stat", 4) == 0 || my_strncmp(line, "lstat", 5) == 0 || my_strncmp(line, "fstat", 5) == 0)
      {
        data.unistd = 1;
        data.sys_types = 1;
        data.sys_stat = 1;
      }
    }
  }
  //printf("\n/*\n**\t   Made by Ratouney's C-Header Generator\n**\n**\n");
  //printf("**           __             _,-\"~^\"-.\n");
  //printf("**         _// )      _,-\"~`         `.\n");
  //printf("**       .\\ ( /`\"-,-\"`                 ;\n");
  //printf("**      / 6                             ;\n");
  //printf("**     /           ,             ,-\"     ;\n");
  //printf("**    (,__.--.      \\           /        ;\n");
  //printf("**     '   /`-.\\   |          |        `._________\n");
  //printf("**       _.-'_/`  )  )--...,,,___\\     \\-----------,)\n");
  //printf("**     (((\"~` _.-'.-'           __`-.   )         //\n");
  //printf("**          (((\"`             (((---~ \"`         //\n");
  //printf("**                                              ((________________\n");
  //printf("**                                              `----\"\"\"\"~~~~^^^```\n");
  //printf("*/\n");
  buffer = show_include(data, buffer);
  buffer = epihead(buffer, username);
  //la_show(buffer);
  write_to_file(buffer, filename);
  la_free(buffer);
}
