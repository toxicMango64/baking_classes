#include "../../inc/parse.h"

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




//above can be deleted after linking libft



char	*trimcleanstring(char *str)
{
	char *start;
	char *end;
	char *output;

	start = str;
	end = str;
	output = str;
	while (isspace((unsigned char)*start))
		start++;
	if (*start == '\0')
		return (*output = '\0', output);
	while (*end != '\0')
	{
		if (isspace((unsigned char)*end))
		{
			end++;
			if (!isspace((unsigned char)*end) && *end != '\0')
				*output++ = ' ';
		}
		else
			*output++ = *end++;
	}
	if (isspace((unsigned char)*(output - 1)))
		*(output - 1) = '\0';
	else
		*output = '\0';
	return (str);
}

char **check_quotes(char **pipe_splitted)
{
	int i = 0;
	while (pipe_splitted[i])
	{
		int j = 0;
		int in_single_quote = 0;
		int in_double_quote = 0;
		while (pipe_splitted[i][j])
		{
			if (pipe_splitted[i][j] == '"')
			{
				if (!in_single_quote)
					in_double_quote =!in_double_quote;
			}
			else if (pipe_splitted[i][j] == '\'')
			{
				if (!in_double_quote)
					in_single_quote =!in_single_quote;
			}
			j++;
		}
		if ((in_double_quote) || (in_single_quote))
			printf("you have unclosed double quote in str[%d]\n", i);
		i++;
	}
	return (pipe_splitted);
}
char	**parse(char *user_input)
{
	char	*no_spaces_input;
	char** pipe_splitted;
	char** checked_quotes;

	no_spaces_input = trimcleanstring(user_input);
	pipe_splitted = ft_split(no_spaces_input, '|');
	checked_quotes = check_quotes(pipe_splitted);
	if (*user_input || *no_spaces_input)
		add_history(user_input);
	return (pipe_splitted);
}
// this function does not handle the follwoing case :
// ls -la libft | cat input.t"x't"
