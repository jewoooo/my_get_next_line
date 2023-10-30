/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewoolee <jewoolee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 19:29:14 by jewoolee          #+#    #+#             */
/*   Updated: 2023/10/30 22:18:48 by jewoolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	gnl_strlen(char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != 0)
		len++;
	return (len);
}

char	*gnl_strdup(char *s)
{
	size_t	i;
	size_t	size;
	char	*dup_s;

	size = 0;
	while (s[size] != '\0')
		size++;
	dup_s = (char *)malloc(sizeof(char) * (size + 1));
	if (dup_s == 0)
		return (0);
	i = 0;
	while (i < size)
	{
		dup_s[i] = s[i];
		i++;
	}
	dup_s[i] = '\0';
	return (dup_s);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	size_t	i;
	char	*join_s;

	if (s1 == 0)
		return (gnl_strdup(s2));
	join_s = (char *)malloc(sizeof(char) * \
				(gnl_strlen(s1) + gnl_strlen(s2) + 1));
	if (join_s == 0)
		return (0);
	i = 0;
	while (i < gnl_strlen(s1))
	{
		join_s[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < gnl_strlen(s2))
	{
		join_s[gnl_strlen(s1) + i] = s2[i];
		i++;
	}
	join_s[gnl_strlen(s1) + i] = '\0';
	free(s1);
	s1 = 0;
	return (join_s);
}
