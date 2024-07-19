/**
 * this is all libft functions can be deleted after conecting libft in the make file
 * strlen, strcpy, split, substr, putchar, putstr
*/
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <unistd.h>

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

static char	*ft_strcpy(char *src, char *dest)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(char *src)
{
	unsigned int	i;
	char			*dest;

	i = ft_strlen(src);
	dest = (char *)malloc(sizeof(char) * i + 1);
	if (!(dest))
		return (NULL);
	return (ft_strcpy(src, dest));
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	if (!(s))
		return (NULL);
	if (start >= ft_strlen(s)) // strlen(s) = 4 start = 6
		return (ft_strdup(""));
	if (len > ft_strlen(s)- start) // hello lo
		len = ft_strlen(s) - start;
	sub = (char *)malloc ((len + 1) * sizeof(char));
	if (!(sub))
		return (NULL);
	i = 0;
	if (start < ft_strlen(s))
	{
		while ((s[start] != '\0') && (i < len))
		{
			sub[i] = s[start];
			start++;
			i++;
		}
	}
	sub[i] = '\0';
	return (sub);
}


static void	free_all(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

static	int	wordcounter(char const *s, char c)
{
	int	i;
	int	subnum;

	i = 0;
	subnum = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
		{
			i++;
		}
		if ((s[i] != '\0') && (s[i] != c))
		{
			subnum++;
		}
		while ((s[i] != '\0') && (s[i] != c))
		{
			i++;
		}
	}
	return (subnum);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		start;
	char	**substrs;

	i = 0;
	j = 0;
	if (s == NULL)
		return (NULL);
	substrs = (char **)malloc(sizeof(char *) * (wordcounter(s, c) + 1));
	if (!(substrs) || !(s))
		return (NULL);
	while (j < wordcounter(s, c))
	{
		while (s[i] == c)
			i++;
		start = i;
		while ((s[i] != '\0') && (s[i] != c))
			i++;
		substrs[j] = ft_substr(s, start, i - start);
		if (!substrs[j])
			return (free_all(substrs), NULL);
		j++;
	}
	return (substrs[j] = NULL, substrs);
}
void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

//////////////////////////////////////////////////   echo function /////////////////////////////////////////////
/////////////////// anything above of this is libft but i could not link it because of smth in makefile///////////

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
int main()
{
	char *input;
	char **command;

	while (1)
	{
		input = readline("uncle$ ");
		add_history(input);
		command = ft_split(input, ' ');
		echo_command(command);
		// printf ("{%s}\n", input);
		free (input);
	}
	return (0);
}
