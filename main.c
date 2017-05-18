/*
** main.c for Headergen in /home/ratouney/header
** 
** Made by 
** Login   <ratouney >
** 
** Started on  Wed May 17 14:21:53 2017 Jean Pignouf
** Last update Thu May 18 14:21:12 2017 
*/

#include <dirent.h>
#include "flemme.h"

typedef struct	s_file
{
  char		*name;

  int		fd;
  char		**loaded;
  char		**func;
  
  struct s_file *next;
}		t_file;

char		**copytab(char **ding, int mode)
{
  char		**new;
  int		count;

  count = 0;
  while (ding[count])
    count++;
  if ((new = malloc(sizeof(char *) * (count + 1))) == NULL)
    return (NULL);
  new[count] = NULL;
  count = -1;
  while (ding[++count])
    {
      new[count] = stcl(ding[count], 0, 0, 0);
      if (mode == 1)
	free(ding[count]);
    }
  if (mode == 1)
    free(ding);
  return (new);
}

void		add_to_list(t_file **list, char *str, int mode)
{
  t_file	*temp;
  t_file	*new;

  new = malloc(sizeof(t_file));
  new->name = stcl(str, 0, 0, 0);
  new->loaded = NULL;
  new->func = NULL;
  new->next = NULL;
  if ((*list) == NULL)
    (*list) = new;
  else
    {
      temp = (*list);
      while (temp->next)
	temp = temp->next;
      temp->next = new;
    }
  if (mode == 1)
    free(str);
}

void		scan_dir(t_file **list, char *path, int level)
{
  struct dirent **namelist;
  char		*name_of_file = NULL;
  char		*toadd = NULL;
  struct stat	info;
  int n;

  if (path[my_strlen(path) - 1] != '/')
    toadd = fuse(path, "/", 0);
  else
    toadd = stcl(path, 0, 0, 0);
  n = scandir(path, &namelist, NULL, alphasort);
  if (n < 0)
    perror("scandir");
  else
    {
      while (n--)
	{
	  name_of_file = fuse(toadd, namelist[n]->d_name, 0);
	  stat(name_of_file, &info);
	  if (info.st_mode & S_IFDIR)
	    if (namelist[n]->d_name[0] == '.')
	      free(name_of_file);
	    else
	      {
		if (name_of_file[0] == '.' && name_of_file[1] == '/')
		  name_of_file = stcl(name_of_file, 2, 0, 1);
		scan_dir(list, name_of_file, level + 1);
		free(name_of_file);
	      }
	  else
	    {
	      if (name_of_file[0] == '.' && name_of_file[1] == '/')
		name_of_file = stcl(name_of_file, 2, 0, 1);
	      if (name_of_file[my_strlen(name_of_file) - 1] == 'c')
		add_to_list(list, name_of_file, 0);
	      free(name_of_file);
	    }
	  free(namelist[n]);
	}
      free(namelist);
    }
  free(toadd);
}

void		free_list(t_file *list)
{
  t_file	*prev;
  t_file	*temp;
  
  temp = list;
  while (temp)
    {
      prev = temp;
      free(temp->name);
      temp = temp->next;
      free(prev);
    }
}

void		load_stuff(t_file *list)
{
  t_file	*temp;
  t_content	data;
  int		count;

  temp = list;
  while (temp)
    {
      data = loadfile(temp->name);
      if (data.errno == 0)
	{
	  printf("Successfully loaded : [\e[32m%s\e[39m] = [%d bytes]\n", temp->name, my_strlen(data.raw));
	  temp->loaded = copytab(data.line, 0);
	}
      else
	printf("Error loading       : [\e[31m%s\e[39m]\n", temp->name);
      loadfile_destroy(data);
      temp = temp->next;
    }
}

int		is_declar(char *str)
{
  int		count;
  int		op;
  int		cl;

  op = 0;
  cl = 0;
  count = -1;
  while (str[++count])
    if (str[count] == '(')
      op++;
    else if (str[count] == ')')
      cl++;
  if (op > 0 && cl > 0 && op == cl)
    return (1);
  else
    return (0);    
}

void		lf_void(t_file *list)
{
  t_file	*temp;
  char		*line;
  int		count;

  temp = list;
  while (temp)
    {
      count = 0;
      while (temp->loaded[count])
	{
	  line = temp->loaded[count];
	  if (line[0] == '\0' || line[0] == '\n' || is_declar(line) == 0)
	    {
	      count++;
	      continue;
	    }
	  while (line[0] == ' ' || line[0] == '\t')
	    line++;
	  if (my_strncmp(line, "void", 4) == 0)
	    printf("[%s]\n", line);
	  count++;
	}
      temp = temp->next;
    }  
}

void		lf_t_(t_file *list)
{
  t_file	*temp;
  char		*line;
  int		count;

  temp = list;
  while (temp)
    {
      count = 0;
      while (temp->loaded[count])
	{
	  line = temp->loaded[count];
	  if (line[0] == '\0' || line[0] == '\n' || is_declar(line) == 0)
	    {
	      count++;
	      continue;
	    }
	  while (line[0] == ' ' || line[0] == '\t')
	    line++;
	  if (my_strncmp(line, "t_", 2) == 0)
	    printf("[%s]\n", line);
	  count++;
	}
      temp = temp->next;
    }  
}

void		clear_lines(t_file *list)
{
  t_charray	*data;
  t_file	*temp;
  char		*line;
  int		count;

  temp = list;
  while (temp)
    {
      count = 0;
      data = calib_import(temp->loaded, -1);
      while (data->data[count])
	{
	  line = data->data[count];
	  if (line[0] == '\0')
	    printf("Remove line %d in [%s]\n", count, temp->name);
	  count++;
	}
      destroy_charray(data);
      temp = temp->next;
    } 	
}

int		main(int argc, char **argv)
{
  t_file *list;

  list = NULL;
  if (argc >= 2)
    scan_dir(&list, argv[1], 1);
  else
    scan_dir(&list, "./", 1);
  load_stuff(list);
  clear_lines(list);
  /*  lf_void(list);
      lf_t_(list);*/
  free_list(list);
  return (0);
}
