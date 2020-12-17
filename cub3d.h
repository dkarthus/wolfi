/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarthus <dkarthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 15:03:47 by dkarthus          #+#    #+#             */
/*   Updated: 2020/12/17 16:24:47 by dkarthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./inc/libft.h"
# include "./inc/mlx.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# define SCALE 1

typedef struct	s_legend
{
	int		res_y;
	int		res_x;
	int 	f_trgb;
	int 	c_trgb;
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	char 	*spr;
	char	**lvl;
}				t_legend;

typedef struct	s_txtr
{
	void *NO;
	int wNO;
	int hNO;
	void *SO;
	int wSO;
	int hSO;
	void *WE;
	int wWE;
	int hWE;
	void *EA;
	int wEA;
	int hEA;
	void *SPR;
	int wSPR;
	int hSPR;
}				t_txtr;

typedef struct	s_obj
{
	double x;
	double y;
	double dir;
	double fov_st;
	double fov_end;
}				t_obj;

typedef struct	s_vars
{
	void		*mlx;
	void		*win;
	void		*img;
	void		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	t_legend	*l;
	t_obj		*pov;
	t_txtr 		*tx;
}				t_vars;

int			ft_create_trgb(int t, int r, int g, int b);
int			ft_get_t(int trgb);
int			ft_get_r(int trgb);
int			ft_get_g(int trgb);
int			ft_get_b(int trgb);

char		**ft_parse(char *file);
int			ft_parse_legend(char **map, t_legend *l);
int			ft_parse_lvl(char **map, t_legend *l, int *flag);
int			ft_parse_res(char *line, t_legend *l, int *flag);
int			ft_parse_stexture(char *line, t_legend *l, int *flag);
int			ft_parse_ntexture(char *line, t_legend *l, int *flag);
int			ft_parse_wtexture(char *line, t_legend *l, int *flag);
int			ft_parse_etexture(char *line, t_legend *l, int *flag);
int			ft_parse_spritetex(char *line, t_legend *l, int *flag);
int			ft_parse_ccol(char *line, t_legend *l, int *flag);
int			ft_parse_fcol(char *line, t_legend *l, int *flag);
void		ft_free_leg(t_legend *l);
void		ft_free_map(char **map);
t_legend	*ft_leg_init();


int		ft_draw_map(t_vars *inst);
int		ft_draw_rays(t_vars *inst);
//t_obj	*ft_player_init(char **map);
void	ft_pixel_put_image(t_vars *inst, int x, int y, int col);

#endif