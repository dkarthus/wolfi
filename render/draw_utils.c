/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarthus <dkarthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 15:30:38 by dkarthus          #+#    #+#             */
/*   Updated: 2021/03/10 15:30:38 by dkarthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void ft_pixel_put_image(t_vars *inst, int x, int y, unsigned int col)
{
	char *dst;

	dst = inst->addr + (x * (inst->bpp / 8) + y * inst->line_len);
	*(unsigned int *)dst = col;
}

unsigned int ft_get_pixel_col(t_txt *txt, int x, int y)
{
	char *dst;

	dst = txt->addr + (x * (txt->bpp / 8) + y * txt->line_len);
	return (*(unsigned int *)dst);
}