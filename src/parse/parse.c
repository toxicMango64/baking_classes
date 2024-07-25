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

t_cmdline *parse_single_cmdline(const char *str_line)
{
	char		*line;
	char		*result;
	t_cmdline	*command;

	command = (t_cmdline *)malloc(sizeof(t_cmdline));
	if (is_empty(str_line))
		return (NULL);
	memset(command, 0, sizeof(t_cmdline));
	line = str_clone(str_line);
	extract_redirections(line, command); /* redirections needed */
	result = strtok(line, " ");
	while (result && command->argcount < (MAX_ARGUMENTS - 1))
	{
		((char**)command->arguments)[command->argcount] = str_clone(result);
		command->argcount++;
		result = strtok ( NULL, " ");
	}
	free(line);
	return (command);
}

t_cmdline	*parset_cmdlines(char *line)
{
	char		*next_str_cmd;
	t_cmdline	*command;

	if (is_empty(line))
		return (NULL);
	next_str_cmd = strchr(line , '|');
	if (next_str_cmd)
		*next_str_cmd = 0;
	command = parse_single_cmdline(line);
	if (!command)
		return (NULL);
	if (next_str_cmd)
		command->next = parset_cmdlines(next_str_cmd+1);
	return (command);
}

t_cmdline	*parse_cmd(const char *strline)
{
	t_cmdline	*head;
	t_cmdline	*last;
	char		*line;
	char		*ampersand;

	if (is_empty(strline))
		return (NULL);
	line = str_clone(strline);
	if (line[strlen(line) - 1] == '\n')
		line[strlen(line) - 1] = 0;
	if ((last = head = parset_cmdlines(line)))
	{
		while (last->next)
			last = last->next;
		/* are we doing the bonus? add extra steps */
	}
	free(line);
	return (head);
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
	
	command = parse_cmd(clean_input);
	return (pipe_splitted);
	// return (command); // returns char **command to run it
}
// this function does not handle the follwoing case :
// ls -la libft | cat input.t"x't"
