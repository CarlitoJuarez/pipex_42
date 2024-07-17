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

// char    *ft_strjoin(char *s1, char *s2);
char    *concat(char *cmnd, char *path);
// char    *first(char *s);

int     ft_strcmp(char *s1, char *s2);
int     is_space(char c);

// basic functions 2

char    *file_read(char *file);

int     file_check_r(char *file);
int     file_check_w(char *file);

void    free_list(char **arr);
void    free_list_list(char ***arr);

// get_next_line

char    *get_next_line(int fd, char *limiter);

// exec cmnd

char    *exec_cmnd(char *path, char **cmnd_list, char *content);

// split function

char    **split_it(char *path);

#endif
