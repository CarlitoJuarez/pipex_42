/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjuarez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:03:47 by cjuarez           #+#    #+#             */
/*   Updated: 2024/07/22 17:03:30 by cjuarez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# ifndef BUF_SIZE
#  define BUF_SIZE 1024
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <limits.h>
# include <stddef.h>
# include <stdarg.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>

// basic functions 1

void	free_them_all(char *content, char **cmnd_list, char ***arg_list);

int		ft_strcmp(char *s1, char *s2);
int		is_space(char c);

char	*concat_full_path(char *cmnd, char *path);
char	*fill_str(int size, char *s, int index);

// basic functions 2

void	free_list(char **arr);
void	free_list_list(char ***arr);

int		file_check_r(char *file);
int		file_check_w(char *file);

char	*file_read(char *file);

// basic functions 3

void	free_it(char *s);
char	*special_case_dev(char *cmnd_list, char **arg_list);

// basic functions 4

int     make_smaller(int size);
size_t  ft_strlen(char *s);
char    *fill_nil();

// flags & paths

char	*find_path(char **envp, char *cmnd);

char	**flags(char *s);

// get_next_line

int		ft_strstr(char *s1, char *s2);

char	*get_next_line(int fd, char *limiter, int times);

// split function

char	**split_path(char *path);

// exec cmnd

char	*exec_cmnd(char *path, char **cmnd_list, char *content);
char	*exec_cmnd_dev(char *path, char **cmnd_list);

// ft_printf

int		ft_printf(const char *str, ...);
int		ft_putchar(int c);
int		ft_putstr(char *s);
int		ft_putaddress(void *p);
int		ft_puthexa(unsigned int n, const char c);
int		ft_putnbr(int n);
int		ft_putunsigned(unsigned long n);

char	*ft_strchr(const char *s, int c);

#endif
