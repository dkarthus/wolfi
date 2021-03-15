/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarthus <dkarthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 21:15:47 by dkarthus          #+#    #+#             */
/*   Updated: 2021/03/15 22:55:45 by dkarthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void ft_adjust_res(t_vars *inst)
{
	int		size_x;
	int		size_y;

	mlx_get_screen_size(inst->mlx, &size_x, &size_y);
	if (size_x < inst->l->res_x)
		inst->l->res_x = size_x;
	if (size_y < inst->l->res_y)
		inst->l->res_y = size_y;
}

static void ft_game_on(t_vars *inst, char *pth)
{
	char	**map;

	if (!(map = ft_parse(pth)))
	{
		ft_putstr_fd("Error\n Invalid map", 1);
		exit (0);
	}
	if (!(ft_parse_legend(map, inst->l)))
		exit (0);
	inst->mlx = mlx_init();
	ft_adjust_res(inst);
	ft_player_init(inst);
	ft_get_txtr(inst);
	if (!(inst->win = mlx_new_window(inst->mlx, inst->l->res_x,
								  inst->l->res_y, "wubalubadubdub")))
	{
		ft_putstr_fd("Error\n Could't init win", 1);
		exit (0);
	}
	if (!(inst->img = mlx_new_image(inst->mlx, inst->l->res_x, inst->l->res_y)))
	{
		ft_putstr_fd("Error\nCouldn't create image", 1);
		exit (0);
	}
}

int main(int argc, char *argv[])
{
	t_vars inst;

	if (argc == 2)
		ft_game_on(&inst, argv[1]);
	if (argc == 3 && !ft_strncmp(argv[2], "-save", 5))
		ft_screenshot(&inst, argv[1]);
	ft_putstr_fd("Error\nInvalid argument(s)", 1);
	return (1);
}