/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_sprites.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarthus <dkarthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 23:39:56 by dkarthus          #+#    #+#             */
/*   Updated: 2021/03/01 23:39:56 by dkarthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_draw_sprites(t_vars *inst)
{
	float spr[20];
	t_obj ray;
	double dstV = 10000000;
	double dstH = 10000000;
	double dst;
	int x;
	int y;
	int mid;
	double xof;
	double yof;
	int iter, act;
	float x_V, x_H, x_tx;
	unsigned int col_up, col_dwn;
	t_txt *tx_drw;

	ray.fov_st = inst->pov->dir - M_PI / 6.0;
	x = inst->l->res_x;
	while (x >= 0)
	{
		iter = 1;
		if (sin(ray.fov_st) > 0.001)
		{
			ray.y = SCALE * ((int)inst->pov->y / SCALE) - 0.0001;
			ray.x = (inst->pov->y - ray.y) * (cos(ray.fov_st) / sin(ray
																			.fov_st)) + inst->pov->x;
			yof = -SCALE;
			xof = -yof * (cos(ray.fov_st) / sin(ray.fov_st));
		}
		else if (sin(ray.fov_st) < -0.001)
		{
			ray.y = SCALE * ((int)inst->pov->y / SCALE) + SCALE;
			ray.x = (inst->pov->y - ray.y) * (cos(ray.fov_st) / sin(ray
																			.fov_st)) + inst->pov->x;
			yof = SCALE;
			xof = -yof * (cos(ray.fov_st) / sin(ray.fov_st));
		}
		else
		{
			iter = 0;
		}
		while (iter > 0 && ray.y >= 0 && ray.x >= 0)
		{
			if (ft_is_hit(inst->l->lvl, (int)ray.y / SCALE, (int)ray.x / SCALE))
			{
				dstH = (ray.x - inst->pov->x) * cos(inst->pov->dir) -
					   (ray.y - inst->pov->y) * sin(inst->pov->dir);
				x_H = (ray.x/SCALE - floor(ray.x/SCALE)) * (float)inst->NO.x;
				break;
			}
			ray.x += xof;
			ray.y += yof;
			iter++;
		}

		iter = 1;
		if (cos(ray.fov_st) > 0.001)
		{
			ray.x = SCALE * ((int)inst->pov->x / SCALE) + SCALE;
			ray.y = (inst->pov->x - ray.x) * (sin(ray.fov_st) / cos(ray
																			.fov_st)) + inst->pov->y;
			xof = SCALE;
			yof = -xof * (sin(ray.fov_st) / cos(ray.fov_st));
		}
		else if (cos(ray.fov_st) < -0.001)
		{
			ray.x = SCALE * ((int)inst->pov->x / SCALE) - 0.0001;
			ray.y = (inst->pov->x - ray.x) * (sin(ray.fov_st) / cos(ray
																			.fov_st)) + inst->pov->y;
			xof = -SCALE;
			yof = -xof * (sin(ray.fov_st) / cos(ray.fov_st));
		}
		else
		{
			iter = 0;
		}
		while (iter > 0 && ray.y >= 0 && ray.x >= 0)
		{
			if (ft_is_hit(inst->l->lvl, (int)ray.y / SCALE, (int)ray.x / SCALE))
			{
				dstV = (ray.x - inst->pov->x) * cos(inst->pov->dir) -
					   (ray.y - inst->pov->y) * sin(inst->pov->dir);
				x_V = (ray.y/SCALE - floor(ray.y/SCALE)) * (float)inst->NO.x;
				break;
			}
			ray.x += xof;
			ray.y += yof;
			iter++;
		}
		if (dstH > dstV)
		{
			dst = dstV;
			x_tx = x_V;
			tx_drw = &inst->WE;
			if (cos(ray.fov_st) < 0)
				tx_drw = &inst->EA;
		}
		else
		{
			dst = dstH;
			x_tx = x_H;
			tx_drw = &inst->NO;
			if (sin(ray.fov_st) < 0)
				tx_drw = &inst->SO;
		}
		y= -1;
		act = (192 * inst->l->res_x) / (-1.0 * dst * tan(30));
		while (y < act)
		{
			y++;
			if (y > (mid))
				break;
			col_up = ft_get_pixel_col(tx_drw, x_tx, tx_drw->y * (act -
																 y) /
													(2*act));
			col_dwn = ft_get_pixel_col(tx_drw, x_tx, tx_drw->y * (act +
																  y)/
													 (2*act));
			ft_pixel_put_image(inst, x, mid - y, col_up);
			ft_pixel_put_image(inst, x, mid + y, col_dwn);
		}
		x--;
		ray.fov_st += M_PI/(3 * inst->l->res_x);
		//	ray.fov_st = rnd_ang(ray.fov_st);
		ray.fov_end += M_PI/(3 * inst->l->res_x);
	}
}
