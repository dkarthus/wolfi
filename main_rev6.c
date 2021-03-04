/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_rev6.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarthus <dkarthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 19:36:42 by dkarthus          #+#    #+#             */
/*   Updated: 2021/03/01 23:39:47 by dkarthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int ft_is_hit(char **map, int y, int x)
{
	int strs;

	strs = 0;
	if (y <= 0 || x <= 0)
		return (1);
	while(map[strs])
		strs++;
	if (y >= strs - 1)
		return (1);
	if (x >= ft_strlen(map[y]) - 1)
		return (1);
	if (map[y][x] == '1' || map[y][x] == ' ')
		return (1);
	return (0);
}

void ft_pixel_put_image(t_vars *inst, int x, int y, unsigned int col)
{
	char *dst;

	dst = inst->addr + (x * (inst->bpp / 8) + y * inst->line_len);
	*(unsigned int *)dst = col;
}

static unsigned int ft_get_pixel_col(t_txt *txt, int x, int y)
{
	char *dst;

	dst = txt->addr + (x * (txt->bpp / 8) + y * txt->line_len);
	return (*(unsigned int *)dst);
}
/*
static float dtr(int deg)
{
	return (deg * M_PI / 180.0);
}
*/
double rnd_ang(double ang)
{
	if (ang > 6.2657)
		ang -= 6.2832;
	if (ang < 0)
		ang += 6.2832;
	return (ang);
}


int ft_draw_rays(t_vars *inst)
{
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
//	ray.fov_st = 4.398;
	ray.fov_st = inst->pov->dir - M_PI / 6.0;
//	ray.fov_st = rnd_ang(ray.fov_st);
	ray.fov_end = 0;
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
//	mlx_clear_window(inst->mlx, inst->win);
	mlx_put_image_to_window(inst->mlx, inst->win, inst->img, 0, 0);
	mlx_do_sync(inst->mlx);
//	mlx_destroy_image(inst->mlx, inst->img);
	return (0);
}

static int	key_hook(int keycode, t_vars *inst)
{
	float y;
	float x;

	y = inst->pov->y;
	x = inst->pov->x;
	float j = 32;
	if (keycode == 119 && inst->l->lvl[(int) ((y + j * sin(inst->pov->dir)) /
											  SCALE)][(int) ((x + j * cos(inst->pov->dir)) / SCALE)] != '1')
	{
		inst->pov->y = inst->pov->y - j * sin(inst->pov->dir);
		inst->pov->x = inst->pov->x + j * cos(inst->pov->dir);
	}
	if (keycode == 115 && inst->l->lvl[(int) ((y - j * sin(inst->pov->dir)) /
											  SCALE)][(int) ((x - j * cos(inst->pov->dir)) / SCALE)] != '1')
	{
		inst->pov->x = inst->pov->x - j * cos(inst->pov->dir);
		inst->pov->y = inst->pov->y + j * sin(inst->pov->dir);
	}
	if (keycode == 100 && inst->l->lvl[(int) ((y - j * sin(inst->pov->dir +
														  M_PI / 2.0)) / SCALE)][(int) ((x - j * cos(inst->pov->dir + M_PI / 2.0)) /
																						SCALE)] != '1')
	{
		inst->pov->x = inst->pov->x - j * cos(inst->pov->dir + M_PI / 2.0);
		inst->pov->y = inst->pov->y + j * sin(inst->pov->dir + M_PI / 2.0);
	}
	if (keycode == 97 && inst->l->lvl[(int) ((y - j * sin(inst->pov->dir -
														   M_PI / 2.0)) / SCALE)][(int) ((x - j * cos(inst->pov->dir - M_PI / 2.0)) /
																						 SCALE)] != '1')
	{
		inst->pov->x = inst->pov->x - j * cos(inst->pov->dir - M_PI / 2.0);
		inst->pov->y = inst->pov->y + j * sin(inst->pov->dir - M_PI / 2.0);
	}
	if (keycode == 65363)
	{
		inst->pov->dir = inst->pov->dir - 0.1;
		inst->pov->dir = rnd_ang(inst->pov->dir);
	}
	if (keycode == 65361)
	{
		inst->pov->dir = inst->pov->dir + 0.1;
		inst->pov->dir = rnd_ang(inst->pov->dir);
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
		return (1.5 * M_PI);
	if (angle == 'W')
		return (M_PI);
	if (angle == 'N')
		return (M_PI_2);
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
	inst->NO.img = mlx_xpm_file_to_image(inst->mlx, inst->l->NO,
										 &inst->NO.x, &inst->NO.y);
	inst->NO.addr = mlx_get_data_addr(inst->NO.img, &inst->NO.bpp,
									  &inst->NO.line_len, &inst->NO.endian);
	inst->SO.img = mlx_xpm_file_to_image(inst->mlx, inst->l->SO,
										 &inst->SO.x, &inst->SO.y);
	inst->SO.addr = mlx_get_data_addr(inst->SO.img, &inst->SO.bpp,
									  &inst->SO.line_len, &inst->SO.endian);
	inst->WE.img = mlx_xpm_file_to_image(inst->mlx, inst->l->WE,
										 &inst->WE.x, &inst->WE.y);
	inst->WE.addr = mlx_get_data_addr(inst->WE.img, &inst->WE.bpp,
									  &inst->WE.line_len, &inst->WE.endian);
	inst->EA.img = mlx_xpm_file_to_image(inst->mlx, inst->l->EA,
										 &inst->EA.x, &inst->EA.y);
	inst->EA.addr = mlx_get_data_addr(inst->EA.img, &inst->EA.bpp,
									  &inst->EA.line_len, &inst->EA.endian);
	inst->SPR.img = mlx_xpm_file_to_image(inst->mlx, inst->l->spr,
										  &inst->SPR.x, &inst->SPR.y);
	inst->SPR.addr = mlx_get_data_addr(inst->SPR.img, &inst->SPR.bpp,
									   &inst->SPR.line_len, &inst->SPR.endian);
}

int main(void)
{
	char		**map;
	t_vars		inst;
	t_legend	*l;
	int sizex, sizey;

	if (!(inst.l = ft_leg_init()))
		return (-1);
	map = ft_parse("/home/dkarthus/CLionProjects/wolfi/map.cub");
	if (!(ft_parse_legend(map, inst.l)))
		return (-1);
	inst.mlx = mlx_init();
	mlx_get_screen_size(inst.mlx, &sizex, &sizey);
	if (sizex > inst.l->res_x)
		inst.l->res_x = sizex;
	if (sizey > inst.l->res_y)
		inst.l->res_y = sizey;
	inst.win = mlx_new_window(inst.mlx, inst.l->res_x, inst.l->res_y, "Hell!");
	//inst.l = l;
	//inst.tx = &tx;
	inst.pov = ft_player_init(inst.l->lvl);
	ft_get_txtr(&inst);
	inst.img = mlx_new_image(inst.mlx, inst.l->res_x, inst.l->res_y);
	inst.addr = mlx_get_data_addr(inst.img, &inst.bpp, &inst.line_len, &inst
			.endian);
	ft_draw_rays(&inst);
	//mlx_loop_hook(inst.mlx, &ft_draw_rays, &inst);
//	mlx_hook(inst.win, 17, 0, key_hook, &inst);
	mlx_key_hook(inst.win, &key_hook, &inst);
	mlx_loop(inst.mlx);
	return (0);
}