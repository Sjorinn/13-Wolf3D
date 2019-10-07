/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchambon <pchambon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 15:08:35 by pchambon          #+#    #+#             */
/*   Updated: 2019/10/07 14:28:51 by pchambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

int		init_tex_2(t_image tex[6], void *mlx)
{
	if (!(tex[3].ptr = mlx_xpm_file_to_image(mlx,
		"/Users/pchambon/Desktop/42/13-Wolf3D/textures/stone.xpm",
		&tex[3].len.x, &tex[3].len.y)))
		return (0);
	if (!(tex[3].addr =
	mlx_get_data_addr(tex[3].ptr, &tex[3].bpp, &tex[3].sline, &tex[3].end)))
		return (0);
	if (!(tex[4].ptr = mlx_xpm_file_to_image(mlx,
		"/Users/pchambon/Desktop/42/13-Wolf3D/textures/wood.xpm",
		&tex[4].len.x, &tex[4].len.y)))
		return (0);
	if (!(tex[4].addr =
	mlx_get_data_addr(tex[4].ptr, &tex[4].bpp, &tex[4].sline, &tex[4].end)))
		return (0);
	if (!(tex[5].ptr = mlx_xpm_file_to_image(mlx,
		"/Users/pchambon/Desktop/42/13-Wolf3D/textures/menu.xpm",
		&tex[5].len.x, &tex[5].len.y)))
		return (0);
	if (!(tex[5].addr =
	mlx_get_data_addr(tex[5].ptr, &tex[5].bpp, &tex[5].sline, &tex[5].end)))
		return (0);
	return (1);
}

int		init_tex(t_image tex[6], void *mlx)
{
	if (!(tex[0].ptr = mlx_xpm_file_to_image(mlx,
		"/Users/pchambon/Desktop/42/13-Wolf3D/textures/brick.xpm",
		&tex[0].len.x, &tex[0].len.y)))
		return (0);
	if (!(tex[0].addr =
	mlx_get_data_addr(tex[0].ptr, &tex[0].bpp, &tex[0].sline, &tex[0].end)))
		return (0);
	if (!(tex[1].ptr = mlx_xpm_file_to_image(mlx,
		"/Users/pchambon/Desktop/42/13-Wolf3D/textures/grass.xpm",
		&tex[1].len.x, &tex[1].len.y)))
		return (0);
	if (!(tex[1].addr =
	mlx_get_data_addr(tex[1].ptr, &tex[1].bpp, &tex[1].sline, &tex[1].end)))
		return (0);
	if (!(tex[2].ptr = mlx_xpm_file_to_image(mlx,
		"/Users/pchambon/Desktop/42/13-Wolf3D/textures/metal.xpm",
		&tex[2].len.x, &tex[2].len.y)))
		return (0);
	if (!(tex[2].addr =
	mlx_get_data_addr(tex[2].ptr, &tex[2].bpp, &tex[2].sline, &tex[2].end)))
		return (0);
	return (init_tex_2(tex, mlx));
}
