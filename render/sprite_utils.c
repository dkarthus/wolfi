/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarthus <dkarthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 14:38:03 by dkarthus          #+#    #+#             */
/*   Updated: 2021/03/15 22:45:34 by dkarthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int ft_spr_sort(t_vars *inst, int y, int x, t_obj *ray)
{
	//handle mallocs
	t_sprites *new;

	if (inst->spr_dst == NULL)
	{
		inst->spr_dst = ft_new_spr(inst, y, x, ray);
		return (1);
	}
	if (ft_ch_duplicate(inst, y, x, ray))
		return (1);
	new = ft_new_spr(inst, y, x, ray);
	inst->spr_dst = ft_spr_insert(inst, new);
	return (1);
}

t_sprites *ft_spr_insert(t_vars *inst, t_sprites *new)
{
	t_sprites *tmp;

	if (inst->spr_dst->dst < new->dst)
	{
		new->next = inst->spr_dst;
		return (new);
	}
	tmp = inst->spr_dst;
	while(tmp)
	{
		if (tmp->next == NULL)
		{
			tmp->next = new;
			return (inst->spr_dst);
		}
		if (tmp->next->dst <= new->dst)
		{
			new->next = tmp->next;
			tmp->next = new;
			return (inst->spr_dst);
		}
		tmp = tmp->next;
	}
	return (inst->spr_dst);
}

t_sprites *ft_new_spr(t_vars *inst, int y, int x, t_obj *ray)
{
	t_sprites *new;

	new = malloc(sizeof(t_sprites));
	if (!new)
		return (NULL);
	new->x = x;
	new->y = y;
	new->dst = (x + 0.5 - inst->pov.x) * cos(inst->pov.dir) - (y + 0.5 -
			inst->pov.y) * sin(inst->pov.dir);
	new->ang = acos(new->dst / sqrtf((x + 0.5 - inst->pov.x) * (x + 0.5 -
	inst->pov.x) + (y + 0.5 - inst->pov.y) * (y + 0.5 - inst->pov.y)));
	new->xpx_st = (int)ray->dir;
	new->next = NULL;
	return (new);
}

int ft_ch_duplicate(t_vars *inst, int y, int x, t_obj *ray)
{
	t_sprites *tmp;

	tmp = inst->spr_dst;
	while (tmp)
	{
		if (tmp->x == x && tmp->y == y)
		{
			tmp->xpx_end = (int)ray->dir;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void ft_clear_spr_list(t_vars *inst)
{
	t_sprites *tmp;

	while(inst->spr_dst)
	{
		tmp = inst->spr_dst->next;
		free (inst->spr_dst);
		inst->spr_dst = tmp;
	}
}