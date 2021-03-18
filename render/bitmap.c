/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarthus <dkarthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 14:49:25 by dkarthus          #+#    #+#             */
/*   Updated: 2021/03/19 00:49:34 by dkarthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static unsigned int	ft_get_col(t_vars *inst, int x, int y)
{
	char *dst;

	dst = inst->addr + (x * (inst->bpp / 8) + y * inst->line_len);
	return (*(unsigned int *)dst);
}

static void			ft_fill_header(t_vars *inst, int fd)
{
	int buf;

	write(fd, "BM", 2);
	buf = 54 + 4 * inst->l.res_x * inst->l.res_y;
	write(fd, &buf, 4);
	buf = 0;
	write(fd, &buf, 4);
	buf = 54;
	write(fd, &buf, 4);
	buf = 40;
	write(fd, &buf, 4);
	write(fd, &inst->l.res_x, 4);
	write(fd, &inst->l.res_y, 4);
	buf = 1;
	write(fd, &buf, 2);
	write(fd, &inst->bpp, 2);
	buf = 0;
	write(fd, &buf, 4);
	write(fd, &buf, 4);
	write(fd, &buf, 4);
	write(fd, &buf, 4);
	write(fd, &buf, 4);
}

void				ft_render_bmp(t_vars *inst)
{
	int				fd;
	int				x;
	int				y;
	unsigned int	col;

	if (!(fd = open("Cube3d.bmp", O_RDWR | O_CREAT | O_TRUNC, S_IRWXU)))
	{
		perror("Error\nCouldn't write/create BMP file.");
		exit(0);
	}
	ft_fill_header(inst, fd);
	y = inst->l.res_y - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < inst->l.res_x)
		{
			col = ft_get_col(inst, x, y);
			write(fd, &col, 4);
			x++;
		}
		y--;
	}
	close(fd);
	full_exit(inst);
}
