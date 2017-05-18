/*
** main.c for Headergen in /home/ratouney/header
** 
** Made by 
** Login   <ratouney >
** 
** Started on  Wed May 17 14:21:53 2017 Jean Pignouf
** Last update Fri May 19 00:34:53 2017 
*/

#include <dirent.h>
#include "flemme.h"

typedef struct	s_config
{
  char		*folder;
  char		*filename;
  char		*login;
}		t_config;

typedef struct	s_func
{
  char		*raw;
  char		*name;
  char		*ret;
  char		*ptr;
  char		*arg;

  struct s_func	*next;  
}		t_func;

typedef struct	s_ret
{
  char		*name;
  int		len;

  struct s_ret	*next;
}		t_ret;

typedef struct	s_file
{
  char		*name;

  char		**loaded;
  struct s_func	*func;
  
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

void		parse_proto(char *proto, t_func *new)
{
  int		count;
  int		name_start;
  int		ptr_start;
  int		rt_end;
  int		arg_end;
  int		arg_start;

  count = 0;
  while (proto[count] && proto[count] != '(')
    count++;
  arg_start = ++count;
  count = my_strlen(proto) - 1;
  while (count > 0 && proto[count] != ')')
    count--;
  arg_end = count;
  count = 0;
  while (proto[count] && proto[count] != ' ' && proto[count] != '\t')
    count++;
  rt_end = count;
  while (proto[count] && (proto[count] == ' ' || proto[count] == '\t'))
    count++;
  ptr_start = count;
  while (proto[count] && proto[count] == '*')
    count++;
  name_start = count;

  if (ptr_start != count)
    new->ptr = stcl(proto, ptr_start, count, 0);
  else
    new->ptr = NULL;
  new->ret = stcl(proto, 0, rt_end, 0);
  new->name = stcl(proto, name_start, arg_start - 1, 0);
  new->arg = stcl(proto, arg_start, arg_end, 0);
}

void		add_to_func(t_func **list, char *str, int mode)
{
  t_func	*temp;
  t_func	*new;

  if ((new = malloc(sizeof(t_func))) == NULL)
    return ;
  new->next = NULL;
  new->raw = stcl(str, 0, 0, 0);
  parse_proto(str, new);
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
	  if (my_strncmp(line, "void", 4) == 0 || my_strncmp(line, "int",3) == 0 || my_strncmp(line, "t_", 2) == 0 || my_strncmp(line, "float", 5) == 0 || my_strncmp(line, "double", 6) == 0 || my_strncmp(line, "char", 4) == 0)
	    add_to_func(&temp->func, line, 0);
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
	      data = calib_rem(data, count, 0);
	  count++;
	}
      free_tab(temp->loaded);
      temp->loaded = calib_export(data, 1);
      temp = temp->next;
    }
}

int		isinretlist(t_ret *list, char *str)
{
  t_ret		*temp;

  temp = list;
  while (temp)
    {
      if (my_strcmp(str, temp->name) == 0)
	return (1);
      temp = temp->next;
    }
  return (0);
}

