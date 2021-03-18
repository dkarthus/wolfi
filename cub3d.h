/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarthus <dkarthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 15:03:47 by dkarthus          #+#    #+#             */
/*   Updated: 2021/03/19 01:13:14 by dkarthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <mlx.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

typedef struct	s_legend
{
	int			res_y;
	int			res_x;
	int			f_trgb;
	int			c_trgb;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*spr;
	char		**lvl;
}				t_legend;

typedef struct	s_txt
{
	void		*img;
	void		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	int			x;
	int			y;
}				t_txt;

typedef struct	s_obj
{
	float		x;
	float		y;
	float		dir;
	float		fov_st;
	float		txt_xof;
	float		txt_yof;
	t_txt		*tx_drw;
}				t_obj;

typedef struct	s_sprites
{
	float				dst;
	int					x;
	int					y;
	int					xpx_st;
	int					xpx_end;
	float				ang;
	struct s_sprites	*next;
}				t_sprites;

typedef struct	s_vars
{
	void		*mlx;
	void		*win;
	void		*img;
	void		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	int			mode;
	t_legend	l;
	t_obj		pov;
	t_txt		no;
	t_txt		so;
	t_txt		we;
	t_txt		ea;
	t_txt		spr;
	t_sprites	*spr_dst;
	float		*dsts;
}				t_vars;

int				ft_create_trgb(int t, int r, int g, int b);

char			**ft_parse(char *file);
int				ft_parse_legend(char **map, t_legend *l);
int				ft_parse_lvl(char **map, t_legend *l, int *flag);
int				ft_parse_res(char *line, t_legend *l, int *flag);
int				ft_parse_stexture(char *line, t_legend *l, int *flag);
int				ft_parse_ntexture(char *line, t_legend *l, int *flag);
int				ft_parse_wtexture(char *line, t_legend *l, int *flag);
int				ft_parse_etexture(char *line, t_legend *l, int *flag);
int				ft_parse_spritetex(char *line, t_legend *l, int *flag);
int				ft_parse_ccol(char *line, t_legend *l, int *flag);
int				ft_parse_fcol(char *line, t_legend *l, int *flag);

void			ft_free_leg(t_legend *l);
void			ft_free_map(char **map);
int				full_exit(t_vars *inst);
void			ft_player_init(t_vars *inst);
void			ft_main_inst_init(t_vars *inst);

int				ft_spr_sort(t_vars *inst, int y, int x, t_obj *ray);
t_sprites		*ft_new_spr(t_vars *inst, int y, int x, t_obj *ray);
int				ft_ch_duplicate(t_vars *inst, int y, int x, t_obj *ray);
t_sprites		*ft_spr_insert(t_vars *inst, t_sprites *new);
void			ft_draw_sprites(t_vars *inst);
void			ft_draw_ceil_floor(t_vars *inst);
void			ft_draw_walls(t_vars *inst, t_obj *ray, float dst, int x);
void			ft_clear_spr_list(t_vars *inst);
int				key_hook(int keycode, t_vars *inst);

int				ft_render_img(t_vars *inst);
void			ft_render_walls(t_vars *inst);
void			ft_render_bmp(t_vars *inst);

float			ft_dst_sort(float dst_y, float dst_x, t_obj *ray, t_vars *inst);
int				ft_is_hit(t_vars *inst, int y, int x, t_obj *ray);
void			ft_get_txtr(t_vars *inst);
void			ft_pixel_put_image(t_vars *inst, int x, int y,
					unsigned int col);
unsigned int	ft_get_pixel_col(t_txt *txt, int x, int y);

#endif
