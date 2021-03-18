/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarthus <dkarthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 16:08:37 by dkarthus          #+#    #+#             */
/*   Updated: 2021/03/19 01:10:35 by dkarthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	ft_hit(t_vars *inst, float ang, int sign)
{
	int y;
	int x;

	y = (int)(inst->pov.y - sign * sin(ang));
	x = (int)(inst->pov.x + sign * cos(ang));
	if (inst->l.lvl[y][x] == '1' || inst->l.lvl[y][x] == '2')
		return (0);
	return (1);
}

static void	ft_adjust_pos(t_vars *inst, float ang, int sign)
{
	inst->pov.y = inst->pov.y - sign * sin(ang) / 2;
	inst->pov.x = inst->pov.x + sign * cos(ang) / 2;
}

int			key_hook(int keycode, t_vars *inst)
{
	if (keycode == 119 && ft_hit(inst, inst->pov.dir, 1))
		ft_adjust_pos(inst, inst->pov.dir, 1);
	if (keycode == 115 && ft_hit(inst, inst->pov.dir, -1))
		ft_adjust_pos(inst, inst->pov.dir, -1);
	if (keycode == 100 && ft_hit(inst, inst->pov.dir + M_PI_2, -1))
		ft_adjust_pos(inst, inst->pov.dir + M_PI_2, -1);
	if (keycode == 97 && ft_hit(inst, inst->pov.dir + M_PI_2, 1))
		ft_adjust_pos(inst, inst->pov.dir + M_PI_2, 1);
	if (keycode == 65363)
		inst->pov.dir = inst->pov.dir - 0.05;
	if (keycode == 65361)
		inst->pov.dir = inst->pov.dir + 0.05;
	if (keycode == 65307)
		full_exit(inst);
	return (0);
}

int			full_exit(t_vars *inst)
{
	if (inst->img)
		mlx_destroy_image(inst->mlx, inst->img);
	if (inst->no.img)
		mlx_destroy_image(inst->mlx, inst->no.img);
	if (inst->so.img)
		mlx_destroy_image(inst->mlx, inst->so.img);
	if (inst->we.img)
		mlx_destroy_image(inst->mlx, inst->we.img);
	if (inst->ea.img)
		mlx_destroy_image(inst->mlx, inst->ea.img);
	if (inst->spr.img)
		mlx_destroy_image(inst->mlx, inst->spr.img);
	ft_free_leg(&inst->l);
	if (inst->dsts != NULL)
		free(inst->dsts);
	if (inst->win)
		mlx_destroy_window(inst->mlx, inst->win);
	if (inst->mlx)
		free(inst->mlx);
	exit(0);
}
