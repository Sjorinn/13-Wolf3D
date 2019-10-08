/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchambon <pchambon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 14:24:34 by pchambon          #+#    #+#             */
/*   Updated: 2019/10/07 14:55:17 by pchambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

char	*open_fd(char *filename)
{
	int		fd;
	int		ret;
	char	*buff;
	char	*str;

	fd = open(filename, O_RDONLY);
	if (fd < 2)
		return (NULL);
	if (!(buff = ft_strnew(BUFF_SIZE)))
		return (NULL);
	if (!(str = ft_strnew(BUFF_SIZE)))
		return (NULL);
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		str = ft_strjoin_free(str, buff);
		if (!(buff = ft_strnew(BUFF_SIZE)))
			return (NULL);
	}
	ft_strdel(&buff);
	close(fd);
	return (str);
}

/*
** la fonction print_data affiche la carte sur le terminal.
*/

void	print_data(int **data)
{
	t_case		i;

	i.x = 0;
	i.y = 0;
	ft_putendl("##################################################");
	while (i.y < 24)
	{
		ft_putchar('#');
		while (i.x < 24)
		{
			if (data[i.y][i.x] > 0)
				ft_putstr("##");
			if (data[i.y][i.x] == 0)
				ft_putstr("  ");
			i.x++;
		}
		ft_putendl("#");
		i.y++;
		i.x = 0;
	}
	ft_putendl("##################################################");
}

int		error(int ret)
{
	if (ret == 0)
		perror("Wolf3d usage : ./wolf3d <map filename>.");
	if (ret == 1)
		perror("Wolf3d error");
	if (ret == 2)
		perror("Wolf3d error : File not a Wolf3d map.");
	if (ret == 3)
	{
		perror("Wolf3d error : Failed to load textures ");
		exit(0);
	}
	return (0);
}

int		main(int ac, char **av)
{
	char	*file;

	if (ac > 2 || ac < 2)
		return (error(0));
	if (!(file = open_fd(av[1])))
		return (error(1));
	if (!check_file(file))
		return (error(2));
	open_win(file);
	ft_strdel(&file);
	return (0);
}
