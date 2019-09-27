/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchambon <pchambon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 12:20:08 by pchambon          #+#    #+#             */
/*   Updated: 2019/09/27 15:41:35 by pchambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	clear_image(t_image *img)
{
	t_case i;

	i.x = 0;
	i.y = 0;
	while (i.x < X_MAX)
	{
		while (i.y < Y_MAX)
		{
			put_pxl(img, i.x, i.y, 0);
			i.y++;
		}
		i.y = 0;
		i.x++;
	}
}

int		put_pxl_tex(t_image *img, t_image *tex, t_case b, int ori)
{
	int		i;
	int		j;

	if (b.x > X_MAX || b.y > Y_MAX || b.x < 0 || b.y < 0)
		return (1);
	i = b.x * (img->bpp / 8) + b.y * img->sline;
	j = tex->pxl.x * (tex->bpp / 8) + tex->pxl.y * tex->sline;
	img->addr[i] = (ori == 1) ? tex->addr[j] :
		tex->addr[j] >> 1 & 8355711;
	img->addr[i + 1] = (ori == 1) ? tex->addr[j + 1] :
		tex->addr[j + 1] >> 1 & 8355711;
	img->addr[i + 2] = (ori == 1) ? tex->addr[j + 2] :
		tex->addr[j + 2] >> 1 & 8355711;
	return (0);
}

void	get_tex_x(t_image *tex, t_cam *cam)
{
	cam->wallx = (cam->ori == 0) ? cam->usr.y + cam->wall * cam->ray.y :
		cam->usr.x + cam->wall * cam->ray.x;
	cam->wallx -= floor(cam->wallx);
	tex->pxl.x = (int)(cam->wallx * (double)tex->len.x);
	tex->pxl.x = (cam->ori == 0 && cam->ray.x > 0) ?
		tex->len.x - tex->pxl.x - 1 : tex->pxl.x;
	tex->pxl.x = (cam->ori == 1 && cam->ray.y < 0) ?
		tex->len.x - tex->pxl.x - 1 : tex->pxl.x;
	tex->pxl.y = 0;
}
