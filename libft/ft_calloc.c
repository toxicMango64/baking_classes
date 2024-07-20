/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mualkhid <mualkhid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:31:13 by mualkhid          #+#    #+#             */
/*   Updated: 2024/02/22 20:03:38 by mualkhid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*str;

	if (size && (count > (UINT_MAX / size)))
		return (NULL);
	str = malloc(count * size);
	if (str == NULL)
		return (NULL);
	ft_bzero(str, count * size);
	return (str);
}




















// int main()
// {
// 	size_t count = 4;
// 	size_t size = 4;
// 	int *arr = ft_calloc(count, size);
// 	size_t i = 0;
// 	while (i < count)
// 	{
// 		printf("%d ", arr[i]);
// 		i++;
// 	}
// }
