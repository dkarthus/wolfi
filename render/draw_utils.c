/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarthus <dkarthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 15:30:38 by dkarthus          #+#    #+#             */
/*   Updated: 2021/03/19 00:48:38 by dkarthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int				ft_create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void			ft_pixel_put_image(t_vars *inst, int x, int y, unsigned int col)
{
	char *dst;

	dst = inst->addr + (x * (inst->bpp / 8) + y * inst->line_len);
	*(unsigned int *)dst = col;
}

unsigned int	ft_get_pixel_col(t_txt *txt, int x, int y)
{
	char *dst;

	dst = txt->addr + (x * (txt->bpp / 8) + y * txt->line_len);
	return (*(unsigned int *)dst);
}

void			ft_draw_ceil_floor(t_vars *inst)
{
	int x;
	int y;

	y = 0;
	while (y < inst->l.res_y / 2)
	{
		x = 0;
		while (x < inst->l.res_x)
		{
			ft_pixel_put_image(inst, x, y, inst->l.c_trgb);
			x++;
		}
		y++;
	}
	while (y < inst->l.res_y)
	{
		x = 0;
		while (x < inst->l.res_x)
		{
			ft_pixel_put_image(inst, x, y, inst->l.f_trgb);
			x++;
		}
		y++;
	}
}
