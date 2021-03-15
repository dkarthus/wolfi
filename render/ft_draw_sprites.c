/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_sprites.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarthus <dkarthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 23:39:56 by dkarthus          #+#    #+#             */
/*   Updated: 2021/03/15 21:01:38 by dkarthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	ft_util_draw(t_vars *inst, t_sprites *spr)
{
	int		act;
	int 	y;
	int 	x;
	int		mid_y, mid_x;
	unsigned int bg_col;
	unsigned int col_up;
	unsigned int col_dwn;
	float rad_per_px;

	rad_per_px = M_PI / (3.0 * inst->l.res_x);
	mid_y = inst->l.res_y / 2;
	bg_col = ft_get_pixel_col(&inst->SPR, 0, 0);
	act = inst->l.res_x / (2.0 * spr->dst);
	mid_x = abs(spr->xpx_st + spr->xpx_end) / 2;
	if (mid_x > inst->l.res_x / 2)
		mid_x  = (M_PI / 6.0 + spr->ang) / rad_per_px;
	else
		mid_x = (M_PI / 6.0 - spr->ang) / rad_per_px;
	/*printf("%f, st=%d, end=%d, ang=%f\n", spr->dst, spr->xpx_st, spr->xpx_end,
		spr->ang);
	printf("%d\n", mid_x);
	printf("-----\n");*/
	x = 0;
	while (x < act)
	{
		y = 0;
		while (y < act)
		{
			if (y > mid_y)
				break;
			spr->x = inst->SPR.x * (act - x) / (2 * act);
			spr->y = inst->SPR.y * (act - y) / (2 * act);
			col_up = ft_get_pixel_col(&inst->SPR, spr->x, spr->y);
			if ((col_up != bg_col) && (inst->dsts[mid_x - x] > spr->dst) &&
			((mid_x - x) > spr->xpx_end) && ((mid_x - x) < spr->xpx_st))
				ft_pixel_put_image(inst, mid_x - x, mid_y - y, col_up);
			spr->x = inst->SPR.x * (act + x) / (2 * act);
			spr->y = inst->SPR.y * (act + y) / (2 * act);
			col_dwn = ft_get_pixel_col(&inst->SPR, spr->x, spr->y);
			if (col_dwn != bg_col && inst->dsts[mid_x + x] > spr->dst && (
					(mid_x + x) < spr->xpx_st) && (mid_x + x) > spr->xpx_end)
				ft_pixel_put_image(inst, mid_x + x, mid_y + y, col_dwn);
			spr->x = inst->SPR.x * (act + x) / (2 * act);
			spr->y = inst->SPR.y * (act - y) / (2 * act);
			col_up = ft_get_pixel_col(&inst->SPR, spr->x, spr->y);
			if (col_up != bg_col && inst->dsts[mid_x + x] > spr->dst && (
					(mid_x + x) < spr->xpx_st) && ((mid_x + x) > spr->xpx_end))
				ft_pixel_put_image(inst, mid_x + x, mid_y - y, col_up);
			spr->x = inst->SPR.x * (act - x) / (2 * act);
			spr->y = inst->SPR.y * (act + y) / (2 * act);
			col_dwn = ft_get_pixel_col(&inst->SPR, spr->x, spr->y);
			if (col_dwn != bg_col && inst->dsts[mid_x - x] > spr->dst && (
					(mid_x - x) > spr->xpx_end) && ((mid_x - x) < spr->xpx_st))
				ft_pixel_put_image(inst, mid_x - x, mid_y + y, col_dwn);
			y++;
		}
		x++;
	}
}

void ft_draw_sprites(t_vars *inst)
{
	t_sprites *tmp;

	tmp = inst->spr_dst;
	while (tmp)
	{
		ft_util_draw(inst, tmp);
/*		printf("%f, st=%d, end=%d, ang=%f\n", tmp->dst, tmp->xpx_st,
			tmp->xpx_end, tmp->ang);*/
		tmp = tmp->next;
	}
	ft_clear_spr_list(inst);
}