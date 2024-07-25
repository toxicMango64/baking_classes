#ifndef MINISHELL_H
# define MINISHELL_H

# define MAX_INPUT 262144
# define MAX 2048

# include "parse.h"
# include <unistd.h>
# include <stdio.h>
# include <ctype.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

/* --------------------------------- minishell ------------------------------ */

# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>

/* --------------------------------- minishell ------------------------------ */

/* --------------------------------- minishell ------------------------------ */

// extern char **environ;

// structs
typedef enum
{
	WORD,
	OPERATOR,
	PIPE,
	/* ... */
}	token_type;

// Define a t_token structure
typedef struct s_token
{
	token_type		type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_command
{
	char				**argv;
	int					argc;
	char				*cmd;
	struct s_command	*next;
}	t_command;

// typedef struct s_cmdline
// {
// 	char				*arguments[MAX_ARGUMENTS];
// 	int					argcount;
// 	char const			*input_redirect;
// 	char const			*output_redirect;
// 	int					background;
// 	struct s_cmdline	*next;
// }	t_cmdline;

typedef struct s_minishell
{
	char	**env;
	char	*pwd;
	t_token	*history;
	t_command	*commands;
}	t_minishell;

/* --------------------------------- minishell ------------------------------ */

int		ft_atoi(const char *nptr);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);

/* --------------------------------- builtin -------------------------------- */

char	**get_env(void);
char	*get_path(void);

/* --------------------------------- builtin -------------------------------- */


/* --------------------------------- minishell ------------------------------ */

/* --------------------------------- parser --------------------------------- */
/* --------------------------------- parser --------------------------------- */

/* --------------------------------- exec ----------------------------------- */

// void execute_command(t_command *cmd, minishell *shell);

/* --------------------------------- exec ----------------------------------- */

#endif
