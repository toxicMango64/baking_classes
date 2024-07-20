/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mualkhid <mualkhid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 08:20:44 by mualkhid          #+#    #+#             */
/*   Updated: 2024/01/21 15:35:48 by mualkhid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	size_t	i;

	str = ft_strdup(s);
	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		str[i] = (*f)(i, str[i]);
		i++;
	}
	return (str);
}
// char to_upper(unsigned int i, char s)
// {
// 	return(ft_toupper(s));
// }
// int main()
// {
// 	char s[] = "abdo";
// 	char *result = ft_strmapi(s, to_upper);
// 	printf("%s\n", result);
// }
















// char to_lower(unsigned int i, char s)
// {
// 	return(ft_tolower(s));
// }
// int main()
// {
// 	char s[] = "SaLAd";
// 	char *result = ft_strmapi(s, to_lower);
// 	printf("%s\n", result);
// }
