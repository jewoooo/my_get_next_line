/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewoolee <jewoolee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 19:29:11 by jewoolee          #+#    #+#             */
/*   Updated: 2023/11/05 21:22:52 by jewoolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*free_all(char **ptr, char *s)
{
	if (*ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
	if (s != NULL)
		free(s);
	return (NULL);
}

static char	*eof_line(char **ptr, char *s)
{
	char	*line;

	free(s);
	if (*ptr == NULL)
		return (NULL);
	line = gnl_strdup(*ptr);
	free(*ptr);
	*ptr = NULL;
	if (line == NULL)
		return (NULL);
	return (line);
}

static char	*backup_line(char **s, size_t from)
{
	size_t	i;
	size_t	size;
	char	*backup;

	size = gnl_strlen(*s) - from;
	if (size < 1)
	{
		free(*s);
		return (NULL);
	}
	backup = (char *)malloc(sizeof(char) * (size + 1));
	if (backup == NULL)
	{
		free(*s);
		return (NULL);
	}
	i = 0;
	while (i < size)
	{
		backup[i] = (*s)[from + i];
		i++;
	}
	backup[i] = '\0';
	free(*s);
	return (backup);
}

static char	*get_a_line(char **s)
{
	size_t	size;
	char	*line;

	size = 0;
	while ((*s)[size] != '\n')
		size++;
	line = (char *)malloc(sizeof(char) * (size + 2));
	if (line == NULL)
	{
		free(*s);
		*s = NULL;
		return (NULL);
	}
	line = gnl_strncpy(line, *s, size + 1);
	line[size + 1] = '\0';
	*s = backup_line(s, size + 1);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*rd_line[OPEN_MAX];
	char		*buff;
	ssize_t		rd_size;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	while (gnl_strnl(rd_line[fd]) == 0)
	{
		buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buff == NULL)
			return (free_all(&rd_line[fd], buff));
		rd_size = read(fd, (void *)buff, BUFFER_SIZE);
		if (rd_size < 0)
			return (free_all(&rd_line[fd], buff));
		if (rd_size == 0)
			return (eof_line(&rd_line[fd], buff));
		buff[rd_size] = '\0';
		rd_line[fd] = gnl_strjoin(rd_line[fd], buff);
		if (rd_line[fd] == NULL)
			return (free_all(&rd_line[fd], buff));
		free(buff);
	}
	return (get_a_line(&rd_line[fd]));
}
