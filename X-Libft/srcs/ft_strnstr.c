/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchambon <pchambon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 11:09:32 by pchambon          #+#    #+#             */
/*   Updated: 2019/09/27 13:19:31 by pchambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strnstr(const char *haystack, const char *ne, size_t n)
{
	size_t	i;
	char	*str;

	if (*ne == '\0')
		return ((char *)haystack);
	i = ft_strlen(ne);
	str = (char *)haystack;
	while (*str && n-- >= i)
	{
		if (ft_memcmp(str, ne, i) == 0)
			return (str);
		str++;
	}
	return (NULL);
}
