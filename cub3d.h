/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rosanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 15:43:33 by rosanche          #+#    #+#             */
/*   Updated: 2020/02/10 16:00:28 by rosanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H

# include "mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <ctype.h>
# include <stdarg.h>
# include "libft/libft.h"
# include <stdbool.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>

typedef struct	s_move
{
	bool		front;
	bool		back;
	bool		right;
	bool		left;
	bool		r_left;
	bool		r_right;
	bool		esc;
}				t_move;

typedef struct	s_gril
{
	char		**sm;
	int			map_width;
	int			map_height;
}				t_gril;

typedef struct	s_image
{
	void		*ptr;
	char		*str;
	int			height;
	int			width;
	int			bpp;
	int			endian;
	int			s_line;
	int			tex_x;
	int			tex_y;
}				t_image;

typedef struct	s_sprite
{
	double		x;
	double		y;
	double		distance;
	int			texture;
	double		spritex;
	double		spritey;
	double		invdet;
	double		transformx;
	double		transformy;
	int			spritescreenx;
	int			spritewidth;
	int			spriteheight;
	int			drawstarty;
	int			drawendy;
	int			drawstartx;
	int			drawendx;
}				t_sprite;

typedef struct	s_file
{
	char		*line;
	char		*path[5];
}				t_file;

typedef struct	s_cub
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*ptr_img;
	char		*img;
	int			l_size;
	int			w_w;
	int			w_h;

	int			x;
	int			y;

	double		p_x;
	double		p_y;
	char		p_v;

	double		d_x;
	double		d_y;
	double		plane_x;
	double		plane_y;

	double		side_s;
	double		rdir_x;
	double		rdir_y;

	int			rp_x;
	int			rp_y;
	double		d_sidex;
	double		d_sidey;
	double		d_deltax;
	double		d_deltay;
	double		d_wall;
	int			nx;
	int			ny;
	int			hit;
	int			side_hit;

	int			line_height;
	int			dw_start;
	int			dw_end;
	double		step;
	int			bt;
	int			e;

	t_gril		*tab;
	t_move		move;
	t_file		file;
	t_sprite	*s;
	int			nb_sprite;
	double		*dt_sprite;
	int			*or_sprite;

	t_image		text[5];
	double		texpos;
	int			w_side;
	int			floor[4];
	int			ceil[4];
	bool		save;
}				t_cub;

t_cub			*init_cub(t_cub *cub);
t_gril			*init_s();

int				height_n_fill(int fd, t_cub *cub, char *line);
int				width(t_gril *grill, t_cub *cub);
int				raycast(t_cub *cub);
int				load_texture(t_cub *cub);
int				wall_hit(t_cub *cub);
int				check_file(int fd, t_cub *cub);
void			draw_text(t_cub *cub, int y, int x, double step);
int				error(char *str, t_cub *cub);
int				release_key(int key, void *param);
int				press_key(int key, void *param);
int				deal_key(t_cub *cub);
void			draw_sprite(t_cub *cub, int y, int x);
int				display_sprite(t_cub *cub, double *zbuffer);
void			sort_sprite(t_cub *cub);
void			destroy(t_cub *cub);
void			p_orient(t_cub *cub);
int				stop(t_cub *cub);
int				ft_strlen_tab(char **str);
int				create_bmp(t_cub *cub);
int				start_game(t_cub *cub, int fd);
int				create_screenshot(t_cub *cub, int fd);
int				check_map(t_cub *cub);
int				save_game(t_cub *cub, int fd);
int				guess_wnh(t_cub *cub, int i);
int				guess_color(t_cub *cub, int i, int *floor);

#endif