void		add_to_retlist(t_ret **list, char *str, int mode)
{
  t_ret		*temp;
  t_ret		*new;

  if ((new = malloc(sizeof(t_ret))) == NULL)
    return ;
  new->next = NULL;
  new->name = stcl(str, 0, 0, 0);
  new->len = my_strlen(new->name);
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

void		retlenlist(t_file *list, t_ret **given)
{
  t_ret		*retlist;
  t_func	*fns;
  t_file	*temp;

  temp = list;
  retlist = (*given);
  while (temp)
    {
      fns = temp->func;
      while (fns)
	{
	  if (isinretlist(retlist, fns->ret) == 0)
	      add_to_retlist(given, fns->ret, 0);
	  fns = fns->next;
	}
      temp = temp->next;
    }
}

int		longest_ret(t_ret *list)
{
  int		max;
  t_ret		*temp;

  max = 0;
  temp = list;
  while (temp)
    {
      if (temp->len > max)
	max = temp->len;
      temp = temp->next;
    }
  return (max);
}

void		my_putchars(int fd, char c, int num)
{
  int		count;

  count = -1;
  while (++count < num)
    write(fd, &c, 1);    
}

void		print_header(int fd, char *user)
{
  char *data;
  time_t mytime;
  mytime = time(NULL);
  data = ctime(&mytime);
  
  dprintf(fd, "/*\n");
  dprintf(fd, "** Header for project in %s\n", getenv("PWD"));
  dprintf(fd, "**\n");
  dprintf(fd, "** Made by %s\n", getenv("USER"));
  dprintf(fd, "** Login <%s@epitech.eu>\n", user);
  dprintf(fd, "**\n");
  dprintf(fd, "** Started on  %s %s\n", stcl(data, 0, my_strlen(data) - 1, 0), getenv("USER"));
  dprintf(fd, "** Last update %s %s\n", stcl(data, 0, my_strlen(data) - 1, 0), getenv("USER"));
  dprintf(fd, "*/\n");
}

char		*capitalize_h(char *str)
{
  int		count;
  char		*new;

  new = malloc(sizeof(char) * (my_strlen(str) + 2));
  count = 0;
  while (str[count])
    {
      if (str[count] >= 'a' && str[count] <= 'z')
	new[count] = str[count] - 32;
      else if (str[count] == '.' || str[count] == '-' || str[count] == ' ')
	new[count] = '_';
      else
	new[count] = str[count];
      count++;
    }
  new[count] = '_';
  new[count + 1] = '\0';
  return (new);
}

void		print_func(t_file *list, char *output, char *user)
{
  int		fd;
  t_file	*temp;
  t_ret		*retlist = NULL;
  int		maxlen;
  int		curlen;
  t_func	*data;

  fd = open(output, O_WRONLY | O_CREAT | O_TRUNC);
  chmod(output, S_IRUSR|S_IRGRP|S_IROTH|S_IWUSR|S_IWGRP|S_IWOTH);
  print_header(fd, user);
  dprintf(fd, "\n");
  dprintf(fd, "#ifndef %s\n", capitalize_h(output));
  dprintf(fd, "# define %s\n", capitalize_h(output));
  retlenlist(list, &retlist);
  maxlen = longest_ret(retlist);
  temp = list;
  while (temp)
    {
      data = temp->func;
      if (data == NULL)
	{
	  temp = temp->next;
	  continue;
	}
      dprintf(fd, "\n/*\n** %s\n*/\n\n", temp->name);
      while (data)
	{
	  curlen = my_strlen(data->ret);
	  if (curlen < maxlen)
	    {
	      write(fd, data->ret, my_strlen(data->ret));
	      write(fd, "\t", 1);
	    }
	  else
	    {
	      write(fd, data->ret, my_strlen(data->ret));
	      write(fd, "\t", 1);
	    }
	  dprintf(fd, "%s%s(%s);\n", (data->ptr == NULL ? "" : data->ptr), data->name, (data->arg == NULL ? "void" : data->arg));
	  data = data->next;
	}
      temp = temp->next;
    }
  dprintf(fd, "\n#endif /* !%s */\n", capitalize_h(output));
}

int		get_config(t_config *config, int argc, char **argv)
{
  int count;

  config->folder = NULL;
  config->login = NULL;
  config->filename = NULL;
  count = 1;
  while (argv[count])
    {
      if (my_strcmp(argv[count], "-d") == 0 || my_strcmp(argv[count], "--directory") == 0)
	{
	  if (argv[count + 1] == NULL)
	    {
	      printf("header-generator: option requires an argument -- '%s'.\n", argv[count]);
	      return (-1);
	    }
	  if (access(argv[count + 1], R_OK) != 0)
	    {
	      printf("header-generator: Could not access folder %s.\n", argv[count + 1]);
	      return (-1);
	    }
	  else
	    config->folder = stcl(argv[count + 1], 0, 0, 0);
	  count++;
	}
      else if (my_strcmp(argv[count], "-u") == 0 || my_strcmp(argv[count], "--username") == 0)
	{
	  if (argv[count + 1] == NULL)
	    {
	      printf("header-generator: option requires an argument -- '%s'.\n", argv[count]);
	      return (-1);
	    }
	  else
	    config->login = stcl(argv[count + 1], 0, 0, 0);
	  count++;
	}
      else if (my_strcmp(argv[count], "-f") == 0 || my_strcmp(argv[count], "--filename") == 0)
	{
	  if (argv[count + 1] == NULL)
	    {
	      printf("header-generator: option requires an argument -- '%s'.\n", argv[count]);
	      return (-1);
	    }
	  else
	    config->filename = stcl(argv[count + 1], 0, 0, 0);
	  count++;
	}
      else if (my_strcmp(argv[count], "-h") == 0 || my_strcmp(argv[count], "--help") == 0)
	{
	  printf("\e[32mUSAGE\e[39m: header-generator [-d|--directory] [-f|--filename] [-u|--username]\n");
	  printf("\n\e[33mDirectory\e[39m :\n");
	  printf("\tSpecifies the starting directory to look for source files\n");
	  printf("\tBy default, current folder is selected [./]\n");
	  printf("\n\e[33mFilename\e[39m :\n");
	  printf("\tSpecifies the name of the output file, which is overwritten\n");
	  printf("\tBy default, output file is called [header.h]\n");
	  printf("\n\e[33mUsername\e[39m :\n");
	  printf("\tSpecifies the username to be applied in the header\n");
	  printf("\tBy default, the system username is taken [%s]\n", getenv("USER"));
	  printf("\n\nMade by Ratouney\nMore info :\n\t\e[36mhttp://github.com/ratouney/header\e[39m\n");
	  return (-1);
	}
	count++;
    }
  if (config->folder == NULL)
    config->folder = stcl("./", 0, 0, 0);
  if (config->login == NULL)
    config->login = getenv("USER");
  if (config->filename == NULL)
    config->filename = stcl("header.h", 0, 0, 0);
  return (0);
}

int		main(int argc, char **argv)
{
  t_config	config;
  t_file	*list;
  char		*output;
  char		*user;

  if (get_config(&config, argc, argv) == -1)
    return (1);
  list = NULL;
  scan_dir(&list, config.folder, 1);
  if (argc >= 3 || argv[2] == NULL)
    output = argv[2];
  else
    output = fuse(fuse(getenv("PWD"), "--", 0), "header.h", 0);
  if (argc >= 4)
    user = argv[3];
  else
    user = getenv("USER");
  load_stuff(list);
  //clear_lines(list);
  lf_void(list);
  print_func(list, config.filename, config.login);
  free_list(list);
  return (0);
}
