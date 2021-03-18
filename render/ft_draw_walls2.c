/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_walls2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarthus <dkarthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 20:33:22 by dkarthus          #+#    #+#             */
/*   Updated: 2021/03/19 00:52:14 by dkarthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static float	y_calc_util(t_vars *inst, t_obj *ray, float xof, float yof)
{
	float dst_y;

	dst_y = 10000;
	while ((sinf(ray->fov_st) > 0.001) || (sinf(ray->fov_st) < -0.001))
	{
		if (ft_is_hit(inst, (int)ray->y, (int)ray->x, ray))
		{
			dst_y = (ray->x - inst->pov.x) * cosf(inst->pov.dir) -
					(ray->y - inst->pov.y) * sinf(inst->pov.dir);
			ray->txt_yof = (ray->x - floorf(ray->x));
			return (dst_y);
		}
		ray->x += xof;
		ray->y += yof;
	}
	return (dst_y);
}

static float	ft_y_collision(t_vars *inst, t_obj *ray)
{
	float	xof;
	float	yof;

	if (sinf(ray->fov_st) > 0.001)
	{
		ray->y = (int)inst->pov.y - 0.0001;
		ray->x = (inst->pov.y - ray->y) * (cosf(ray->fov_st) /
			sinf(ray->fov_st)) + inst->pov.x;
		yof = -1;
		xof = -yof * (cosf(ray->fov_st) / sinf(ray->fov_st));
	}
	else if (sinf(ray->fov_st) < -0.001)
	{
		ray->y = (int)inst->pov.y + 1;
		ray->x = (inst->pov.y - ray->y) * (cosf(ray->fov_st) /
			sinf(ray->fov_st)) + inst->pov.x;
		yof = 1;
		xof = -yof * (cosf(ray->fov_st) / sinf(ray->fov_st));
	}
	return (y_calc_util(inst, ray, xof, yof));
}

static float	x_calc_util(t_vars *inst, t_obj *ray, float xof, float yof)
{
	float dst_x;

	dst_x = 10000;
	while ((cosf(ray->fov_st) > 0.001) || (cosf(ray->fov_st) < -0.001))
	{
		if (ft_is_hit(inst, (int)ray->y, (int)ray->x, ray))
		{
			dst_x = (ray->x - inst->pov.x) * cosf(inst->pov.dir) -
					(ray->y - inst->pov.y) * sinf(inst->pov.dir);
			ray->txt_xof = (ray->y - floorf(ray->y));
			return (dst_x);
		}
		ray->x += xof;
		ray->y += yof;
	}
	return (dst_x);
}

static float	ft_x_collision(t_vars *inst, t_obj *ray)
{
	float	xof;
	float	yof;

	if (cosf(ray->fov_st) > 0.001)
	{
		ray->x = (int)inst->pov.x + 1;
		ray->y = (inst->pov.x - ray->x) * (sinf(ray->fov_st) /
			cosf(ray->fov_st)) + inst->pov.y;
		xof = 1;
		yof = -xof * (sinf(ray->fov_st) / cosf(ray->fov_st));
	}
	else if (cosf(ray->fov_st) < -0.001)
	{
		ray->x = (int)inst->pov.x - 0.0001;
		ray->y = (inst->pov.x - ray->x) * (sinf(ray->fov_st) /
			cosf(ray->fov_st)) + inst->pov.y;
		xof = -1;
		yof = -xof * (sinf(ray->fov_st) / cosf(ray->fov_st));
	}
	return (x_calc_util(inst, ray, xof, yof));
}

void			ft_render_walls(t_vars *inst)
{
	int		x;
	float	dst;
	float	dst_y;
	float	dst_x;
	t_obj	ray;

	x = inst->l.res_x - 1;
	ray.fov_st = inst->pov.dir - (float)(M_PI / 6.0);
	if (!(inst->dsts = malloc(sizeof(float) * inst->l.res_x)))
	{
		perror("Error\n Couldn't allocate in ft_render_walls\n");
		full_exit(inst);
	}
	while (x >= 0)
	{
		ray.dir = x;
		dst_y = ft_y_collision(inst, &ray);
		dst_x = ft_x_collision(inst, &ray);
		dst = ft_dst_sort(dst_y, dst_x, &ray, inst);
		inst->dsts[x] = dst;
		ft_draw_walls(inst, &ray, dst, x);
		x--;
		ray.fov_st += (float)(M_PI / (3 * inst->l.res_x));
	}
}
