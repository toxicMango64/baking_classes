#include "../inc/minishell.h"

/* Function to handle Ctrl-C Signal */
void	catch_all_signals(int signum)
{
	printf("\n%s:%s$ -> ",getenv("USER"), getcwd(NULL, MAX) );
	printf("Caught signal: {%d}\n", signum);
}

/**
 * initialize an empty signal set
 * add each signal to the set
*/
void	setup_signal_handlers(void)
{
	int					signum;
	sigset_t			all_signals;
	struct sigaction	sa;

	signum = 0;
	sigemptyset(&all_signals);
	while (++signum < NSIG)
		sigaddset(&all_signals, signum);
	sa.sa_handler = catch_all_signals;
	sa.sa_mask = all_signals;
	sa.sa_flags = 0;
	signum = 0;
	while (++signum < NSIG)
		if (sigaction(signum, &sa, NULL) == -1)
			(perror("\nsigaction"), exit(1));
}

// functions
// void	lexer(char *input, t_token **tokens)
// {
// 	// tokenize input into individual tokens
// 	// ...
// }

// void	parser(t_token *tokens, t_command **commands)
// {
// 	/* parse tokens into a list of commands */
// 	/* ... */
// }

void print_tokens(t_token *tokens)
{
    while (tokens != NULL)
    {
        printf("Token: {%s}, Type: {%d}\n", tokens->value, tokens->type);
        tokens = tokens->next;
    }
}

int	interactive_mode(t_minishell *shell)
{
	char		*user_input;
	// char		**command; /* will run the command */
	char		*temp_cmd; /* temp char *temp_cmd */
	t_token		*tokens;
	t_command	*commands;
	t_command	*cmd;

	while (1)
	{
		user_input = readline("minishell-v1$ ");
		if (!user_input)
			return (perror("error while reading input"), 126);
		printf ("\tuser_input: {%s}\n", user_input);
		temp_cmd = parse(user_input);
		lexer(user_input, &tokens);

		print(user_input, &tokens);
		
		free (user_input);
		// parser(tokens, &commands);
		// cmd = commands;
		// while (cmd)
		// {
		// 	execute_command(cmd, shell);
		// 	cmd = cmd->next;
		// }
		// handle Ctrl-C, Ctrl-D, and Ctrl-'\'
	}
	return (0);
}

int	interactive_mode(t_minishell *shell)
{
	char		*user_input;
	// char		**command; /* will run the command */
	char		*temp_cmd; /* temp char *temp_cmd */
	t_token		*tokens;
	t_command	*commands;
	t_command	*cmd;

	while (1)
	{
		user_input = readline("minishell-v1$ ");
		if (!user_input)
			return (perror("error while reading input"), 126);
		printf ("\tuser_input: {%s}\n", user_input);
		temp_cmd = parse(user_input);
		lexer(user_input, &tokens);

		print(user_input, &tokens);
		
		free (user_input);
		// parser(tokens, &commands);
		// cmd = commands;
		// while (cmd)
		// {
		// 	execute_command(cmd, shell);
		// 	cmd = cmd->next;
		// }
		// handle Ctrl-C, Ctrl-D, and Ctrl-'\'
	}

	while (1)
	{
		user_input = readline("minishell-v1$ ");
		// user_input = "echo hello | echo he\'ll\'o";
		if (!user_input)
			return (perror("realine error"), 126);
		printf ("\tuser_input: {%s}\n", user_input);
		command = parse(user_input);
		free (user_input);
	}

	return (0);
}

int	main(int ac, char **av)
{
	t_minishell			shell;
	// struct sigaction	sa;

	if (1 < ac)
		return (printf("%s: %s: is a file or a directory", av[0], av[1]), 126); /* minishell does not take args */

	// sa.sa_handler = setup_signal_handlers; /* will handle every signal DO NOT DELETE */
	// sigaction(SIGINT, &sa, NULL);
	// sa.sa_flags = SA_RESTART;

	shell.env = get_env(); /* initialize environment variables */
	shell.pwd = getcwd(NULL, 0); /* initialize current working directory */
	shell.history = NULL; /* initialize history */
	shell.commands = NULL; /* initialize commands */

	if (interactive_mode(&shell))
		return (printf ("vegy sed!"), 126); /* returns a random value does not have a meaning */

	return (0);
}
//ls -la libft | cat input.txt
//cc -lreadline src/minishell.c src/parse/*.c -o minishell

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
