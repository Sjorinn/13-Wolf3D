/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchambon <pchambon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 14:25:49 by pchambon          #+#    #+#             */
/*   Updated: 2019/10/08 15:44:47 by pchambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "mlx.h"
# include "../X-Libft/includes/libft.h"
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>

# define BUFF_SIZE 4086
# define X_MAX 1080
# define Y_MAX 720
# define ROT_SPEED 0.12

typedef	struct	s_point
{
	double		x;
	double		y;
}				t_point;

typedef struct	s_case
{
	int			x;
	int			y;
}				t_case;

typedef struct	s_cam
{
	t_point		usr;
	t_case		map;
	t_point		vec;
	t_point		pln;
	double		x;
	t_point		ray;
	t_point		side;
	t_point		delt;
	double		wall;
	t_case		step;
	int			hit;
	int			ori;
	int			h;
	int			num;
	t_case		draw;
	double		wallx;
}				t_cam;

typedef struct	s_floor
{
	t_point		f_wall;
	t_point		dist;
	t_point		f_curr;
	t_case		f;
	t_case		s;
}				t_floor;

typedef struct	s_image
{
	void		*ptr;
	char		*addr;
	int			bpp;
	int			sline;
	int			end;
	t_case		len;
	t_case		pxl;
}				t_image;

typedef struct	s_key
{
	int		up;
	int		down;
	int		right;
	int		left;
}				t_key;

typedef	struct	s_param
{
	void		*mlx;
	void		*win;
	t_image		*img;
	int			**data;
	t_cam		*cam;
	t_image		*tex[9];
	t_key		*key;
	int			i;

}				t_param;

/*
**	main.c
*/

char			*open_fd(char *filename);
void			print_data(int **data);
void			fail_text(t_param *p);
int				error(int ret);

/*
**	init.c
*/

void			init_cam(t_cam *cam);
void			init_key(t_key *key);
void			init_img(t_image *img, void *mlx);

/*
**	init_tex.c
*/

int				init_tex_2(t_image tex[9], void *mlx);
int				init_tex(t_image tex[9], void *mlx);

/*
**	parser.c
*/

int				parser2(char *file, int **tab, t_case *t, int *i);
int				**parser(char *file, t_cam *cam);
int				check_file2(char *file, int *i, int *flag, t_case *max);
int				check_file(char *file);

/*
**	window.c
*/

int				free_all(t_param *p);
int				key_func(int keycode, t_param *p);
int				open_win(char *file);
int				window(t_param *p);

/*
**	raycaster.c
*/

int				put_pxl(t_image *img, int x, int y, unsigned int c);
void			draw_line(int i, t_param *p, t_case a, int x);
int				hit(int **data, t_cam *cam);
void			wall(int i, t_cam *cam, t_param *p);
int				raycaster(int **data, t_cam *cam, t_param *p);

/*
**	key_func.c
*/

void			forw(t_cam *cam, t_param *p);
void			back(t_cam *cam, t_param *p);
void			rot_right(t_cam *cam);
void			rot_left(t_cam *cam);
int				movement(t_param *p);

/*
**	texture.c
*/

void			clear_image(t_image *img);
int				put_pxl_tex(t_image *img, t_image *tex, t_case b, int ori);
void			get_tex_x(t_image *tex, t_cam *cam);

/*
**	floor.c
*/

int				draw_floor(int i, t_cam *cam, t_image *tex, t_param *p);
void			calc_tex_pxl(t_floor l, t_image *tex, t_cam *cam);
t_point			get_floor_wall(t_cam *cam);

#endif
