/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_txt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarthus <dkarthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 21:49:19 by dkarthus          #+#    #+#             */
/*   Updated: 2021/03/19 01:11:15 by dkarthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	ft_txt_to_struct(char *txt_pth, t_txt *txt, t_vars *inst)
{
	txt->img = mlx_xpm_file_to_image(inst->mlx, txt_pth, &txt->x, &txt->y);
	if (txt->img == NULL)
	{
		perror("Error\nCouldn't read txt in ft_txt_to_struct.\n");
		full_exit(inst);
	}
	txt->addr = mlx_get_data_addr(txt->img, &txt->bpp,
	&txt->line_len, &txt->endian);
}

void		ft_get_txtr(t_vars *inst)
{
	ft_txt_to_struct(inst->l.no, &inst->no, inst);
	ft_txt_to_struct(inst->l.so, &inst->so, inst);
	ft_txt_to_struct(inst->l.we, &inst->we, inst);
	ft_txt_to_struct(inst->l.ea, &inst->ea, inst);
	ft_txt_to_struct(inst->l.spr, &inst->spr, inst);
}
