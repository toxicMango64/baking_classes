#ifndef PARSE_H
# define PARSE_H

# include "minishell.h"
# include <string.h>
# include <stdlib.h>

char	**parse(char *user_input);
int		ft_isspace(int c);

#endif