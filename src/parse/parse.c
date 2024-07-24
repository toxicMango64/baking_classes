#include "../../inc/parse.h"
#include "../../inc/minishell.h"

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
