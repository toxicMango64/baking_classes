#ifndef PARSE_H
# define PARSE_H

# define MAX_ARGUMENTS 256

# include "minishell.h"
# include <string.h>
# include <stdlib.h>

typedef struct s_cmdline
{
	char				*arguments[MAX_ARGUMENTS];
	int					argcount;
	char const			*input_redirect;
	char const			*output_redirect;
	int					background;
	struct s_cmdline	*next;
}	t_cmdline;

char		*parse(char *user_input);
int			ft_isspace(int c);
int			is_empty(const char *str);
char		*str_clone(const char *source);
t_cmdline	*parset_cmdlines(char* line);

#endif

/**
 * qoutes or not (double and single)
 * expansion $ ($PATH $HOME) get it from env
 * 
*/

/**
 * command
 * flags
 * piped or not
*/

/**
 * $ " ' ! < >
 * << (heredoc)
 * >> < > redirections
 *
 * "   '$HOME' "
*/