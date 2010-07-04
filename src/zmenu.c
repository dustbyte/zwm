#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>

#include "zwm.h"
#include "log.h"

extern		char **environ;

char		*get_path(void)
{
  char		**cur;

  cur = environ;
  while (*cur && strncmp("PATH=", *cur, 5) != 0)
    ++cur;
  return (*cur);
}

int		list_strcmp(void *d1, void *d2)
{
  return (-strcmp((char *)d1, (char *)d2));
}

void		add_exec_to_list(Wm *wm, char *dir)
{
  struct stat	sb;
  DIR		*d;
  struct dirent *de;
  char		fpath[4096];
  char		*s;
  t_elem	*e;

  if (lstat(dir, &sb) != -1 && S_ISDIR(sb.st_mode))
    if ((d = opendir(dir)) != NULL)
      while ((de = readdir(d)) != NULL)
	{
	  bzero(fpath, 4096);
	  strncpy(fpath, dir, 4096);
	  strcat(fpath + strlen(dir), "/");
	  strncat(fpath + strlen(dir) + 1, de->d_name, 4095 - strlen(dir));
	  if (lstat(fpath, &sb) != -1 && S_ISREG(sb.st_mode))
	    {
	      if ((e = malloc(sizeof(*e))) == NULL)
		wlog(SYS | ERR, "malloc");
	      if ((s = malloc(sizeof(*s) * (strlen(de->d_name) + 1))) == NULL)
		wlog(SYS | ERR, "malloc");
	      strcpy(s, de->d_name);
	      list_insert(&wm->zmenu.exec_list, e, s, list_strcmp);
	    }
	}
}

void		zmenu_create_list(Wm *wm)
{
  int		i;
  char		*path;
  char		*dir;

  path = get_path();
  if (path)
    {
      path += 5;
      list_init(&(wm->zmenu.exec_list));
      while (*path)
	{
	  i = 0;
	  if (*path == ':')
	    ++path;
	  while (path[i] && path[i] != ':')
	    ++i;
	  if ((dir = malloc(sizeof(*dir) * (i + 1))) == NULL)
	    wlog(SYS | ERR, "malloc");
	  strncpy(dir, path, i);
	  dir[i] = '\0';
	  add_exec_to_list(wm, dir);
	  free(dir);
	  path += i;
	}
    }
}

void		init_call_zmenu(Wm *wm)
{
  t_elem	*e;

  bzero(wm->zmenu.buf, 4096);
  zmenu_create_list(wm);
  wm->zmenu.status = ZMENU_RUN;
}

int		zmenu(Wm *wm)
{
  if (wm->zmenu.status == ZMENU_CALL)
    init_call_zmenu(wm);
  if (wm->zmenu.status == ZMENU_RUN)
    (void)wm;
  else if (wm->zmenu.status == ZMENU_NORMAL)
    (void)wm;
  return (0);
}
