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




# define MAX_HEREDOC_SIZE 4096

extern char	**environ;

typedef struct s_command
{
	char	*command;
	char	*input_file;
	char	*out_file;
	int		append;
	char	*delimiter;
	char	*content;
	size_t	content_size;
	size_t	buffer_size;
	size_t	total_read;
	int	output_fd;
}			t_command;


void		parse_and_execute(char *input);
void		handle_input_redirection(t_command *params);
void		handle_output_redirection(t_command *params);
void		heredoc_read(t_command *heredoc);
char		*heredoc_get_content(t_command *heredoc);
void		heredoc_free(t_command *heredoc);
void		heredoc_init(t_command *heredoc);
void		execute_child_process(t_command *params);
void		parse_command(t_command *params, char *input);
void		add_command_token(t_command *params, char *token);
void		execute_command(const char *file, char *const argv[]);
void		try_exec_in_path(const char *file, char *const argv[]);
char		*construct_full_path(const char *dir, const char *file);
void		append_token_to_command(char **command, const char *token);
char		*allocate_and_copy_token(const char *token);
void		cleanup_and_exit(int exit_code);
void		execute_redirections(t_command *params);
void		my_execlp(const char *file, char *const argv[]);
void		execute_execlp(const char *command);

#endif

#endif
