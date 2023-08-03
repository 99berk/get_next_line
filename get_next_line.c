/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bakgun <bakgun@student.42kocaeli.com.tr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 11:46:55 by bakgun            #+#    #+#             */
/*   Updated: 2023/07/27 14:23:53 by bakgun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*check_remainder(char **remainder);

static void	ft_strdel(char **as)
{
	if (as && *as)
	{
		free(*as);
		*as = NULL;
	}
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*buff;
	int		bytes_read;
	char		*p_n;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	buff = ft_strnew(BUFFER_SIZE + 1);
	if (!buff || (read(fd, buff, 0) < 0))
	{
		free(buff);
		return (NULL);
	}

	tmp = check_remainder(&remainder);
	while (!ft_strchr(buff, '\n') && (bytes_read = read(fd, buff, BUFFER_SIZE)))
	{
		buff[bytes_read] = '\0';
		if ((p_n = ft_strchr(buff, '\n')))
		{
			*p_n = '\0';
			free(remainder);
			remainder = ft_strdup(++p_n);
		}
		char *old_tmp = tmp;
		tmp = ft_strjoin(tmp, buff);
		free(old_tmp);
		if(tmp == NULL) // handle error in ft_strjoin
			return (NULL);
	}
	free(buff);
	if (tmp && tmp[0] == '\0')
	{
		free(tmp);
		return (NULL);
	}
	return (tmp);
}

static char	*check_remainder(char **remainder)
{
	char	*p_n;
	char	*res;

	if (*remainder)
	{
		if ((p_n = ft_strchr(*remainder, '\n')))
		{
			*p_n = '\0';
			res = ft_strdup(*remainder);
			ft_strcpy(*remainder, ++p_n);
			if (*remainder[0] == '\0')
				ft_strdel(remainder);
		}
		else
		{
			res = ft_strdup(*remainder);
			ft_strdel(remainder);
		}
	}
	else
		res = ft_strnew(2); //allocate extra space for '\n' and '\0'
	return (res);
}


