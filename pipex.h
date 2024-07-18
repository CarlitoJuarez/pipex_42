#ifndef PIPEX_H
# define PIPEX_H

# ifndef BUF_SIZE
# define BUF_SIZE 1024
# endif

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>

// basic functions 1

void    free_them_all(char *content, char **cmnd_list, char ***arg_list);

int     ft_strcmp(char *s1, char *s2);
int     is_space(char c);

char    *concat_full_path(char *cmnd, char *path);
char    *fill_str(int size, char *s, int index);

// basic functions 2

void    free_list(char **arr);
void    free_list_list(char ***arr);

int     file_check_r(char *file);
int     file_check_w(char *file);

char    *file_read(char *file);

// flags & paths

char    *find_path(char **envp, char *cmnd);

char    **flags(char *s);

// get_next_line

char    *get_next_line(int fd, char *limiter);

// split function

char    **split_path(char *path);

// exec cmnd

char    *exec_cmnd(char *path, char **cmnd_list, char *content);

#endif
