/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bakgun <bakgun@student.42kocaeli.com.tr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 11:36:19 by bakgun            #+#    #+#             */
/*   Updated: 2023/08/14 12:10:45 by bakgun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_copy_to_stash(char *stash, char *buf)
{
	char	*temp;
	char	*res;

	res = 0;
	if (!stash && buf)
	{
		res = ft_strdup(buf);
		if (!res)
			return (ft_free_stash(&res, 0));
		return (res);
	}
	temp = ft_strdup(stash);
	if (!temp)
	{
		ft_free_stash(&stash, 0);
		return (ft_free_stash(&temp, 0));
	}
	ft_free_stash(&stash, 0);
	res = ft_strjoin(temp, buf);
	if (!res)
		ft_free_stash(&res, 0);
	ft_free_stash(&temp, 0);
	return (res);
}

static int	ft_have_nl(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_extract_line(char *stash)
{
	char	*line;
	size_t	i;
	size_t	j;

	i = 0;
	if (!stash)
		return (ft_free_stash(&stash, 0));
	while (stash[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (ft_free_stash(&line, 0));
	j = 0;
	while (j < i + 1)
	{
		line[j] = stash[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

static char	*ft_recreate_stash(char *stash)
{
	size_t	i;
	char	*res;

	i = 0;
	if (!stash)
		return (NULL);
	while (stash[i] != '\n')
		i++;
	if (stash[i + 1] == '\0')
		return (ft_free_stash(&stash, 0));
	res = ft_substr(stash, i + 1, ft_strlen(stash));
	if (!res)
	{
		ft_free_stash(&stash, 0);
		return (NULL);
	}
	ft_free_stash(&stash, 0);
	return (res);
}

char	*get_next_line(int fd)
{
	char		buf[BUFFER_SIZE + 1];
	long		ret;
	static char	*stash[256] = {0};
	char		*line;

	line = 0;
	ret = BUFFER_SIZE;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (ft_free_stash(&stash[fd], 0));
	while (ret > 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if ((ret <= 0 && !stash[fd]) || ret == -1)
			return (ft_free_stash(&stash[fd], 0));
		buf[ret] = '\0';
		stash[fd] = ft_copy_to_stash(stash[fd], buf);
		if (ft_have_nl(stash[fd]))
		{
			line = ft_extract_line(stash[fd]);
			if (!line)
				return (ft_free_stash(&stash[fd], 0));
			return (stash[fd] = ft_recreate_stash(stash[fd]), line);
		}
	}
	return (ft_free_stash(&stash[fd], 1));
}
