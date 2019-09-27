/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchambon <pchambon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 09:34:57 by pchambon          #+#    #+#             */
/*   Updated: 2019/09/27 13:18:54 by pchambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		int_free(void *obj)
{
	free(obj);
	return (0);
}