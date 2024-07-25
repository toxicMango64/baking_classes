#include "../../inc/parse.h"
#include "../../inc/minishell.h"

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

char	*str_clone(const char *source)
{
	char	*clone;

	clone = (char *)malloc(strlen(source) + 1);
	strcpy (clone, source);
	return (clone);
}

int is_empty(const char *str)
{
	if (!str)
		return (1);

	while (*str)
	if (!isspace(*(str++)))
	return (0);
	return (1);
}

char	*copyWord(char	*str)
{
    char	*begin = NULL;
    char	*end = NULL;
    char	*word;
	char	current_char;

    while (!end)
    {
        current_char = *str;
        if (current_char == '>' || current_char == '<' || current_char == '='
			|| current_char == 0)
            end = str - 1;
        else if (current_char == ' ')
            if (begin)
                end = str - 1;
        else
            if (!begin)
                begin = str;
        str++;
    }
    if (begin == NULL)
        return (NULL);
    word = (char *) malloc(end - begin + 2);
    if (word == NULL)
        return (NULL);
    strncpy(word, begin, (int)(end - begin) + 1);
    word[(int)(end - begin) + 1] = '\0';
    return (word);
}

void	extract_redirections(char	*str_line, t_cmdline *command)
{
	char	*str;

	str = str_line;
	while ((str = strpbrk(str, "<>")))
	{
		if (*str == '<')
		{
			free (command->input_redirect);
			command->input_redirect = copy_word(str + 1);
		}
		else
		{
			free (command->output_redirect);
			command->output_redirect = copy_word(str+1);
		}
		*(str++) = 0;
	}
}
