/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchambon <pchambon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 10:48:23 by pchambon          #+#    #+#             */
/*   Updated: 2019/09/27 15:41:35 by pchambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

int		free_all(t_param *p)
{
	int	i;

	i = 0;
	mlx_destroy_image(p->mlx, p->img->ptr);
	mlx_destroy_window(p->mlx, p->win);
	while (i <= 24)
	{
		ft_memdel((void**)&p->data[i]);
		i++;
	}
	ft_memdel((void**)&p->data);
	exit(0);
}

int		key_func_press(int keycode, t_param *p)
{
	if (keycode == 53 || keycode == 12)
		free_all(p);
	if (keycode == 126)
		p->key->up = 1;
	if (keycode == 125)
		p->key->down = 1;
	if (keycode == 124)
		p->key->right = 1;
	if (keycode == 123)
		p->key->left = 1;
	movement(p);
	return (0);
}

int		key_func_release(int keycode, t_param *p)
{
	if (keycode == 126)
		p->key->up = 0;
	if (keycode == 125)
		p->key->down = 0;
	if (keycode == 124)
		p->key->right = 0;
	if (keycode == 123)
		p->key->left = 0;
	movement(p);
	return (0);
}

int		open_win(char *file)
{
	t_param	p;
	t_key	key;
	t_image img;
	t_cam	cam;
	t_image tex[9];

	p.i = -1;
	p.key = &key;
	p.cam = &cam;
	while (p.i++ < 6)
		p.tex[p.i] = &tex[p.i];
	if (!(p.data = parser(file, p.cam)))
		return (1);
	p.img = &img;
	p.mlx = mlx_init();
	p.win = mlx_new_window(p.mlx, X_MAX, Y_MAX + 100, "Wolf3d");
	init_img(p.img, p.mlx);
	init_key(p.key);
	init_cam(p.cam);
	if (init_tex(tex, p.mlx) == 0)
		error(3);
	raycaster(p.data, p.cam, &p);
	print_data(p.data);
	window(&p);
	return (0);
}

int		window(t_param *p)
{
	mlx_put_image_to_window(p->mlx, p->win, p->tex[5]->ptr, 0, Y_MAX);
	mlx_put_image_to_window(p->mlx, p->win, p->img->ptr, 0, 0);
	mlx_do_key_autorepeatoff(p->mlx);
	mlx_hook(p->win, 2, 0, key_func_press, p);
	mlx_hook(p->win, 3, 0, key_func_release, p);
	mlx_hook(p->win, 17, 0, free_all, p);
	mlx_loop_hook(p->mlx, movement, p);
	mlx_loop(p->mlx);
	return (0);
}
