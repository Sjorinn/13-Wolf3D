/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchambon <pchambon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 16:02:48 by pchambon          #+#    #+#             */
/*   Updated: 2019/09/27 15:41:35 by pchambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	init_cam(t_cam *cam)
{
	cam->vec.x = -1;
	cam->vec.y = 0;
	cam->pln.x = 0;
	cam->pln.y = 0.66;
}

void	init_key(t_key *key)
{
	key->up = 0;
	key->down = 0;
	key->right = 0;
	key->left = 0;
}

void	init_img(t_image *img, void *mlx)
{
	img->ptr = mlx_new_image(mlx, X_MAX, Y_MAX);
	img->addr = mlx_get_data_addr(img->ptr, &img->bpp, &img->sline, &img->end);
}
