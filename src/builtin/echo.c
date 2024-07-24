#include "../inc/minishell.h"


/*
*	Checks whether an arg is an -n option flag.
*	Returns 1 if the arg is at least -n , returns 0 if it is smth else but -n -nn -nnn
*/
int	is_n_option(char *arg)
{
	int		i;
	int	flag;

	flag = 0;
	i = 0;
	if (arg[i] != '-') //check if start with - or not
		return (flag); //if not return 0 because it's not -n
	i++; // if yes check the character after it
	while (arg[i] && arg[i] == 'n') // if it is n keep checking till the end
		i++;
	if (arg[i] == '\0') // if u reached the end that means all of them are n
		flag = 1; // set the flag as 1 because we found at least -n
	return (flag);
}

/*
*	printing the message after echo
*/
void	echo_printing(char **args, int flag, int i)
{
	if (!args[i]) // the case of just echo
	{
		if (!flag) // if u found just echo print a new line
			ft_putchar_fd('\n', 1); //ft_putstr_fd
		return ;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1]) // if there is more than one arg put a space between them
			ft_putchar_fd(' ', 1);//ft_putstr_fd
		else if (!args[i + 1] && !flag) //if there is no more args and -n print \n
			ft_putchar_fd('\n', 1);//ft_putstr_fd
		i++;
	}
}

/*
*	Executes the echo command: prints the strings after echo
*	and adding new line or not depends on the -n option.
*/
int	echo_command(char **args)
{
	int		i;
	int		flag;

	flag = 0;
	i = 1;
	while (args[i] && is_n_option(args[i])) // if it is at least (-n ) set the flag as 1
	{
		flag = 1;
		i++;
	}
	echo_printing(args, flag, i);
	return (0);
}

/////this is how u can use echo command in our project so far
// int main()
// {
// 	char *input;
// 	char **command;

// 	while (1)
// 	{
// 		input = readline("uncle$ ");
// 		add_history(input);
// 		command = ft_split(input, ' ');
// 		echo_command(command);
// 		// printf ("{%s}\n", input);
// 		free (input);
// 	}
// 	return (0);
// }
