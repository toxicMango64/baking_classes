/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mualkhid <mualkhid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 08:19:55 by mualkhid          #+#    #+#             */
/*   Updated: 2024/02/22 20:04:01 by mualkhid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, s + i);
		i++;
	}
}






















// void to_upper(unsigned int i, char *str)
// {
// 	*str = ft_toupper(*str);
// }


// int main()
// {
// 	char s[] = "sAad";
// 	ft_striteri(s, to_upper);
// 	printf("%s\n", s);
// }
