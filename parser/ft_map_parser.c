/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarthus <dkarthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 15:08:56 by dkarthus          #+#    #+#             */
/*   Updated: 2020/12/06 20:00:16 by dkarthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static char	**ft_create_map(char *file, char **map)
{
	int fd;
	int i;
	int j;

	i = 1;
	j = 0;
	fd = open(file, O_RDONLY);
	while (i)
	{
		i = ft_get_next_line(fd, &map[j]);
		j++;
		if (i == -1)
			return (NULL);
	}
	close(fd);
	return (map);
}

char		**ft_parse(char *file)
{
	int		fd;
	int		i;
	char	*line;
	char	**map;
	size_t	lines;

	lines = 0;
	i = 1;
	if ((fd = open(file, O_RDONLY)) == -1)
		return (NULL);
	while (i)
	{
		i = ft_get_next_line(fd, &line);
		free(line);
		lines++;
	}
	if (!(map = ft_calloc((lines + 1), sizeof(char *))))
		return (NULL);
	close(fd);
	return (ft_create_map(file, map));
}
