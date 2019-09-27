/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchambon <pchambon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 10:46:14 by pchambon          #+#    #+#             */
/*   Updated: 2019/09/27 15:41:35 by pchambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

int		put_pxl(t_image *img, int x, int y, unsigned int c)
{
	int		i;

	if (x > X_MAX || y > Y_MAX || x < 0 || y < 0)
		return (1);
	i = x * (img->bpp / 8) + y * img->sline;
	img->addr[i] = c;
	img->addr[i + 1] = c >> 8;
	img->addr[i + 2] = c >> 16;
	img->addr[i + 3] = c >> 24;
	return (0);
}

void	draw_line(int x, t_param *p, t_case a, int i)
{
	t_case	b;

	b.x = x;
	b.y = 0;
	i--;
	get_tex_x(p->tex[i], p->cam);
	while (b.y < a.y)
	{
		if (a.x > 0)
			p->tex[i]->pxl.y = ((b.y - a.x) * p->tex[i]->len.y) / (a.y - a.x);
		else
			p->tex[i]->pxl.y =
				((b.y - ((Y_MAX - a.y) / 2)) * p->tex[i]->len.y) / a.y;
		put_pxl_tex(p->img, p->tex[i], b, p->cam->ori);
		b.y++;
	}
}

int		hit(int **data, t_cam *cam)
{
	int		hit;

	hit = 0;
	while (hit == 0)
	{
		if (cam->side.x < cam->side.y)
		{
			cam->side.x += cam->delt.x;
			cam->map.x += cam->step.x;
			cam->ori = 0;
		}
		else
		{
			cam->side.y += cam->delt.y;
			cam->map.y += cam->step.y;
			cam->ori = 1;
		}
		cam->num = data[cam->map.x][cam->map.y];
		if (cam->num > 0)
			hit = 1;
	}
	return (hit);
}

void	wall(int i, t_cam *cam, t_param *p)
{
	cam->wall = (cam->ori == 0) ? (cam->map.x - cam->usr.x +
		(1 - cam->step.x) / 2) / cam->ray.x : (cam->map.y - cam->usr.y +
		(1 - cam->step.y) / 2) / cam->ray.y;
	cam->h = (int)((double)Y_MAX / cam->wall);
	cam->draw.x = ((Y_MAX - cam->h) / 2 > 0) ?
		(Y_MAX - cam->h) / 2 : 0;
	cam->draw.y = ((Y_MAX + cam->h) / 2 <= Y_MAX) ?
		(Y_MAX + cam->h) / 2 : cam->h - 1;
	if (cam->num == 7)
	{
		if (cam->usr.y > cam->map.y && cam->ori == 1)
			cam->num = 1;
		if (cam->usr.y < cam->map.y && cam->ori == 1)
			cam->num = 2;
		if (cam->usr.x < cam->map.x && cam->ori == 0)
			cam->num = 3;
		if (cam->usr.x > cam->map.x && cam->ori == 0)
			cam->num = 4;
	}
	draw_line(i, p, cam->draw, cam->num);
	draw_floor(i, cam, p->tex[4], p);
}

int		raycaster(int **data, t_cam *cam, t_param *p)
{
	int		i;

	i = 0;
	while (i < X_MAX)
	{
		cam->x = (2 * i / (double)X_MAX) - 1;
		cam->ray.x = cam->vec.x + cam->pln.x * cam->x;
		cam->ray.y = cam->vec.y + cam->pln.y * cam->x;
		cam->delt.x = fabs(1 / cam->ray.x);
		cam->delt.y = fabs(1 / cam->ray.y);
		cam->map.x = (int)cam->usr.x;
		cam->map.y = (int)cam->usr.y;
		cam->step.x = (cam->ray.x < 0) ? -1 : 1;
		cam->side.x = (cam->ray.x < 0) ?
			(cam->usr.x - cam->map.x) * cam->delt.x :
			(cam->map.x + 1 - cam->usr.x) * cam->delt.x;
		cam->step.y = (cam->ray.y < 0) ? -1 : 1;
		cam->side.y = (cam->ray.y < 0) ?
			(cam->usr.y - cam->map.y) * cam->delt.y :
			(cam->map.y + 1 - cam->usr.y) * cam->delt.y;
		if ((cam->hit = hit(data, cam)))
			wall(i, cam, p);
		i++;
	}
	return (0);
}

/*
**		cam->x	Coordonée en x par rapport à la caméra
**		cam->ray.x X du vecteur
**		cam->ray.y Y du vecteur
**		cam->delt.x Distance entre le mur actuel et le prochain en X
**		cam->delt.y Distance entre le mur actuel et le prochain en Y
**		cam->map.x Case où se trouve le rayon
**		cam->map.y Case où se trouve le rayon
**		cam->step.x Direction pour l'avancée du rayon  en X
**		cam->side.x Taille du rayon entre sa position et le prochain mur en X
**		cam->step.y Direction pour l'avancée du rayon  en Y
**		cam->side.y Taille du rayon entre sa position et le prochain mur en Y
**		cam->hit Flag qui s'active quand un mur est touché
**		cam->ori Le mur est il Nord/Sud ou Est/Ouest
**		cam->wall Où le mur a t'il été touché;
**		cam->h Hauteur du mur;
**		cam->draw.x Coordonnée Y de la base du mur
**		cam->draw.y Coordonnée Y du haut du mur
**		cam->num quel type de mur a été touché;
*/
