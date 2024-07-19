#include "../inc/minishell.h"

int	main(int ac, char **av)
{
	char	*user_input;
	// char	**command;
	char	*command;

	if (1 < ac)
		return (printf("%s: %s: is a file or a directory", av[0], av[1]), 126); // minishell does not take args
	while (1)
	{
		user_input = readline("minishell-v1$ ");
		if (!user_input)
			return (perror("user input error"), 126);
		printf ("\tuser_input: {%s}\n", user_input);
		command = parse(user_input);
		


		printf ("\tcommand: {%s}\n", command);
		free (user_input);
	}
	return (0);
}
