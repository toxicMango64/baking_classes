#include "minishell.h"

void	execute_redirections(t_command *params)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		execute_child_process(params);
	else if (pid > 0)
		waitpid(pid, NULL, 0);
	else
		perror("fork");
}

void	execute_child_process(t_command *params)
{
	int		pipe_fd[2];
	char	*argv[] = {"/bin/sh", "-c", params->command, NULL};

	handle_input_redirection(params);
	handle_output_redirection(params);
	if (params->delimiter)
	{
		heredoc_read(params);
		if (pipe(pipe_fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		write(pipe_fd[1], params->content, params->total_read);
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
	}
	my_execlp("/bin/sh", argv);
	perror("execlp");
	exit(EXIT_FAILURE);
}

void	handle_input_redirection(t_command *params)
{
	int	fd;

	if (params->input_file)
	{
		fd = open(params->input_file, O_RDONLY);
		if (fd == -1)
		{
			perror("open input file");
			exit(EXIT_FAILURE);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
}

void	handle_output_redirection(t_command *params)
{
	int	fd;

	if (params->out_file)
	{
		if (params->append)
			fd = open(params->out_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(params->out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror("open output file");
			exit(EXIT_FAILURE);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

t_command	*heredoc_new(const char *delimiter)
{
	t_command	*heredoc;

	heredoc = malloc(sizeof(t_command));
	heredoc->delimiter = strdup(delimiter);
	heredoc->content = NULL;
	heredoc->content_size = 0;
	return (heredoc);
}

void	heredoc_init(t_command *heredoc)
{
	size_t	buffer_size;

	buffer_size = 1024;
	heredoc->content = malloc(buffer_size);
	if (heredoc->content == NULL)
		return ;
	heredoc->buffer_size = buffer_size;
	heredoc->total_read = 0;
}

void	heredoc_resize(t_command *heredoc)
{
	size_t	new_buffer_size;
	char	*new_buffer;

	new_buffer_size = heredoc->buffer_size * 2;
	new_buffer = malloc(new_buffer_size);
	if (new_buffer == NULL)
		return ;
	memcpy(new_buffer, heredoc->content, heredoc->total_read);
	free(heredoc->content);
	heredoc->content = new_buffer;
	heredoc->buffer_size = new_buffer_size;
}

void	heredoc_append(t_command *heredoc, char *line)
{
	size_t	line_len;

	line_len = strlen(line);
	if (heredoc->total_read + line_len + 1 > heredoc->buffer_size)
		heredoc_resize(heredoc);
	memcpy(heredoc->content + heredoc->total_read, line, line_len);
	heredoc->total_read += line_len;
	heredoc->content[heredoc->total_read] = '\n';
	heredoc->total_read++;
	heredoc->content[heredoc->total_read] = '\0';
}

void	heredoc_read(t_command *heredoc)
{
	char	*line;

	heredoc_init(heredoc);
	while ((line = readline("> ")) != NULL)
	{
		if (strcmp(line, heredoc->delimiter) == 0)
		{
			free(line);
			break ;
		}
		heredoc_append(heredoc, line);
		free(line);
	}
}

char	*heredoc_get_content(t_command *heredoc)
{
	return (heredoc->content);
}

void	heredoc_free(t_command *heredoc)
{
	free(heredoc->delimiter);
	free(heredoc->content);
	free(heredoc);
}

void	parse_and_execute(char *input)
{
	t_command	params;

	params = (t_command){0};
	parse_command(&params, input);
	if (params.command)
		execute_redirections(&params);
}

void	parse_command(t_command *params, char *input)
{
	char	*token;

	params->output_fd = -1;
	token = strtok(input, " ");
	while (token)
	{
		if (strcmp(token, "<") == 0)
			params->input_file = strtok(NULL, " ");
		else if (strcmp(token, ">") == 0)
		{
			params->out_file = strtok(NULL, " ");
			params->append = 0;
		}
		else if (strcmp(token, ">>") == 0)
		{
			params->out_file = strtok(NULL, " ");
			params->append = 1;
		}
		else if (strcmp(token, "<<") == 0)
		{
			params->delimiter = strtok(NULL, " ");
			heredoc_new(params->delimiter);
		}
		else
			add_command_token(params, token);
		token = strtok(NULL, " ");
	}
}

void	add_command_token(t_command *params, char *token)
{
	if (!params->command)
		params->command = allocate_and_copy_token(token);
	else
		append_token_to_command(&params->command, token);
}

char	*allocate_and_copy_token(const char *token)
{
	size_t	size;
	char	*new_command;

	size = strlen(token) + 1;
	new_command = malloc(size);
	if (!new_command)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	strcpy(new_command, token);
	return (new_command);
}

void	append_token_to_command(char **command, const char *token)
{
	size_t	new_size;
	char	*new_command;

	new_size = strlen(*command) + strlen(token) + 2;
	new_command = malloc(new_size);
	if (!new_command)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	strcpy(new_command, *command);
	strcat(new_command, " ");
	strcat(new_command, token);
	free(*command);
	*command = new_command;
}
