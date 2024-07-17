#include "../pipex.h"

// char	*ft_strjoin(char *s1, char *s2)
// {
// 	char	*new;
// 	size_t	i;
// 	size_t	j;

// 	i = 0;
// 	while ( s1 && *(s1 + i) )
// 		i++;
// 	j = 0;
// 	while (*(s2 + j))
// 		j++;
// 	new = malloc(sizeof(char) * (i + j + 1));
// 	if (!new)
// 		return (NULL);
// 	new[i + j] = 0;
// 	i = 0;
// 	while ( s1 && *(s1 + i) )
// 	{
// 		new[i] = s1[i];
// 		i++;
// 	}
// 	j = 0;
// 	while (*(s2 + j))
// 		new[i++] = s2[j++];
//     free(s2);
// 	return (new);
// }

// int check_end(char *res, char *limiter)
// {
//     int i;
//     int j;

//     i = 0;
//     j = 0;
//     while (*(limiter + j))
//         j++;
//     while (*(res + i) && *(res + i) != '\n')
//         i++;
//     i -= j;
//     if (i < 0)
//         return (0);
//     j = 0;
//     while ( *(res + i + j) == *(limiter + j) )
//         j++;
//     if (*(res + i + j) == '\n' || !*(res + i + j))
//         return (1);
//     return (0);
// }

// char *read_this(int fd, char *buf, char *limiter)
// {
//     char *res;
//     int bytes;

//     bytes = 1;
//     while (bytes > 0)
//     {
//         res = malloc(sizeof(char) * BUF_SIZE + 1);
//         if (!res)
//             return(free(buf), NULL);
// 		if (fd == 0)
//         	write(1, ">> ", 3);
//         bytes = read(fd, res, BUF_SIZE);
//         if (!bytes)
//             break;
//         else if (bytes < 0)
//         {
//             perror("read");
//             free(res);
//             free(buf);
//             return (NULL);
//         }
//         res[bytes] = 0;
//         if (fd == 0 && check_end(res, limiter))
//             break;
//         buf = ft_strjoin(buf, res);
//     }
//     free(res);
//     return (buf);
// }


// char *get_next_line(int fd, char *limiter)
// {
//     static char *buf;

//     // if (buf)
//     //     free(buf);
//     buf = NULL;
//     if (fd < 0 || BUF_SIZE <= 0 || BUF_SIZE > INT_MAX)
//         return (buf = NULL, NULL);
//     buf = read_this(fd, buf, limiter);
//     if (!buf)
//         return (NULL);
//     return (buf);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajovanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:07:30 by ajovanov          #+#    #+#             */
/*   Updated: 2024/04/26 14:59:06 by ajovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin_and_free(char *s1, char *s2)
{
	int		i;
	int		b;
	char	*s3;

	i = 0;
	b = 0;
	if (!s1 && !s2)
		return (NULL);
	s3 = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s3)
		return (free(s1), s1 = NULL, NULL);
	while (s1 && s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	while (s2 && s2[b])
	{
		s3[i + b] = s2[b];
		b++;
	}
	s3[i + b] = '\0';
	free(s1);
	s1 = NULL;
	return (s3);
}

void	*free_nm(char **buff1, char **buff2)
{
	if (buff1 && *buff1)
	{
		free(*buff1);
		*buff1 = NULL;
	}
	if (buff2 && *buff2)
	{
		free(*buff2);
		*buff2 = NULL;
	}
	return (NULL);
}




char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s || !c)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)s + i);
	return (NULL);
}

size_t	find_next_line_break(char *str, size_t i)
{
	if (!str || !str[i])
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}

char	*read_line(char *str)
{
	char	*linie;
	size_t	i;

	i = 0;
	if (!str || *str == '\0')
		return (NULL);
	i = find_next_line_break(str, i);
	if (i == 0)
		return (NULL);
	linie = (char *)malloc(sizeof(char) * i + 1);
	if (!linie)
		return (NULL);
	i = 0;
	while (*(str + i) && *(str + i) != '\n')
	{
		*(linie + i) = *(str + i);
		i++;
	}
	if (*(str + i) == '\n')
	{
		*(linie + i) = *(str + i);
		i++;
	}
	*(linie + i) = '\0';
	return (linie);
}

int check_end(char *res, char *limiter)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (*(limiter + j))
        j++;
    while (*(res + i) && *(res + i) != '\n')
        i++;
    i -= j;
    if (i < 0)
        return (0);
    j = 0;
    while ( *(res + i + j) == *(limiter + j) )
        j++;
    if (*(res + i + j) == '\n' || !*(res + i + j))
        return (1);
    return (0);
}



char	*create_substring(char *str)
{
	char	*new_str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!str || !*str)
		return (free(str), str = NULL, NULL);
	i = find_next_line_break(str, i);
	if (i == 0)
		return (free(str), str = NULL, NULL);
	new_str = (char *)malloc((ft_strlen(str) - i) + 1);
	if (!new_str)
		return (free(str), str = NULL, NULL);
	while (*(str + i))
		*(new_str + j++) = *(str + i++);
	*(new_str + j) = '\0';
	if (!*new_str)
		return (free(str), free(new_str), NULL);
	free(str);
	return (new_str);
}



char	*rua(int fd, char **read_buffer, char *read_content, int *read_bytes, char *limiter)
{
	*read_bytes = read(fd, read_content, BUF_SIZE);
	if (*read_bytes == -1)
		return (free(*read_buffer), *read_buffer = NULL, NULL);
	while (*read_bytes > 0)
	{
		*(read_content + *read_bytes) = '\0';
		*read_buffer = ft_strjoin_and_free(*read_buffer, read_content);
		if (!*read_buffer)
			return (NULL);
		if (ft_strchr(*read_buffer, '\n'))
			break ;
		*read_bytes = read(fd, read_content, BUF_SIZE);
		if (*read_bytes == -1)
			return (free(*read_buffer), *read_buffer = NULL, NULL);
        if (fd == 0 && check_end(read_content, limiter))
            break ;
	}
	return (*read_buffer);
}

char	*get_next_line(int fd, char *limiter)
{
	char		*read_content;
	int			read_bytes;
	static char	*read_buffer;

	read_bytes = 1;
	if (fd < 0 || BUF_SIZE <= 0 || BUF_SIZE > INT_MAX)
		return (read_buffer = NULL, NULL);
	read_content = malloc(BUF_SIZE + 1);
	if (read_content == NULL)
		return (free_nm(&read_buffer, NULL), NULL);
	read_buffer = rua(fd, &read_buffer, read_content, &read_bytes, limiter);
	if (read_buffer == NULL)
		return (free_nm(&read_buffer, &read_content), NULL);
	free(read_content);
	read_content = read_line(read_buffer);
	if (read_content == NULL)
		return (free_nm(&read_content, &read_buffer), NULL);
	read_buffer = create_substring(read_buffer);
	if (read_buffer == NULL)
		return (free_nm(&read_buffer, NULL), read_content);
	return (read_content);
}