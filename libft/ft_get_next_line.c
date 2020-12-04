/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarthus <dkarthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 18:20:49 by dkarthus          #+#    #+#             */
/*   Updated: 2020/12/02 20:03:43 by dkarthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_letemfree(char **tail, char **buf)
{
	if (tail && *tail)
	{
		free(*tail);
		*tail = NULL;
	}
	if (buf)
	{
		free(*buf);
		buf = NULL;
	}
	return (-1);
}

static int	ft_adjusttail(char **tail, char **line)
{
	char	*tmp;
	size_t	i;

	i = 0;
	while ((*tail)[i] != '\n' && (*tail)[i] != '\0')
		i++;
	if ((*tail)[i] == '\n')
	{
		if (!(*line = ft_substr(*tail, 0, i)))
			return (ft_letemfree(tail, tail));
		tmp = *tail;
		if (!(*tail = ft_strdup((&(*tail)[i + 1]))))
			return (ft_letemfree(tail, tail));
		free(tmp);
		if ((*tail)[0] == '\0')
			ft_letemfree(tail, tail);
	}
	else
	{
		*line = ft_strdup(*tail);
		ft_letemfree(tail, tail);
		return (0);
	}
	return (1);
}

static int	ft_ret(char **tail, char **line, int b_read, char **buf)
{
	ft_letemfree(buf, buf);
	if (b_read == 0 && !*tail)
	{
		*line = ft_strdup("");
		ft_letemfree(tail, tail);
		return (0);
	}
	if (b_read < 0)
		return (ft_letemfree(tail, tail));
	else
		return (ft_adjusttail(tail, line));
}

int			ft_get_next_line(int fd, char **line)
{
	static char	*tail[4069];
	char		*buf;
	int			b_read;
	char		*tmp;

	if (fd < 0 || !line || (BUFFER_SIZE < 1) || (!(buf = malloc((BUFFER_SIZE
			+ 1) * sizeof(char)))) || fd > 4069)
		return (-1);
	while ((b_read = read(fd, buf, BUFFER_SIZE)))
	{
		buf[b_read] = '\0';
		if (!tail[fd])
			tail[fd] = ft_strdup(buf);
		else
		{
			tmp = tail[fd];
			if (!(tail[fd] = ft_strjoin(tail[fd], buf)))
				return (ft_letemfree(&tmp, &buf));
			free(tmp);
		}
		if (ft_strchr(tail[fd], '\n'))
			break ;
	}
	return (ft_ret(&tail[fd], line, b_read, &buf));
}
