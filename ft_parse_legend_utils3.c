/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_legend_utils3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarthus <dkarthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 16:25:24 by dkarthus          #+#    #+#             */
/*   Updated: 2020/12/07 21:37:30 by dkarthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
static int	ft_count_lines(char **map)
{
	int i;

	i = 0;
	while(map[i])
		i++;
	return (i);
}
static int ft_validate_lvl(char **lvl, int lines)
{
	int i;
	int j;

	i = 0;
	j = 0;

}
int	ft_parse_lvl(char **map, t_legend *l)
{
	int lines;

	if ((lines = ft_count_lines(map)) < 3)
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
		l->lvl[lines] = ft_strdup(map[lines]);
		lines++;
	}

}
