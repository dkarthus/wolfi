/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_rev4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarthus <dkarthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 15:04:35 by dkarthus          #+#    #+#             */
/*   Updated: 2020/12/19 19:06:00 by dkarthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_pixel_put_image(t_vars *inst, int x, int y, int col)
{
	char *dst;

	dst = inst->addr + (x * (inst->bpp / 8) + y * inst->line_len);
	*(unsigned int *)dst = col;
}
/*
static unsigned int ft_get_pixel_col(t_vars *inst, int x, int y)
{
	char *dst;

	dst = inst->addr + (x * (inst->bpp / 8) + y * inst->line_len);
	return (*(unsigned int *)dst);
}
*/
static float ft_deg_rad(int deg)
{
	return (deg * M_PI / 180.0);
}

int ft_draw_rays(t_vars *inst)
{
	t_obj ray;
	double dstW = 10000000;
	double dstH = 10000000;
	double dst;
	int x;
	int y;
	double mid;
	double xof;
	double yof;
	int iter;

	mlx_clear_window(inst->mlx, inst->win);
	inst->img = mlx_new_image(inst->mlx, inst->l->res_x, inst->l->res_y);
	inst->addr = mlx_get_data_addr(inst->img, &inst->bpp, &inst->line_len, &inst
			->endian);
	y = 0;
	mid = inst->l->res_y / 2;
	while (y < mid)
	{
		x = 0;
		while(x < inst->l->res_x)
		{
			ft_pixel_put_image(inst, (int)x, (int)y, inst->l->c_trgb);
			x++;
		}
		y++;
	}
	while (y < inst->l->res_y)
	{
		x = 0;
		while(x < inst->l->res_x)
		{
			ft_pixel_put_image(inst, (int)x, (int)y, inst->l->f_trgb);
			x++;
		}
		y++;
	}
	ray.fov_st = inst->pov->dir - M_PI / 6;
	ray.fov_end = inst->pov->dir + M_PI / 6;
	x = 0;
	while (ray.fov_st <= ray.fov_end || x < inst->l->res_x)
	{
		iter = 1;
		if (sin(ray.fov_st) > 0.01)
		{
			ray.y = (((int)inst->pov->y >> 6) << 6) - 0.0001;
			ray.x = ((inst->pov->y - ray.y) * cos(ray.fov_st)) / sin(ray
			.fov_st) + inst->pov->x;
			yof = -SCALE;
			xof = (-yof * cos(ray.fov_st)) / sin(ray.fov_st);
		}
		else if (sin(ray.fov_st) < -0.01)
		{
			ray.y = (((int)inst->pov->y >> 6) << 6) + SCALE;
			ray.x = ((ray.y - inst->pov->y) * cos(ray.fov_st)) / sin(ray
			.fov_st) + inst->pov->x;
			yof = SCALE;
			xof = (-yof * cos(ray.fov_st)) / sin(ray.fov_st);
		}
		else
		{
			ray.x = inst->pov->x;
			ray.y = inst->pov->y;
			iter = 0;
		}
		while (iter > 0)
		{
			if (inst->l->lvl[(int)ray.y / SCALE][(int)ray.x / SCALE] != '1')
			{
				dstW = sqrt((ray.x - inst->pov->x) * (ray.x - inst->pov->x) +
					   (ray.y - inst->pov->y) * (ray.y - inst->pov->y));
				break;
			}
			ray.x += xof;
			ray.y += yof;
			iter++;
		}


		iter = 1;
		if (cos(ray.fov_st) > 0.01)
		{
			ray.x = (((int)inst->pov->x >> 6 ) << 6) + SCALE;
			ray.y = ((ray.x - inst->pov->x) * sin(ray.fov_st)) / cos(ray
			.fov_st) + inst->pov->y;
			xof = SCALE;
			yof = (-xof * sin(ray.fov_st)) / cos(ray.fov_st);
		}
		else if (cos(ray.fov_st) < -0.01)
		{
			ray.x = (((int)inst->pov->x >> 6) << 6) - 0.0001;
			ray.y = ((inst->pov->x - ray.x) * sin(ray.fov_st)) / cos(ray
			.fov_st) + inst->pov->y;
			xof = -SCALE;
			yof = (-xof * sin(ray.fov_st)) / cos(ray.fov_st);
		}
		else
		{
			ray.x = inst->pov->x;
			ray.y = inst->pov->y;
			iter = 0;
		}
		while (iter)
		{
			if (inst->l->lvl[(int)ray.y / SCALE][(int)ray.x / SCALE] != '1')
			{
				dstH = sqrt((ray.x - inst->pov->x) * (ray.x - inst->pov->x) +
						(ray.y - inst->pov->y) * (ray.y - inst->pov->y));
				break;
			}
			ray.x += xof;
			ray.y += yof;
			iter++;
		}
		/*ray.y = fabs(inst->pov->y - ray.y);
		ray.x = fabs(inst->pov->x - ray.x);
		dst = fabs(ray.x * cos(inst->pov->dir)) + fabs(ray.y * sin
				(inst->pov->dir));
		dst = sqrt(ray.y * ray.y + ray.x * ray.x) * cos(fabs(inst->pov->dir -
				fabs(ray.fov_st)));*/
		dst = dstH > dstW ? dstW : dstH;
		y = -1;
		while (y < (inst->l->res_y / dst))
		{
			y++;
			if (y > (mid - 1))
				continue;
			ft_pixel_put_image(inst, x, mid - y, 0x990099);
			ft_pixel_put_image(inst, x, mid + y, 0x990099);
		}
		x++;
		ray.fov_st += M_PI/(3 * inst->l->res_x);
	}
	mlx_put_image_to_window(inst->mlx, inst->win, inst->img, 0, 0);
	mlx_destroy_image(inst->mlx, inst->img);
	return (0);
}

