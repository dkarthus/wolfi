/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarthus <dkarthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 21:15:47 by dkarthus          #+#    #+#             */
/*   Updated: 2021/03/18 20:26:45 by dkarthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_get_params(t_vars *inst)
{
	int		size_x;
	int		size_y;

	if (!(inst->mlx = mlx_init()))
	{
		perror("Error\nFail to init mlx");
		full_exit(inst);
	}
	size_y = 8000;
	size_x = 8000;
	if (inst->mode)
		mlx_get_screen_size(inst->mlx, &size_x, &size_y);
	if (size_x < inst->l.res_x)
		inst->l.res_x = size_x;
	if (size_y < inst->l.res_y)
		inst->l.res_y = size_y;
	ft_player_init(inst);
	ft_get_txtr(inst);
}

static void	ft_game_init(t_vars *inst, char *pth)
{
	char	**map;

	if (!(map = ft_parse(pth)))
	{
		perror("Error\n Invalid map");
		full_exit(inst);
	}
	if (!(ft_parse_legend(map, &inst->l)))
		full_exit(inst);
	ft_get_params(inst);
	if (inst->mode && !(inst->win = mlx_new_window(inst->mlx, inst->l.res_x,
		inst->l.res_y, "wubalubadubdub")))
	{
		perror("Error\n Could't init win");
		full_exit(inst);
	}
	if (!(inst->img = mlx_new_image(inst->mlx, inst->l.res_x, inst->l.res_y)))
	{
		perror("Error\nCouldn't create image");
		full_exit(inst);
	}
	inst->addr = mlx_get_data_addr(inst->img, &inst->bpp, &inst->line_len,
		&inst->endian);
}

int			main(int argc, char *argv[])
{
	t_vars inst;

	ft_main_inst_init(&inst);
	if (argc == 2)
	{
		inst.mode = 1;
		ft_game_init(&inst, argv[1]);
		mlx_loop_hook(inst.mlx, &ft_render_img, &inst);
		mlx_hook(inst.win, 33, 0L, &full_exit, &inst);
		mlx_key_hook(inst.win, &key_hook, &inst);
		mlx_loop(inst.mlx);
	}
	if (argc == 3 && !ft_strncmp(argv[2], "-save", 5))
	{
		inst.mode = 0;
		ft_game_init(&inst, argv[1]);
		ft_render_img(&inst);
		ft_render_bmp(&inst);
	}
	ft_putstr_fd("Error\nInvalid argument(s)", 1);
	return (1);
}
