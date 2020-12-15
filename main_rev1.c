/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarthus <dkarthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 16:15:59 by dkarthus          #+#    #+#             */
/*   Updated: 2020/12/11 20:06:47 by dkarthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_pixel_put_image(t_vars *img, int x, int y, int col)
{
	char *dst;

	dst = img->addr + (x * (img->bpp / 8) + y * img->line_len);
	*(unsigned int *)dst = col;
}


static int	key_hook(int keycode, t_vars *inst)
{
	mlx_clear_window(inst->mlx, inst->win);
	if (keycode == 13)
		inst->pov->y = inst->pov->y - 3;
	if (keycode == 1)
		inst->pov->y = inst->pov->y + 3;
	if (keycode == 0)
		inst->pov->x = inst->pov->x - 3;
	if (keycode == 2)
		inst->pov->x = inst->pov->x + 3;
	ft_draw_map(inst);
	mlx_put_image_to_window(inst->mlx, inst->win, inst->img, 0, 0);
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
t_obj *ft_player_init(char **map)
{
	t_obj *plr;
	int i;
	int j;
	char *ref = "WESN";

	if (!(plr = ft_calloc(1, sizeof(t_obj))))
		return (NULL);
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr(ref, map[i][j]))
			{
				plr->y = i * 20;
				plr->x = j * 20;
				map[i][j] = '0';
				return (plr);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void ft_draw_plr(t_vars *inst)
{
	int y;
	int x;

	y = inst->pov->y;
	while(y < (inst->pov->y + 20))
	{
		x = inst->pov->x;
		while(x < (inst->pov->x + 20))
		{
			ft_pixel_put_image(inst, x, y, 0x0000FF00);
			x++;
		}
		y++;
	}
}

int	ft_draw_map(t_vars *inst)
{
	int 	x;
	int		y;
	int		i;
	int 	j;

	i = 0;
	while(inst->lvl[i])
	{
		j = 0;
		while(inst->lvl[i][j])
		{
			if (inst->lvl[i][j] == '1')
			{
				x = j * 20;
				while (x++ < (j * 20 + 20))
				{
					y = i * 20;
					while (y++ < (i * 20 + 20))
						ft_pixel_put_image(inst, x, y, 0xffffff);
				}
			}
			j++;
		}
		i++;
	}
	draw_plr(inst);
	return (0);
}

int main(void)
{
	char **map;
	t_vars inst;
	t_legend *l;

	inst.mlx = mlx_init();
	inst.win = mlx_new_window(inst.mlx, 640, 480, "Hell!");
	inst.img = mlx_new_image(inst.mlx, 640, 480);
	inst.addr = mlx_get_data_addr(inst.img, &inst.bpp, &inst.line_len, &inst
	.endian);
	if (!(l = ft_leg_init()))
		return (-1);
	map = ft_parse("/Users/dkarthus/cub3d/map.cub");
	if (!(ft_parse_legend(map, l)))
		return (-1);
	inst.lvl = l->lvl;
	inst.pov = player_init(inst.lvl);
	ft_draw_map(&inst);
	mlx_put_image_to_window(inst.mlx, inst.win, inst.img, 0, 0);
//	mlx_destroy_image(inst.mlx, inst.img);
//	mlx_hook(inst.win, 17, 0, key_hook, &inst);
	mlx_key_hook(inst.win, key_hook, &inst);
//	mlx_loop_hook(inst.mlx, key_hook, &inst);
	mlx_loop(inst.mlx);
	return (0);
}