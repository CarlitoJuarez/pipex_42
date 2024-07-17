#include "../pipex.h"

void handle_child(int *fd, int fd_2, char *path, char **cmnd_list, char *content)
{
    free(content);
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
    free(cmnd_list);
    exit(EXIT_FAILURE);
}

char *handle_parent(int *fd, int fd_2, char *content)
{
    close(fd[0]);
    close(fd_2);
    if (write(fd[1], content, strlen(content)) == -1)
    {
        perror("write:");
        free(content);
        content = NULL;
        exit(EXIT_FAILURE);
    }
    close(fd[1]);
    wait(NULL);
    free(content);
    content = NULL;
    content = file_read(".txt");
    if (!content)
        return (NULL);
    unlink(".txt");
    return (content);
}

char *exec_cmnd(char *path, char **cmnd_list, char *content)
{
    int pid;
    int fd[2];
    int tmp_fd;

    tmp_fd = open(".txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (tmp_fd == -1)
        return (free_list(cmnd_list), ("open tmpfile:"), NULL);
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
        handle_child(fd, tmp_fd, path, cmnd_list, content);
    else
    {
        free_list(cmnd_list);
        content = handle_parent(fd, tmp_fd, content);
        if (!content)
            return (NULL);
    }
    return (content);
}