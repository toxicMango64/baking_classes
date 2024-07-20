/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mualkhid <mualkhid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 08:18:22 by mualkhid          #+#    #+#             */
/*   Updated: 2024/01/12 17:28:05 by mualkhid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char	*sc;
	char	*dest;

	sc = (char *)src;
	dest = (char *)dst;
	if (sc < dest)
	{
		while (n)
		{
			dest[n - 1] = sc[n - 1];
			n--;
		}
	}
	else
		ft_memcpy(dest, sc, n);
	return (dst);
}
int main()
{
	char s[] = "DABLYAT";
	char *d = s - 1;
	size_t n = 7;
	ft_memmove(d, s, n);
	printf("%s\n", d);
	char s1[] = "DABLYAT";
	char *d1 = s1 - 1;
	memmove(d1, s1, n);
	printf("%s\n", d1);

}
