/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_walls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarthus <dkarthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 23:07:09 by dkarthus          #+#    #+#             */
/*   Updated: 2021/03/19 01:10:35 by dkarthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		ft_is_hit(t_vars *inst, int y, int x, t_obj *ray)
{
	int strs;

	strs = 0;
	if (y <= 0 || x <= 0)
		return (1);
	while (inst->l.lvl[strs])
		strs++;
	if (y >= strs - 1)
		return (1);
	if (x >= ft_strlen(inst->l.lvl[y]) - 1)
		return (1);
	if (inst->l.lvl[y][x] == '1' || inst->l.lvl[y][x] == ' ')
		return (1);
	if (inst->l.lvl[y][x] == '2')
		ft_spr_sort(inst, y, x, ray);
	return (0);
}

float	ft_dst_sort(float dst_y, float dst_x, t_obj *ray, t_vars *inst)
{
	if (dst_y > dst_x)
	{
		if (cosf(ray->fov_st) < 0)
		{
			ray->tx_drw = &inst->ea;
			ray->txt_xof = 1 - ray->txt_xof;
		}
		else
			ray->tx_drw = &inst->we;
		return (dst_x);
	}
	else
	{
		ray->txt_xof = ray->txt_yof;
		if (sinf(ray->fov_st) < 0)
		{
			ray->txt_xof = 1 - ray->txt_yof;
			ray->tx_drw = &inst->no;
		}
		else
			ray->tx_drw = &inst->so;
		return (dst_y);
	}
}

void	ft_draw_walls(t_vars *inst, t_obj *ray, float dst, int x)
{
	int				proj_len;
	int				y;
	int				x_tx;
	unsigned int	col_up;
	unsigned int	col_dwn;

	y = 0;
	x_tx = ray->tx_drw->x * ray->txt_xof;
	proj_len = inst->l.res_x / (2.0 * dst);
	while (y < proj_len)
	{
		if (y > inst->l.res_y / 2)
			break ;
		col_up = ft_get_pixel_col(ray->tx_drw, x_tx, ray->tx_drw->y *
		(proj_len - y) / (2 * proj_len));
		col_dwn = ft_get_pixel_col(ray->tx_drw, x_tx, ray->tx_drw->y *
		(proj_len + y) / (2 * proj_len));
		ft_pixel_put_image(inst, x, inst->l.res_y / 2 - y, col_up);
		ft_pixel_put_image(inst, x, inst->l.res_y / 2 + y, col_dwn);
		y++;
	}
}

int		ft_render_img(t_vars *inst)
{
	ft_draw_ceil_floor(inst);
	ft_render_walls(inst);
	ft_draw_sprites(inst);
	if (inst->mode)
		mlx_put_image_to_window(inst->mlx, inst->win, inst->img, 0, 0);
	return (0);
}
