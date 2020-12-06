/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarthus <dkarthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 15:03:47 by dkarthus          #+#    #+#             */
/*   Updated: 2020/12/06 20:46:35 by dkarthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./inc/libft.h"
# include "./inc/mlx.h"
# include <fcntl.h>

#         include <stdio.h>

typedef struct	s_legend
{
	int		res_y;
	int		res_x;
	long	f_rgb;
	long	s_rgb;
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	char	**lvl;
}				t_legend;

char	**ft_parse(char *file);
int		ft_parse_legend(char **map, t_legend *f);

#endif