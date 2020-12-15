/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_rev2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarthus <dkarthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 18:29:55 by dkarthus          #+#    #+#             */
/*   Updated: 2020/12/15 15:10:17 by dkarthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_pixel_put_image(t_vars *inst, int x, int y, int col)
{
	char *dst;

	dst = inst->addr + (x * (inst->bpp / 8) + y * inst->line_len);
	*(unsigned int *)dst = col;
}

void ft_draw_rays(t_vars *inst)
{
	t_obj ray;

	ray.start = inst->pov->angle - M_PI / 4;
	ray.end = inst->pov->angle + M_PI / 4;
	while (ray.start <= ray.end)
	{
		ray.y = inst->pov->y;
		ray.x = inst->pov->x;
		while (inst->lvl[(int) (ray.y / SCALE)][(int) (ray.x / SCALE)] != '1')
		{
			ray.x += cos(ray.start);
			ray.y += sin(ray.start);
			ft_pixel_put_image(inst, ray.x, ray.y, 0x990099);
		}
		ray.start += 0.005;
	}

}

static int	key_hook(int keycode, t_vars *inst)
{
	float y;
	float x;

	y = inst->pov->y;
	x = inst->pov->x;
	if (keycode == 13 && inst->lvl[(int)((y - 3) / SCALE)][(int)(x / SCALE)]
	!= '1')
		inst->pov->y = inst->pov->y - 3;
	if (keycode == 1 && inst->lvl[(int)((y + 3) / SCALE)][(int)(x / SCALE)]
	!= '1')
		inst->pov->y = inst->pov->y + 3;
	if (keycode == 0 && inst->lvl[(int)(y / SCALE)][(int)((x - 3) / SCALE)]
	!= '1')
		inst->pov->x = inst->pov->x - 3;
	if (keycode == 2 && inst->lvl[(int)(y / SCALE)][(int)((x + 3) / SCALE)]
	!= '1')
		inst->pov->x = inst->pov->x + 3;
	if (keycode == 123)
		inst->pov->angle = inst->pov->angle - 0.1;
	if (keycode == 124)
		inst->pov->angle = inst->pov->angle + 0.1;
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
float ft_set_ang(char angle)
{
	if (angle == 'W')
		return (0);
	if (angle == 'S')
		return (1.5708);
	if (angle == 'E')
		return (M_PI);
	if (angle == 'N')
		return (4.7124);
	return (0);
}

		t_obj *ft_player_init(char **map)
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
				plr->y = i * SCALE - SCALE / 2;
				plr->x = j * SCALE - SCALE / 2;
				plr->angle = ft_set_ang(*angle);
				return (plr);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_draw_map(t_vars *inst)
{
	int 	x;
	int		y;
	int		i;
	int 	j;

	mlx_clear_window(inst->mlx, inst->win);
	inst->img = mlx_new_image(inst->mlx, 640, 480);
	inst->addr = mlx_get_data_addr(inst->img, &inst->bpp, &inst->line_len, &inst
			->endian);
	inst->addr = mlx_get_data_addr(inst->img, &inst->bpp, &inst->line_len, &inst
			->endian);
	i = 0;
	while(inst->lvl[i])
	{
		j = 0;
		while(inst->lvl[i][j])
		{
			if (inst->lvl[i][j] == '1')
			{
				x = j * SCALE;
				while (x++ < (j * SCALE + SCALE))
				{
					y = i * SCALE;
					while (y++ < (i * SCALE + SCALE))
						ft_pixel_put_image(inst, x, y, 0xffffff);
				}
			}
			j++;
		}
		i++;
	}
	ft_draw_rays(inst);
	mlx_put_image_to_window(inst->mlx, inst->win, inst->img, 0, 0);
	mlx_destroy_image(inst->mlx, inst->img);
	return (0);
}

int main(void)
{
	char **map;
	t_vars inst;
	t_legend *l;

	inst.mlx = mlx_init();
	inst.win = mlx_new_window(inst.mlx, 640, 480, "Hell!");

	if (!(l = ft_leg_init()))
		return (-1);
	map = ft_parse("/Users/dkarthus/cub3d/map.cub");
	if (!(ft_parse_legend(map, l)))
		return (-1);
	inst.lvl = l->lvl;
	inst.pov = ft_player_init(inst.lvl);
	mlx_loop_hook(inst.mlx, &ft_draw_map, &inst);
//	mlx_destroy_image(inst.mlx, inst.img);
//	mlx_hook(inst.win, 17, 0, key_hook, &inst);
	mlx_key_hook(inst.win, &key_hook, &inst);
	mlx_loop(inst.mlx);
	return (0);
}