/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mualkhid <mualkhid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 08:18:01 by mualkhid          #+#    #+#             */
/*   Updated: 2024/02/22 20:03:26 by mualkhid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	o;

	o = 0;
	while (o < n)
	{
		if ((*(unsigned char *)(s + o)) == (unsigned char)c)
			return ((void *)(s + o));
		o++;
	}
	return (NULL);
}
