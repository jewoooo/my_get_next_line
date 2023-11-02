/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewoolee <jewoolee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 19:29:11 by jewoolee          #+#    #+#             */
/*   Updated: 2023/11/02 21:36:56 by jewoolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*free_all(char *s1, char *s2)
{
	if (s1 != NULL)
	{
		free(s1);
		s1 = NULL;
	}
	if (s2 != NULL)
		free(s2);
	return (NULL);
}

static char	*eof_line(char *s1, char *s2)
{
	char	*line;

	line = gnl_strdup(s1);
	if (line == NULL)
		return (free_all(s1, s2));
	s1 = free_all(s1, s2);
	return (line);
}

static char	*backup_line(char *s, size_t from)
{
	size_t	i;
	size_t	last;
	size_t	size;
	char	*backup;

	last = gnl_strlen(s) + 1;
	size = last - from;
	backup = (char *)malloc(sizeof(char) * (size + 1));
	if (backup == NULL)
	{
		free(s);
		return (NULL);
	}
	i = 0;
	while (i < size)
	{
		backup[i] = s[from + i];
		i++;
	}
	backup[i] = '\0';
	free(s);
	return (backup);
}

static char	*a_line(char *s)
{
	char	*line;
	size_t	i;
	size_t	size;

	size = 0;
	while (s[size] != '\n')
		size++;
	line = (char *)malloc(sizeof(char) * (size + 2));
	if (line == NULL)
	{
		free(s);
		s = NULL;
		return (NULL);
	}
	i = 0;
	while (i <= size)
	{
		line[i] = s[i];
		i++;
	}
	line[i] = '\0';
	s = backup_line(s, size + 1);
	if (s == NULL)
		return (NULL);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*rd_line;
	char		*buff;
	ssize_t		rd_size;

	if (fd < 0 || BUFF_SIZE < 1)
		return (NULL);
	while (rd_line == NULL || gnl_strchr(rd_line, '\n') == NULL)
	{
		buff = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1));
		if (buff == NULL)
			return (free_all(rd_line, buff));
		rd_size = read(fd, (void *)buff, BUFF_SIZE);
		if (rd_size < 0)
			return (free_all(rd_line, buff));
		if (rd_size == 0)
			return (eof_line(rd_line, buff));
		buff[rd_size] = '\0';
		rd_line = gnl_strjoin(rd_line, buff);
		if (rd_line == NULL)
			return (free_all(rd_line, buff));
		free(buff);
	}
	return (a_line(rd_line));
}
