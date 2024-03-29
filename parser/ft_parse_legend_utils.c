/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_legend_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarthus <dkarthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 12:01:02 by dkarthus          #+#    #+#             */
/*   Updated: 2021/03/19 01:11:15 by dkarthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_free_leg(t_legend *l)
{
	if (l->no)
		free(l->no);
	if (l->so)
		free(l->so);
	if (l->we)
		free(l->we);
	if (l->ea)
		free(l->ea);
	if (l->spr)
		free(l->spr);
	if (l->lvl)
		ft_free_map(l->lvl);
}

void	ft_free_map(char **map)
{
	int i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map[i]);
	free(map);
}

int		ft_parse_res(char *line, t_legend *l, int *flag)
{
	char **res;

	if (!(res = ft_split(&line[1], ' ')))
	{
		perror("Error\n->R");
		return (-1);
	}
	if (!res[0] || !res[1])
	{
		ft_putstr_fd("Error\nWrong resolution format", 1);
		ft_free_map(res);
		return (-1);
	}
	l->res_x = ft_atoi((const char *)res[0]);
	l->res_y = ft_atoi((const char *)res[1]);
	if (l->res_y <= 0 || l->res_x <= 0 || res[2])
	{
		ft_putstr_fd("Error\nWrong resolution format", 1);
		ft_free_map(res);
		return (-1);
	}
	*flag = *flag + 1;
	ft_free_map(res);
	return (1);
}

int		ft_parse_ntexture(char *line, t_legend *l, int *flag)
{
	int		fd;

	if (line[1] != 'O' || line[2] != ' ')
	{
		ft_putstr_fd("Error\nWrong NO texture format", 1);
		return (-1);
	}
	line = line + 3;
	if (!(l->no = ft_strdup(line)))
	{
		perror("Error\n->NO");
		return (-1);
	}
	if ((fd = open(l->no, O_RDONLY)) < 0)
	{
		ft_putstr_fd("Error\nWrong NO texture format", 1);
		return (-1);
	}
	close(fd);
	*flag = *flag + 1;
	return (1);
}

int		ft_parse_stexture(char *line, t_legend *l, int *flag)
{
	int		fd;

	if (line[2] != ' ')
	{
		ft_putstr_fd("Error\nWrong SO texture format", 1);
		return (-1);
	}
	if (!(l->so = ft_strdup((line + 3))))
	{
		perror("Error\n->SO");
		return (-1);
	}
	if ((fd = open(l->so, O_RDONLY)) < 0)
	{
		ft_putstr_fd("Error\nWrong SO texture format", 1);
		return (-1);
	}
	close(fd);
	*flag = *flag + 1;
	return (1);
}
