/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewoolee <jewoolee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 19:29:11 by jewoolee          #+#    #+#             */
/*   Updated: 2023/10/30 22:15:41 by jewoolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#define BUFF_SIZE 1

static size_t	gnl_check_nl(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != 0)
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*gnl_free(char *s, char **ptr)
{
	if (s != 0)
	{
		free(s);
		s = 0;
	}
	if (*ptr != 0)
	{
		free(*ptr);
		*ptr = 0;
	}
	return (0);
}

static char	*gnl_a_line(char *s, char **ptr)
{
	size_t	size;
	size_t	i;
	char	*str;

	size = 0;
	while (s[size] != '\n')
		size++;
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (str == 0)
		return (gnl_free(s, ptr));
	i = 0;
	while (*s != '\n')
	{
		str[i] = *s;
		i++;
		s++;
	}
	str[i] = *s;
	s++;
	free(*ptr);
	*ptr = 0;
	return (str);
}

static char	*gnl_eof(char *s, char **ptr)
{
	char	*str;

	if (s == 0)
		return (0);
	str = gnl_strdup(s);
	if (str == 0)
		return (gnl_free(s, ptr));
	while (*s != '\0')
		s++;
	free(s);
	s = 0;
	free(*ptr);
	*ptr = 0;
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*buff;
	char		*res;
	ssize_t		rd_size;

	if (fd < 0 || BUFF_SIZE < 1)
		return (0);
	while (line == 0 || gnl_check_nl(line) == 0)
	{
		buff = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1));
		if (buff == 0)
			return (gnl_free(line, &buff));
		rd_size = read(fd, (void *)buff, BUFF_SIZE);
		if (rd_size < 0)
			return (gnl_free(line, &buff));
		if (rd_size == 0)
			return (gnl_eof(line, &buff));
		buff[rd_size] = '\0';
		line = gnl_strjoin(line, buff);
		if (line == 0)
			return (gnl_free(line, &buff));
	}
	res = gnl_a_line(line, &buff);
	return (res);
}
