/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_leg_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarthus <dkarthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 13:59:28 by dkarthus          #+#    #+#             */
/*   Updated: 2020/12/08 14:36:00 by dkarthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_legend	*ft_leg_init()
{
	t_legend *l;

	if (!(l = malloc(sizeof(t_legend))))
	{
		perror("Error\n->leg");
		return (NULL);
	}
	l->res_y = 0;
	l->res_x = 0;
	l->f_trgb = 0;
	l->c_trgb = 0;
	l->NO = NULL;
	l->SO = NULL;
	l->WE = NULL;
	l->EA = NULL;
	l->spr = NULL;
	l->lvl = NULL;
	return (l);
}
