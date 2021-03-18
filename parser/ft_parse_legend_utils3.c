/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_legend_utils3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarthus <dkarthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 16:25:24 by dkarthus          #+#    #+#             */
/*   Updated: 2021/03/19 00:40:42 by dkarthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static size_t	ft_count_lines(char **map)
{
	int i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

static int		ft_flst_line(char *line)
{
	int j;

	j = 0;
	while (line[j])
	{
		if (line[j] == '0' || (line[j] != '1' && line[j] != ' '))
		{
			ft_putstr_fd("Error\nInvalid map!", 1);
			return (0);
		}
		j++;
	}
	return (1);
}

static int		ft_ch_mid(char **l, size_t i, size_t j)
{
	char	*set1;
	char	*set2;
	size_t	len;

	set1 = " 012WESN";
	set2 = "02WESN";
	len = ft_strlen(l[i - 1]);
	len = (len < ft_strlen(l[i + 1])) ? len : ft_strlen(l[i + 1]);
	if (!ft_strchr(set1, l[i][j]))
		return (0);
	if (ft_strchr(set2, l[i][j]))
	{
		if (j == 0)
			return (0);
		if (j >= (len - 1) || l[i][j - 1] == ' ' || l[i][j + 1] == ' ' ||
		l[i - 1][j - 1] == ' ' || l[i - 1][j] == ' ' || l[i - 1][j + 1] ==
		' ' || l[i + 1][j - 1] == ' ' || l[i + 1][j] == ' ' || l[i + 1][j +
		1] == ' ')
			return (0);
	}
	return (1);
}

static int		ft_validate_lvl(char **l, size_t lines)
{
	size_t	flag;
	size_t	i[2];
	char	*plr;

	i[0] = 1;
	flag = 0;
	plr = "NSWE";
	if (!ft_flst_line(l[0]) || !ft_flst_line(l[lines - 1]))
		return (0);
	while (i[0] < (lines - 1))
	{
		i[1] = 0;
		while (l[i[0]][i[1]])
		{
			if (!ft_ch_mid(l, i[0], i[1]))
				return (0);
			if (ft_strchr(plr, l[i[0]][i[1]]))
				flag++;
			i[1]++;
		}
		i[0]++;
	}
	if (flag == 2 || flag == 0)
		return (0);
	return (1);
}

int				ft_parse_lvl(char **map, t_legend *l, int *flag)
{
	size_t lines;

	if ((*flag != 8) || ((lines = ft_count_lines(map)) < 3) ||
	!(ft_validate_lvl(map, lines)))
	{
		ft_putstr_fd("Error\nInvalid map!", 1);
		return (-1);
	}
	if (!(l->lvl = ft_calloc((lines + 1), sizeof(char *))))
	{
		perror("Error\n->level");
		return (-1);
	}
	lines = 0;
	while (map[lines])
	{
		if (!(l->lvl[lines] = ft_strdup(map[lines])))
		{
			perror("Error\n->level");
			return (-1);
		}
		lines++;
	}
	return (2);
}
