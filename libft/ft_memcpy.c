/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mualkhid <mualkhid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 08:18:15 by mualkhid          #+#    #+#             */
/*   Updated: 2024/01/12 17:04:24 by mualkhid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dst;
	unsigned char	*source;

	if (!dest && !src)
		return (NULL);
	dst = (unsigned char *)dest;
	source = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		dst[i] = source[i];
		i++;
	}
	return (dst);
}

