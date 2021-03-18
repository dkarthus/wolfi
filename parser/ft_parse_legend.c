/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_legend.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarthus <dkarthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 20:32:01 by dkarthus          #+#    #+#             */
/*   Updated: 2020/12/08 17:32:52 by dkarthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	ft_parse_util(char **line, t_legend *l, int *flag)
{
	if (*line[0] == 'R')
		return (ft_parse_res(*line, l, flag));
	if (*line[0] == 'N')
		return (ft_parse_ntexture(*line, l, flag));
	if (*line[0] == 'S' && line[0][1] == 'O')
		return (ft_parse_stexture(*line, l, flag));
	if (*line[0] == 'W')
		return (ft_parse_wtexture(*line, l, flag));
	if (*line[0] == 'E')
		return (ft_parse_etexture(*line, l, flag));
	if (*line[0] == 'F')
		return (ft_parse_fcol(*line, l, flag));
	if (*line[0] == 'C')
		return (ft_parse_ccol(*line, l, flag));
	if (*line[0] == 'S' && line[0][1] == ' ')
		return (ft_parse_spritetex(*line, l, flag));
	if (*line[0] == ' ' || *line[0] == '1')
		return (ft_parse_lvl(line, l, flag));
	if (*line[0] == '\0' || *line[0] == '\n')
		return (1);
	return (-1);
}

int			ft_parse_legend(char **map, t_legend *l)
{
	int i;
	int flag;
	int ret;

	i = 0;
	flag = 0;
	while (map[i])
	{
		if ((ret = ft_parse_util(&map[i], l, &flag)) == -1)
		{
			ft_free_map(map);
			ft_free_leg(l);
			return (0);
		}
		if (ret == 2)
		{
			ft_free_map(map);
			return (1);
		}
		i++;
	}
	ft_free_map(map);
	ft_free_leg(l);
	ft_putstr_fd("Error\n Invalid map", 1);
	return (0);
}
