#include <sys/stat.h>
#include <errno.h>

#include "../pipex.h"

char *file_read(char *file)
{
    int fd;
    char *content;

    fd = open(file, O_RDONLY);
    if (fd == -1)
    {
        if (errno == 2)
            printf("zsh: no such file or directory: %s\n", file);
        else if (errno == 14)
            printf("zsh: permission denied: %s\n", file);
        return (NULL);
    }
    content = get_next_line(fd, 0);
    if (!content)
        return (NULL);
    close(fd);
    return (content);
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
        i++;
    i--;
    while (i)    
    {
        free(*(arr + i));
        *(arr + i) = NULL;
        i--;
    }
    free(*arr);
    *arr = NULL;
    free(arr);
    arr = NULL;
}

void free_list_list(char ***arr)
{
    int i;

    i = 0;
    while (*(arr + i))
        i++;
    i--;
    while (i)
        free_list(*(arr + i--));
    free_list(*arr);
    *arr = NULL;
    free(arr);
    arr = NULL;
}