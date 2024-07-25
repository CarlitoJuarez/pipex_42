/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmnd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjuarez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:08:33 by cjuarez           #+#    #+#             */
/*   Updated: 2024/07/22 16:09:30 by cjuarez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	handle_child(int *fd, int fd_2, char *path, char **cmnd_list)
{
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		perror("dup2 stdin");
		exit(EXIT_FAILURE);
	}
	close(fd[0]);
	if (dup2(fd_2, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(fd_2);
	execve(path, cmnd_list, NULL);
	perror("execve");
	free_list(cmnd_list);
	exit(EXIT_FAILURE);
}

char	*handle_parent(int *fd, int fd_2, char *content)
{
	close(fd[0]);
	close(fd_2);
	if (!content)
	{
		if (write(fd[1], "", 0) == -1)
		{
			perror("write2:");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (write(fd[1], content, strlen(content)) == -1)
		{
			perror("write:");
			exit(EXIT_FAILURE);
		}
	}
	close(fd[1]);
	wait(NULL);
	content = file_read(".txt");
	unlink(".txt");
	return (content);
}

char	*exec_cmnd(char *path, char **cmnd_list, char *content)
{
	int	pid;
	int	fd[2];
	int	tmp_fd;

	tmp_fd = open(".txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (tmp_fd == -1)
		return (free_list(cmnd_list), perror("open tmpfile:"), NULL);
	if (pipe(fd) == -1)
	{
		perror("pipe");
		free_list(cmnd_list);
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		free_list(cmnd_list);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
		handle_child(fd, tmp_fd, path, cmnd_list);
	else
		content = handle_parent(fd, tmp_fd, content);
	return (content);
}

void	handle_child_dev(int fd_2, char *path, char **cmnd_list)
{
	if (dup2(fd_2, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(fd_2);
	execve(path, cmnd_list, NULL);
	perror("execve");
	free_list(cmnd_list);
	exit(EXIT_FAILURE);
}

char	*exec_cmnd_dev(char *path, char **cmnd_list)
{
	int		pid;
	int		tmp_fd;
	char	*content;

	content = NULL;
	tmp_fd = open(".txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (tmp_fd == -1)
		return (perror("open tmpfile:"), NULL);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		free_list(cmnd_list);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
		handle_child_dev(tmp_fd, path, cmnd_list);
	else
	{
		wait(NULL);
		content = file_read(".txt");
		unlink(".txt");
	}
	return (content);
}
