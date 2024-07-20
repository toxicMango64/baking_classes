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

int	main(int ac, char **av)
{
	char				*user_input;
	// char				**command; /* will run the command */
	char				*temp_cmd; /* temp char *temp_cmd */
	struct sigaction	sa;

	// if(ft_isdigit(3)) /* causes issues :SKULL: */
	// 	printf("lift is working\n\n");
	if (1 < ac)
		return (printf("%s: %s: is a file or a directory", av[0], av[1]), 126); /* minishell does not take args */
	sa.sa_handler = setup_signal_handlers; /* will handle every signal DO NOT DELETE */
	sigaction(SIGINT, &sa, NULL);
	sa.sa_flags = SA_RESTART;
	while (1)
	{
		user_input = readline("minishell-v1$ ");
		if (!user_input)
			return (perror("realine error"), 126);
		printf ("\tuser_input: {%s}\n", user_input);
		temp_cmd = parse(user_input);

		printf ("\ttemp_cmd: {%s}\n", temp_cmd);
		free (user_input);
	}
	return (0);
}
