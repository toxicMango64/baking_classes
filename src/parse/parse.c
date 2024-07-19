#include "../../inc/parse.h"

char	*trimcleanstring(char *str)
{
	char	*start;
	char	*end;
	char	*output;

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

// char	**parse(char *user_input)
char	*parse(char *user_input)
{
	char	*clean_input;
	// char	**command;

	clean_input = trimcleanstring(user_input);
	if (*user_input || *clean_input)
		add_history(clean_input);
	return (clean_input);
	// return (command);
}
