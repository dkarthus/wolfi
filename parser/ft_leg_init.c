/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_leg_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarthus <dkarthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 13:59:28 by dkarthus          #+#    #+#             */
/*   Updated: 2021/03/15 22:38:11 by dkarthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_legend	*ft_leg_init()
{
	t_legend *l;

	if (!(l = ft_calloc(sizeof(t_legend), 1)))
	{
		perror("Error\n->leg");
		return (NULL);
	}
	return (l);
}

static float ft_set_ang(char angle)
{
	if (angle == 'E')
		return (0);
	if (angle == 'S')
		return (1.5 * M_PI);
	if (angle == 'W')
		return (M_PI);
	if (angle == 'N')
		return (M_PI_2);
	return (0);
}

void	ft_player_init(t_vars *inst)
{
	//t_obj *plr;
	int i;
	int j;
	char *ref = "WESN";
	char *angle;

	//if (!(plr = ft_calloc(1, sizeof(t_obj))))
	//	return (NULL);
	i = 0;
	while (inst->l.lvl[i])
	{
		j = 0;
		while (inst->l.lvl[i][j])
		{
			if ((angle = ft_strchr(ref, inst->l.lvl[i][j])))
			{
				inst->pov.y = (float)i + 0.5;
				inst->pov.x = (float)j + 0.5;
				inst->pov.dir = ft_set_ang(*angle);
				return;
			}
			j++;
		}
		i++;
	}
}