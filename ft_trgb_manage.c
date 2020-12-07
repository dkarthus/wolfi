/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trgb_manage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarthus <dkarthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 14:13:01 by dkarthus          #+#    #+#             */
/*   Updated: 2020/12/07 14:13:01 by dkarthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	ft_get_t(int trgb)
{
	return (trgb & (0xFF << 24));
}

int	ft_get_r(int trgb)
{
	return (trgb & (0xFF << 16));
}

int	ft_get_g(int trgb)
{
	return (trgb & (0xFF << 8));
}

int	ft_get_b(int trgb)
{
	return (trgb & 0xFF);
}
