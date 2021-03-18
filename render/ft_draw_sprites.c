/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_sprites.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarthus <dkarthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 23:39:56 by dkarthus          #+#    #+#             */
/*   Updated: 2021/03/19 00:57:51 by dkarthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	ft_draw_spr_up(t_vars *inst, t_sprites *spr, int mid_x)
{
	int				act;
	int				x;
	int				y;
	unsigned int	bg_col;
	unsigned int	col;

	bg_col = ft_get_pixel_col(&inst->spr, 0, 0);
	act = inst->l.res_x / (2.0 * spr->dst);
	x = inst->spr.x * (act - spr->x) / (2 * act);
	y = inst->spr.y * (act - spr->y) / (2 * act);
	col = ft_get_pixel_col(&inst->spr, x, y);
	if ((col != bg_col) && (inst->dsts[mid_x - spr->x] > spr->dst) &&
		((mid_x - spr->x) > spr->xpx_end) && ((mid_x - spr->x) < spr->xpx_st))
		ft_pixel_put_image(inst, mid_x - spr->x, inst->l.res_y / 2
		- spr->y, col);
	x = inst->spr.x * (act + spr->x) / (2 * act);
	col = ft_get_pixel_col(&inst->spr, x, y);
	if ((col != bg_col) && (inst->dsts[mid_x + spr->x] > spr->dst) &&
		((mid_x + spr->x) < spr->xpx_st) && ((mid_x + spr->x) > spr->xpx_end))
		ft_pixel_put_image(inst, mid_x + spr->x, inst->l.res_y / 2
		- spr->y, col);
}

static void	ft_draw_spr_dwn(t_vars *inst, t_sprites *spr, int mid_x)
{
	int				act;
	int				x;
	int				y;
	unsigned int	bg_col;
	unsigned int	col;

	bg_col = ft_get_pixel_col(&inst->spr, 0, 0);
	act = inst->l.res_x / (2.0 * spr->dst);
	x = inst->spr.x * (act + spr->x) / (2 * act);
	y = inst->spr.y * (act + spr->y) / (2 * act);
	col = ft_get_pixel_col(&inst->spr, x, y);
	if (col != bg_col && inst->dsts[mid_x + spr->x] > spr->dst && (
			(mid_x + spr->x) < spr->xpx_st) && (mid_x + spr->x) > spr->xpx_end)
		ft_pixel_put_image(inst, mid_x + spr->x, inst->l.res_y / 2
		+ spr->y, col);
	x = inst->spr.x * (act - spr->x) / (2 * act);
	col = ft_get_pixel_col(&inst->spr, x, y);
	if (col != bg_col && inst->dsts[mid_x - spr->x] > spr->dst && (
			(mid_x - spr->x) > spr->xpx_end) && (mid_x - spr->x) < spr->xpx_st)
		ft_pixel_put_image(inst, mid_x - spr->x, inst->l.res_y / 2
		+ spr->y, col);
}

static int	ft_find_center(t_sprites *spr, int res_x)
{
	int		mid_x;
	float	rad_per_px;

	rad_per_px = M_PI / (3 * res_x);
	mid_x = abs(spr->xpx_st + spr->xpx_end) / 2;
	if (mid_x > res_x / 2)
		mid_x = (M_PI / 6.0 + spr->ang) / rad_per_px;
	else
		mid_x = (M_PI / 6.0 - spr->ang) / rad_per_px;
	return (mid_x);
}

static void	ft_util_draw(t_vars *inst, t_sprites *spr)
{
	int	act;
	int	y;
	int	x;
	int	mid_x;

	act = inst->l.res_x / (2.0 * spr->dst);
	mid_x = ft_find_center(spr, inst->l.res_x);
	x = 0;
	while (x <= act)
	{
		y = 0;
		while (y <= act)
		{
			if (y > inst->l.res_y / 2)
				break ;
			spr->x = x;
			spr->y = y;
			ft_draw_spr_up(inst, spr, mid_x);
			ft_draw_spr_dwn(inst, spr, mid_x);
			y++;
		}
		x++;
	}
}

void		ft_draw_sprites(t_vars *inst)
{
	t_sprites *tmp;

	tmp = inst->spr_dst;
	while (tmp)
	{
		ft_util_draw(inst, tmp);
		tmp = tmp->next;
	}
	ft_clear_spr_list(inst);
}
