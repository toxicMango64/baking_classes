/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mualkhid <mualkhid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 08:16:25 by mualkhid          #+#    #+#             */
/*   Updated: 2023/12/27 13:24:25 by mualkhid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = 0;
		i++;
	}
}
// int main()
// {
// 	char str[] = "Munia";
// 	size_t n = 4;
// 	size_t i;
// 	i = 0;
// 	ft_bzero(str, n);
// 	while (i < 4)
// 	{
// 		printf("%c\n", str[i]);
// 		i++;
// 	}
// }
