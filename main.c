/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarthus <dkarthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 16:15:59 by dkarthus          #+#    #+#             */
/*   Updated: 2020/12/10 21:02:26 by dkarthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	key_hook(int keycode, t_t *t)
{
	mlx_clear_window(t->inst->mlx, t->inst->win);
	if (keycode == 13)
		t->plr->y = t->plr->y + 3;
	if (keycode == 1)
		t->plr->y = t->plr->y - 3;
	if (keycode == 0)
		t->plr->x = t->plr->x - 3;
	if (keycode == 2)
		t->plr->x = t->plr->x + 3;
	ft_draw_map(t);
	return (0);
}
/*
static int	x_exit(t_vars *inst)
{
	mlx_destroy_image(inst->mlx, inst->img);
	mlx_destroy_window(inst->mlx, inst->win);
	ft_free_leg(inst->l);
	exit (0);
}
*/
void pixel_put_image(t_vars *img, int y, int x, int col)
{
	char *pxl;

	pxl = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pxl = col;
}

t_obj *player_init(char angl, int i, int j)
{
	t_obj *plr;
	if (!(plr = ft_calloc(1, sizeof(t_obj))))
		return (NULL);
	plr->x = j * 20;
	plr->y = i * 20;
	plr->angle 	= angl;
	return (plr);
}

void draw_plr(t_obj *plr, t_vars *inst)
{
	int y;
	int x;

	y = plr->y;
	while(y < (plr->y + 20))
	{
		x = plr->x;
		while(x < (plr->x + 20))
		{
			pixel_put_image(inst->img, y, x, 0x0000FF00);
			x++;
		}
		y++;
	}
}

int	ft_draw_map(t_t *t)
{
	int 	x;
	int		y;
	int		i;
	int 	j;
	char *ref = "WESN";

	t->inst->img = mlx_new_image(t->inst->mlx, 1000, 1000);
	t->inst->addr = mlx_get_data_addr(t->inst->img, &t->inst->bpp,
	&t->inst->line_len, &t->inst->endian);
	i = 0;
	while(t->inst->l->lvl[i])
	{
		j = 0;
		while(t->inst->l->lvl[i][j])
		{
			if (ft_strchr(ref, t->inst->l->lvl[i][j]))
			{
				t->plr = player_init(t->inst->l->lvl[i][j], i, j);
				t->inst->l->lvl[i][j] = '0';
			}
			if (t->inst->l->lvl[i][j] == '1')
			{
				y = i;
				while (y++ < i + 15)
				{
					x = j;
					while (x++ < j + 15)
					{
						pixel_put_image(t->inst->img, y, x, 0x00FF0000);
					}
				}
			}
			j++;
		}
		i++;
	}
//	draw_plr(t->plr, t->inst);
	mlx_put_image_to_window(t->inst->mlx, t->inst->win, t->inst->img, 0, 0);
	mlx_destroy_image(t->inst->mlx, t->inst->img);
	return (0);
}

int main(void)
{
	char **map;
	t_t t;

	t.inst = malloc(sizeof(t_t));
	t.inst->mlx = mlx_init();
	t.inst->win = mlx_new_window(t.inst->mlx, 1000, 1000, "Hello world!");
//	inst.img = mlx_new_image(inst.mlx, 1000, 1000);
//	inst.addr = mlx_get_data_addr(inst.img, &inst.bpp, &inst.line_len, &inst
//			.endian);
	if (!(t.inst->l = ft_leg_init()))
		return (-1);
	map = ft_parse("/Users/dkarthus/cub3d/map.cub");
	if (!(ft_parse_legend(map, t.inst->l)))
		return (-1);
	ft_draw_map(&t);
//	mlx_hook(inst.win, 17, 0, key_hook, &inst);
	mlx_key_hook(t.inst->win, &key_hook, &t);
	//mlx_loop_hook(inst.mlx, ft_draw_map, &inst);
	mlx_loop(t.inst->mlx);
	return (0);
}

