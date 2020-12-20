/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_rev5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarthus <dkarthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 15:56:01 by dkarthus          #+#    #+#             */
/*   Updated: 2020/12/20 19:22:44 by dkarthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_pixel_put_image(t_vars *inst, int x, int y, int col)
{
	char *dst;

	dst = inst->addr + (x * (inst->bpp / 8) + y * inst->line_len);
	*(unsigned int *)dst = col;
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
				plr->y = i;// * SCALE + SCALE / 2;
				plr->x = j;// * SCALE + SCALE / 2;
				plr->dir = ft_set_ang(*angle);
				return (plr);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int ft_draw_rays(t_vars *inst)
{
	double posX = inst->pov->x;
	double posY = inst->pov->y;
	double rayDirX;
	double rayDirY;
	double dirX = -1;
	double dirY = 0;
	int w;
	int h;
	int mapX = (int)posX;
	int mapY = (int)posY;
	double planeX = 0;
	double planeY = 0.66;
	double cameraX;
	double deltaX;
	double deltaY;
	double sideDisY;
	double sideDisX;
	int stepX;
	int stepY;
	int hit = 1;
	int side;
	double dist;

	mlx_clear_window(inst->mlx, inst->win);
	inst->img = mlx_new_image(inst->mlx, inst->l->res_x, inst->l->res_y);
	inst->addr = mlx_get_data_addr(inst->img, &inst->bpp, &inst->line_len, &inst
			->endian);

	w = 0;
	while (w <= inst->l->res_x)
	{
		cameraX = 2 * w / (double)inst->l->res_x - 1;
		rayDirX = dirX + planeX * cameraX;
		rayDirY = dirY + planeY * cameraX;
		deltaX = (rayDirY == 0) ? 0 : ((rayDirX == 0) ? 1 : fabs(1 / rayDirX));
		deltaY = (rayDirX == 0) ? 0 : ((rayDirY == 0) ? 1 : fabs(1 / rayDirY));
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDisX = (posX - mapX) * deltaX;
		}
		else
		{
			stepX = 1;
			sideDisX = (mapX + 1.0 - posX) * deltaX;

		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDisY = (posY - mapY) *deltaY;
		}
		else
		{
			stepY = 1;
			sideDisY = (mapY + 1.0 - posY) * deltaY;
		}
		while (hit)
		{
			if (sideDisX < sideDisY)
			{
				sideDisX += deltaX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDisY += deltaY;
				mapY += stepY;
				side = 1;
			}
			if (inst->l->lvl[mapY][mapX] == '1')
				hit = 0;
		}
		if (side == 0)
			dist = fabs((mapX - posX + (1 - stepX) / 2) / rayDirX);
		else
			dist = fabs((mapY - posY + (1 - stepY) / 2) / rayDirY);
		h = -1;
		int mid = inst->l->res_y / 2;
		printf("%f\n", dist);
		while (h < inst->l->res_y/ dist)
		{
			h++;
			if (h > mid)
				continue;
			ft_pixel_put_image(inst, w, mid - h, 0x990099);
			ft_pixel_put_image(inst, w, mid + h, 0x990099);
		}
		w++;
	}
	mlx_put_image_to_window(inst->mlx, inst->win, inst->img, 0, 0);
	mlx_destroy_image(inst->mlx, inst->img);
	return (0);
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
	mlx_loop_hook(inst.mlx, &ft_draw_rays, &inst);
//	mlx_hook(inst.win, 17, 0, key_hook, &inst);
//	mlx_key_hook(inst.win, &key_hook, &inst);
	mlx_loop(inst.mlx);
	return (0);
}
