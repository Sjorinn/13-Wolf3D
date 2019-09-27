/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchambon <pchambon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 15:10:20 by pchambon          #+#    #+#             */
/*   Updated: 2019/09/27 15:41:35 by pchambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

t_point	get_floor_wall(t_cam *cam)
{
	t_point	f_wall;

	f_wall.x = 0;
	f_wall.y = 0;
	if (cam->ori == 0 && cam->ray.x > 0)
	{
		f_wall.x = cam->map.x;
		f_wall.y = cam->map.y + cam->wallx;
	}
	else if (cam->ori == 0 && cam->ray.x < 0)
	{
		f_wall.x = cam->map.x + 1;
		f_wall.y = cam->map.y + cam->wallx;
	}
	else if (cam->ori == 1 && cam->ray.y > 0)
	{
		f_wall.x = cam->map.x + cam->wallx;
		f_wall.y = cam->map.y;
	}
	else if (cam->ori == 1 && cam->ray.y < 0)
	{
		f_wall.x = cam->map.x + cam->wallx;
		f_wall.y = cam->map.y + 1;
	}
	return (f_wall);
}

void	calc_tex_pxl(t_floor l, t_image *tex, t_cam *cam)
{
	l.f_curr.x = (l.dist.y / l.dist.x) * (l.f_wall.x - cam->usr.x) + cam->usr.x;
	l.f_curr.y = (l.dist.y / l.dist.x) * (l.f_wall.y - cam->usr.y) + cam->usr.y;
	tex->pxl.x = (int)(l.f_curr.x * tex->len.x) % tex->len.x;
	tex->pxl.y = (int)(l.f_curr.y * tex->len.y) % tex->len.y;
}

int		draw_floor(int x, t_cam *cam, t_image *tex, t_param *p)
{
	t_floor	l;

	l.dist.x = cam->wall;
	l.f.x = x;
	l.s.x = x;
	l.f_wall = get_floor_wall(cam);
	if (cam->draw.y < 0)
		cam->draw.y = Y_MAX;
	l.f.y = cam->draw.y + 1;
	while (l.f.y < Y_MAX)
	{
		l.s.y = Y_MAX - l.f.y;
		l.dist.y = Y_MAX / (2.0 * l.f.y - Y_MAX);
		calc_tex_pxl(l, tex, cam);
		put_pxl_tex(p->img, tex, l.f, 0);
		put_pxl_tex(p->img, tex, l.s, 0);
		l.f.y++;
	}
	return (0);
}
