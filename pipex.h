/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjuarez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:03:47 by cjuarez           #+#    #+#             */
/*   Updated: 2024/07/30 10:31:40 by cjuarez          ###   ########.fr       */
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

int		is_space(char c);
int		ft_strcmp(char *s1, char *s2);
int		any_of_those(char *content);

char	*fill_str(int size, char *s, int index);
char	*concat_full_path(char *cmnd, char *path);

// basic functions 2

void	handle_err(int errnum);

int		file_check_r(char *file);
int		file_check_w(char *file);

size_t	ft_strlen(char *s);

char	*file_read(char *file);

// basic functions 3

void	print_p(char *c, char *cmnd, int access, char *last);

int		check_num(char *s);

long	ft_atoi(char *s);

// basic function 4

void	exit_fail(char *content, char **cmnd_list, int fd);

int		check_ls(char **arr, char *str);

char	*pass_c(char *c);

// fill

char	*fill_nil(char *path);
char	*fill_acc(char *this);
char	*fill_dir(void);
char	*fill_cont(int errnum);
char	*fill_this(char *this);

// flags & paths

int		trim_cmnd(char *cmnd);

char	*find_path(char **envp, char *cmnd, char *content, char *last);

char	**flags(char *s);

// free

void	free_it(char **s);
void	free_a(char *content, char **cmnd_list, char ***arg_list);
void	free_list(char **arr);
void	free_list_list(char ***arr);

// get_next_line

int		ft_strstr(char *s1, char *s2);

char	*get_next_line(int fd, char *limiter, int times);

// special case /dev/stdin

char	*special_dev(char **cmnd_list, char ***arg_list, int i, char **envp);

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
