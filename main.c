/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarthus <dkarthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 16:15:59 by dkarthus          #+#    #+#             */
/*   Updated: 2020/12/06 20:10:58 by dkarthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
/*
int main(int argc, char **argv)
{
	void	*mlx;
	void	*mlx_win;
	int 	x = 100;
	int		y = 100;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 640, 480, "Hello world!");
	while(y++ < 200)
	{
		x = 100;
		while (x++ < 200)
			mlx_pixel_put(mlx, mlx_win, x, y, 0xFFFFFF);;
	}
	mlx_loop(mlx);
}
*/

int main(void)
{
	char **map;
	int	i;

	i = 0;
	map = ft_parse("/Users/dkarthus/cub3d/map.cub");
	while(map[i])
	{
		printf("%s\n", map[i]);
		free(map[i]);
		i++;
	}
	free(map[i]);
	free(map);
	return (0);
}