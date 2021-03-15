/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarthus <dkarthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 15:30:38 by dkarthus          #+#    #+#             */
/*   Updated: 2021/03/15 21:13:52 by dkarthus         ###   ########.fr       */
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

void ft_get_txtr(t_vars *inst)
{
	inst->NO.img = mlx_xpm_file_to_image(inst->mlx, inst->l.NO,
										 &inst->NO.x, &inst->NO.y);
	inst->NO.addr = mlx_get_data_addr(inst->NO.img, &inst->NO.bpp,
									  &inst->NO.line_len, &inst->NO.endian);
	inst->SO.img = mlx_xpm_file_to_image(inst->mlx, inst->l.SO,
										 &inst->SO.x, &inst->SO.y);
	inst->SO.addr = mlx_get_data_addr(inst->SO.img, &inst->SO.bpp,
									  &inst->SO.line_len, &inst->SO.endian);
	inst->WE.img = mlx_xpm_file_to_image(inst->mlx, inst->l.WE,
										 &inst->WE.x, &inst->WE.y);
	inst->WE.addr = mlx_get_data_addr(inst->WE.img, &inst->WE.bpp,
									  &inst->WE.line_len, &inst->WE.endian);
	inst->EA.img = mlx_xpm_file_to_image(inst->mlx, inst->l.EA,
										 &inst->EA.x, &inst->EA.y);
	inst->EA.addr = mlx_get_data_addr(inst->EA.img, &inst->EA.bpp,
									  &inst->EA.line_len, &inst->EA.endian);
	inst->SPR.img = mlx_xpm_file_to_image(inst->mlx, inst->l.spr,
										  &inst->SPR.x, &inst->SPR.y);
	inst->SPR.addr = mlx_get_data_addr(inst->SPR.img, &inst->SPR.bpp,
									   &inst->SPR.line_len, &inst->SPR.endian);
}