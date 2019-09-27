/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchambon <pchambon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 15:57:57 by pchambon          #+#    #+#             */
/*   Updated: 2019/09/27 15:41:35 by pchambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

int		check_file2(char *file, int *i, int *flag, t_case *max)
{
	if (file[*i] != '\n' && file[*i] != ' ' && file[*i] != '\0' &&
		!ft_isdigit(file[*i]) && file[*i] != 'x')
		return (0);
	if (file[*i] == '\n')
	{
		if (max->x < 24)
			return (0);
		max->y += 1;
		max->x = 0;
	}
	if (ft_isdigit(file[*i]))
	{
		if (file[*i] - '0' > 7)
			return (0);
		max->x += 1;
	}
	if (file[*i] == 'x')
	{
		*flag += 1;
		max->x += 1;
	}
	if (max->x > 24)
		return (0);
	return (1);
}

int		check_file(char *file)
{
	int		i;
	int		flag;
	t_case	max;

	i = 0;
	max.x = 0;
	max.y = 0;
	flag = 0;
	while (file[i] != '\0')
	{
		if (!(check_file2(file, &i, &flag, &max)))
			return (0);
		i++;
	}
	if (max.y != 24 || flag == 0 || flag > 1)
		return (0);
	return (1);
}

int		parser2(char *file, int **tab, t_case *t, int *i)
{
	if (file[*i] == '\n')
	{
		t->y += 1;
		t->x = 0;
		if (!(tab[t->y] = (int*)malloc(sizeof(int) * 25)))
			return (0);
	}
	if (ft_isdigit(file[*i]))
	{
		tab[t->y][t->x] = file[*i] - '0';
		t->x += 1;
	}
	return (1);
}

int		**parser(char *file, t_cam *cam)
{
	int		**tab;
	t_case	t;
	int		i;

	t.x = 0;
	t.y = 0;
	i = 0;
	if (!(tab = (int**)malloc(sizeof(int*) * 25)))
		return (NULL);
	if (!(tab[t.y] = (int*)malloc(sizeof(int) * 25)))
		return (NULL);
	while (file[i] != '\0')
	{
		if (!(parser2(file, tab, &t, &i)))
			return (NULL);
		if (file[i] == 'x')
		{
			tab[t.y][t.x] = 0;
			cam->usr.x = (double)t.x + 0.5;
			cam->usr.y = (double)t.y + 0.5;
			t.x += 1;
		}
		i++;
	}
	return (tab);
}
