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

	if (!(l = ft_calloc(sizeof(t_legend), 1)))
	{
		perror("Error\n->leg");
		return (NULL);
	}
	return (l);
}
