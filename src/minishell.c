#include "../inc/minishell.h"

/**
 * char *argv[] = {"ls", "-l", "-a", NULL}; // arguments for the new program
 * char *envp[] = {"PATH=/bin:/usr/bin", "HOME=/home/user", NULL}; // environment variables
 * if (bultin)
 * 	exe_bultinft();
 * else
 * 	if (execve("/bin/bash", argv, envp) == -1)
 * 		(perror("execve"), exit(EXIT_FAILURE));
 */
int	main(int ac, char **av)
{
	char		*user_input;
	// char		*command;

	if(ft_isdigit(3))
		printf("lift is working\n\n");
	if (1 < ac)
		return (printf("%s: %s: is a file or a directory", av[0], av[1]), 126); // minishell does not take args

	while (1)
	{
		user_input = readline("minishell-v1$ ");
		if (!user_input)
			return (perror("user input error"), 126);
		if (*user_input)
			add_history(user_input);
		printf ("{%s}\n", user_input);

		// command = parse(user_input);
		// printf ("{%s}\n", command);

		// char *argv[] = {"ls", "-l", "-a", NULL}; // arguments for the new program
		// char *envp[] = {"PATH=/bin:/usr/bin", "HOME=/home/user", NULL}; // environment variables
		// if (execve("/bin/bash", argv, envp) == -1)
		// 	(free (user_input), perror("execve"), exit(EXIT_FAILURE));
		free (user_input);
	}

	return (0);
}

/**
 * example for env:
 *
 * /usr/local/bin
 * /usr/bin
 * /bin
 * /usr/sbin
 * /sbin
*/
