#include "../../inc/parse.h"

int	ft_isspace(char ch)
{
	if ("\t" == ch || "\n" == ch || "\v" == ch || "\f" == ch || "\r" == ch
		|| " " == ch)
	return (ch);
}
/* 
*/