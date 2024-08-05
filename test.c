
void	cleanup_and_exit(int exit_code)
{
	// Free things we didn't yet
	rl_clear_history();
	exit(exit_code);
}

int	main(void)
{
	char *input;

	while (1)
	{
		input = readline("baking_classes> ");
		if (input == NULL)
			cleanup_and_exit(EXIT_SUCCESS);
		if (strcmp(input, "exit") == 0)
		{
			free(input);
			cleanup_and_exit(EXIT_SUCCESS);
		}
		if (*input)
			add_history(input);
		parse_and_execute(input);
		free(input);
	}
	return (EXIT_SUCCESS);
}