/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarthus <dkarthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 22:06:48 by dkarthus          #+#    #+#             */
/*   Updated: 2021/03/19 01:11:15 by dkarthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static float	ft_set_ang(char angle)
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

void			ft_player_init(t_vars *inst)
{
	int			i;
	int			j;
	const char	*ref;
	char		*angle;

	i = 0;
	ref = "WESN";
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
				return ;
			}
			j++;
		}
		i++;
	}
}

void			ft_main_inst_init(t_vars *inst)
{
	inst->mlx = NULL;
	inst->win = NULL;
	inst->img = NULL;
	inst->l.lvl = NULL;
	inst->l.no = NULL;
	inst->l.so = NULL;
	inst->l.we = NULL;
	inst->l.ea = NULL;
	inst->l.spr = NULL;
	inst->no.img = NULL;
	inst->so.img = NULL;
	inst->we.img = NULL;
	inst->ea.img = NULL;
	inst->spr.img = NULL;
	inst->spr_dst = NULL;
	inst->dsts = NULL;
}
