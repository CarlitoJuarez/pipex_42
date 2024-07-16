#include <sys/stat.h>
#include <errno.h>

#include "../pipex.h"

char *file_read(char *file)
{
    int fd;

    printf("FILE_READ: %s\n", file);
    fd = open(file, O_RDONLY);
    printf("ERRNO: %d\n", errno);
    if (fd == -1)
    {
        if (errno == 2)
            printf("zsh: no such file or directory: %s\n", file);
        else if (errno == 14)
            printf("zsh: permission denied: %s\n", file);
        return (NULL);
    }
    file = get_next_line(fd, 0);
    close(fd);
    return (file);
}

int file_check_r(char *file)
{
    int fd;

    fd = open(file, O_RDONLY);
    if (fd == -1)
    {
        if (errno == 2)
            return (1);
        if (errno == 13)
            printf("zsh: permission denied: %s\n", file);
        return (0);
    }
    close(fd);
    return (1);
}

int file_check_w(char *file)
{
    int fd;

    fd = open(file, O_WRONLY);
    if (fd == -1)
    {
        if (errno == 2)
            return (1);
        if (errno == 13)
            printf("zsh: permission denied: %s\n", file);
        return (0);
    }
    close(fd);
    return (1);
}

void free_list(char **arr)
{
    int i;

    i = 0;
    while (*(arr + i))
        free(*(arr + i++));
    free(arr);
}

void free_list_list(char ***arr)
{
    int i;
    int j;

    i = 0;
    while (*(arr + i))
    {
        j = 0;
        while (arr[i][j])
            free(arr[i][j++]);
        free(*(arr + i));
        i++;
    }
    free(arr);
}