/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_legend_utils2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarthus <dkarthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 13:59:23 by dkarthus          #+#    #+#             */
/*   Updated: 2020/12/07 18:56:17 by dkarthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_parse_wtexture(char *line, t_legend *l, int *flag)
{
	int		fd;
	char 	*tmp;

	if (line[1] != 'E' || line[2] != ' ')
	{
		ft_putstr_fd("Error\nWrong WE texture format", 1);
		return(-1);
	}
	line = line + 3;
	tmp = ft_strdup(line);
	if (!(l->WE = ft_strtrim(tmp, " ")))
	{
		free(tmp);
		perror("Error\n->WE");
		return (-1);
	}
	free(tmp);
	l->WE = ft_strdup(line);
	if ((fd = open(l->WE, O_RDONLY)) < 0)
	{
		ft_putstr_fd("Error\nWrong WE texture format", 1);
		return (-1);
	}
	close(fd);
	*flag = *flag + 1;
	return (1);
}

int		ft_parse_etexture(char *line, t_legend *l, int *flag)
{
	int		fd;
	char 	*tmp;

	if (line[1] != 'A' || line[2] != ' ')
	{
		ft_putstr_fd("Error\nWrong EA texture format", 1);
		return(-1);
	}
	line = line + 3;
	tmp = ft_strdup(line);
	if (!(l->EA = ft_strtrim(tmp, " ")))
	{
		free(tmp);
		perror("Error\n->EA");
		return (-1);
	}
	free(tmp);
	l->EA = ft_strdup(line);
	if ((fd = open(l->EA, O_RDONLY)) < 0)
	{
		ft_putstr_fd("Error\nWrong EA texture format", 1);
		return (-1);
	}
	close(fd);
	*flag = *flag + 1;
	return (1);
}

int		ft_parse_spritetex(char *line, t_legend *l, int *flag)
{
	int		fd;
	char 	*tmp;

	if (line[1] != ' ')
	{
		ft_putstr_fd("Error\nWrong sprite texture format", 1);
		return(-1);
	}
	line = line + 2;
	tmp = ft_strdup(line);
	if (!(l->spr = ft_strtrim(tmp, " ")))
	{
		free(tmp);
		perror("Error\n->spr");
		return (-1);
	}
	free(tmp);
	if ((fd = open(l->spr, O_RDONLY)) < 0)
	{
		ft_putstr_fd("Error\nWrong sprite texture format", 1);
		return (-1);
	}
	close(fd);
	*flag = *flag + 1;
	return (1);
}

int			ft_parse_fcol(char *line, t_legend *l, int *flag)
{
	char	**fcol;
	int		i;
	int 	col[5];

	i = 0;
	if (!(fcol = ft_split((line + 1), ' ')))
	{
		perror("Error\n->floor");
		return (-1);
	}
	while (fcol[i])
	{
		col[i] = ft_atoi(fcol[i]);
		if (col[i] < 0 || col[i] > 255 || i == 4)
		{
			ft_free_map(fcol);
			ft_putstr_fd("Error\nWrong floor colour format", 1);
			return (-1);
		}
		i++;
	}
	l->f_trgb = ft_create_trgb(col[0], col[1], col[2], col[3]);
	*flag = *flag + 1;
	return (1);
}

int			ft_parse_ccol(char *line, t_legend *l, int *flag)
{
	char	**ccol;
	int		i;
	int 	col[5];

	i = 0;
	if (!(ccol = ft_split((line + 1), ' ')))
	{
		perror("Error\n->ceiling");
		return (-1);
	}
	while (ccol[i])
	{
		col[i] = ft_atoi(ccol[i]);
		if (col[i] < 0 || col[i] > 255 || i == 4)
		{
			ft_free_map(ccol);
			ft_putstr_fd("Error\nWrong floor colour ceiling", 1);
			return (-1);
		}
		i++;
	}
	l->c_trgb = ft_create_trgb(col[0], col[1], col[2], col[3]);
	*flag = *flag + 1;
	return (1);
}
