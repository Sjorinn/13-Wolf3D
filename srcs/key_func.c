/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchambon <pchambon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 16:42:46 by pchambon          #+#    #+#             */
/*   Updated: 2019/09/27 15:41:35 by pchambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	forw(t_cam *cam, t_param *p)
{
	if (p->data[(int)(cam->usr.x + cam->vec.x)][(int)cam->usr.y] == 0)
		cam->usr.x += cam->vec.x * 0.2;
	if (p->data[(int)cam->usr.x][(int)(cam->usr.y + cam->vec.y)] == 0)
		cam->usr.y += cam->vec.y * 0.2;
}

void	back(t_cam *cam, t_param *p)
{
	if (p->data[(int)(cam->usr.x - cam->vec.x)][(int)cam->usr.y] == 0)
		cam->usr.x -= cam->vec.x * 0.2;
	if (p->data[(int)cam->usr.x][(int)(cam->usr.y - cam->vec.y)] == 0)
		cam->usr.y -= cam->vec.y * 0.2;
}

void	rot_right(t_cam *cam)
{
	double tmp;

	tmp = cam->vec.x;
	cam->vec.x = cam->vec.x * cos(-ROT_SPEED)
		- cam->vec.y * sin(-ROT_SPEED);
	cam->vec.y = tmp * sin(-ROT_SPEED)
		+ cam->vec.y * cos(-ROT_SPEED);
	tmp = cam->pln.x;
	cam->pln.x = cam->pln.x * cos(-ROT_SPEED)
		- cam->pln.y * sin(-ROT_SPEED);
	cam->pln.y = tmp * sin(-ROT_SPEED)
		+ cam->pln.y * cos(-ROT_SPEED);
}

void	rot_left(t_cam *cam)
{
	double tmp;

	tmp = cam->vec.x;
	cam->vec.x = cam->vec.x * cos(ROT_SPEED)
		- cam->vec.y * sin(ROT_SPEED);
	cam->vec.y = tmp * sin(ROT_SPEED)
		+ cam->vec.y * cos(ROT_SPEED);
	tmp = cam->pln.x;
	cam->pln.x = cam->pln.x * cos(ROT_SPEED)
		- cam->pln.y * sin(ROT_SPEED);
	cam->pln.y = tmp * sin(ROT_SPEED)
		+ cam->pln.y * cos(ROT_SPEED);
}

int		movement(t_param *p)
{
	if (p->key->up == 1)
		forw(p->cam, p);
	if (p->key->down == 1)
		back(p->cam, p);
	if (p->key->right == 1)
		rot_right(p->cam);
	if (p->key->left == 1)
		rot_left(p->cam);
	clear_image(p->img);
	raycaster(p->data, p->cam, p);
	mlx_put_image_to_window(p->mlx, p->win, p->img->ptr, 0, 0);
	return (0);
}
