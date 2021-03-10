/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_sprites.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarthus <dkarthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 23:39:56 by dkarthus          #+#    #+#             */
/*   Updated: 2021/03/10 22:33:38 by dkarthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	ft_util_draw(t_vars *inst, t_sprites *spr)
{
	int		act;
	int 	y;
	int 	x;
	int		mid;
	unsigned int bg_col;
	unsigned int col_up;
	unsigned int col_dwn;

	mid = inst->l->res_y / 2;
	bg_col = ft_get_pixel_col(inst->SPR, 0, 0);
	act = inst->l->res_x / (2.0 * spr->dst);
	while (spr->xpx_st <= spr->xpx_end)
	{
		y = -1;
		x = 0;
		while (y < act)
		{
			y++;
			if (y > mid)
				break;
			spr->x = inst->SPR.x * (act - x) / (2 * act);
			spr->y = inst->SPR.y * (act - y) / (2 * act);
			col_up = ft_get_pixel_col(inst->SPR, spr->x, spr->y);
			if
		}
		spr->xpx_st++;
	}
}

void ft_draw_sprites(t_vars *inst)
{
	t_sprites *tmp;

	if (!inst->spr_dst)
		return;
	tmp = inst->spr_dst;
	while (tmp)
	{
		ft_util_draw(inst, tmp);
		tmp = tmp->next;
	}
	ft_clear_spr_list(inst);
}