static int	key_hook(int keycode, t_vars *inst)
{
	double y;
	double x;

	y = inst->pov->y;
	x = inst->pov->x;
	float j = 0.5;
	if (keycode == 13 && inst->l->lvl[(int) ((y + j * sin(inst->pov->dir)) /
	SCALE)][(int) ((x + j * cos(inst->pov->dir)) / SCALE)] != '1')
	{
		inst->pov->y = inst->pov->y + j * sin(inst->pov->dir);
		inst->pov->x = inst->pov->x + j * cos(inst->pov->dir);
	}
	if (keycode == 1 && inst->l->lvl[(int) ((y - j * sin(inst->pov->dir)) /
	SCALE)][(int) ((x - j * cos(inst->pov->dir)) / SCALE)] != '1')
	{
		inst->pov->x = inst->pov->x - j * cos(inst->pov->dir);
		inst->pov->y = inst->pov->y - j * sin(inst->pov->dir);
	}
	if (keycode == 0 && inst->l->lvl[(int) ((y - j * sin(inst->pov->dir +
	M_PI / 2)) / SCALE)][(int) ((x - j * cos(inst->pov->dir + M_PI / 2)) /
	SCALE)] != '1')
	{
		inst->pov->x = inst->pov->x - j * cos(inst->pov->dir + M_PI / 2);
		inst->pov->y = inst->pov->y - j * sin(inst->pov->dir + M_PI / 2);
	}
	if (keycode == 2 && inst->l->lvl[(int) ((y - j * sin(inst->pov->dir -
	M_PI / 2)) / SCALE)][(int) ((x - j * cos(inst->pov->dir - M_PI / 2)) /
	SCALE)] != '1')
	{
		inst->pov->x = inst->pov->x - j * cos(inst->pov->dir - M_PI / 2);
		inst->pov->y = inst->pov->y - j * sin(inst->pov->dir - M_PI / 2);
	}
	if (keycode == 123)
	{
		inst->pov->dir = inst->pov->dir - 0.0174533;
		if (inst->pov->dir < 0)
			inst->pov->dir += 2 * (float)M_PI;
	}
	if (keycode == 124)
	{
		inst->pov->dir = inst->pov->dir + 0.0174533;
		if (inst->pov->dir > 2 * M_PI)
			inst->pov->dir -= 2 * (float)M_PI;
	}
	ft_draw_rays(inst);
	return (0);
}
/*
static int	x_exit(t_vars *inst)
{
	mlx_destroy_image(inst->mlx, inst->img);
	mlx_destroy_window(inst->mlx, inst->win);
	exit (0);
}
*/
static double ft_set_ang(char angle)
{
	if (angle == 'E')
		return (0);
	if (angle == 'S')
		return (1.5708);
	if (angle == 'W')
		return (M_PI);
	if (angle == 'N')
		return (4.7124);
	return (0);
}

static t_obj *ft_player_init(char **map)
{
	t_obj *plr;
	int i;
	int j;
	char *ref = "WESN";
	char *angle;

	if (!(plr = ft_calloc(1, sizeof(t_obj))))
		return (NULL);
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if ((angle = ft_strchr(ref, map[i][j])))
			{
				plr->y = i * SCALE + SCALE / 2;
				plr->x = j * SCALE + SCALE / 2;
				plr->dir = ft_set_ang(*angle);
				return (plr);
			}
			j++;
		}
		i++;
	}
	return (0);
}

static void ft_get_txtr(t_vars *inst)
{
	inst->tx->NO = mlx_xpm_file_to_image(inst->mlx, inst->l->NO,
										 &inst->tx->wNO, &inst->tx->hNO);
	inst->tx->SO = mlx_xpm_file_to_image(inst->mlx, inst->l->SO,
										 &inst->tx->wSO, &inst->tx->hSO);
	inst->tx->WE = mlx_xpm_file_to_image(inst->mlx, inst->l->WE,
										 &inst->tx->wWE, &inst->tx->hWE);
	inst->tx->EA = mlx_xpm_file_to_image(inst->mlx, inst->l->EA,
										 &inst->tx->wEA, &inst->tx->hEA);
	inst->tx->SPR = mlx_xpm_file_to_image(inst->mlx, inst->l->spr,
										  &inst->tx->wSPR, &inst->tx->hSPR);
}

int main(void)
{
	char		**map;
	t_vars		inst;
	t_legend	*l;
	t_txtr		tx;

	if (!(l = ft_leg_init()))
		return (-1);
	map = ft_parse("/Users/dkarthus/cub3d/map.cub");
	if (!(ft_parse_legend(map, l)))
		return (-1);
	inst.mlx = mlx_init();
	inst.win = mlx_new_window(inst.mlx, l->res_x, l->res_y, "Hell!");
	inst.l = l;
	inst.tx = &tx;
	inst.pov = ft_player_init(inst.l->lvl);
	ft_get_txtr(&inst);
	ft_draw_rays(&inst);
//	mlx_loop_hook(inst.mlx, &ft_draw_rays, &inst);
//	mlx_hook(inst.win, 17, 0, key_hook, &inst);
	mlx_key_hook(inst.win, &key_hook, &inst);
	mlx_loop(inst.mlx);
	return (0);
}

