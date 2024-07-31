#include <errno.h>
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

extern char	**environ;

typedef struct s_command
{
	char	*command;
	char	*input_file;
	char	*out_file;
	int		append;
	char	*heredoc_delimiter;
}			t_command;

void		handle_input_redirection(t_command *params);
void		handle_output_redirection(t_command *params);
void		handle_heredoc(t_command *params);
void		execute_child_process(t_command *params);
void		parse_command(t_command *params, char *input);
void		add_command_token(t_command *params, char *token);
void		execute_command(const char *file, char *const argv[]);
void		try_exec_in_path(const char *file, char *const argv[]);
char		*construct_full_path(const char *dir, const char *file);
void		append_token_to_command(char **command, const char *token);
char		*allocate_and_copy_token(const char *token);

void	my_execlp(const char *file, char *const argv[])
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
		execute_command(file, argv);
	else
		waitpid(pid, &status, 0);
}

void	execute_command(const char *file, char *const argv[])
{
	execve(file, argv, environ);
	if (errno == ENOENT)
		try_exec_in_path(file, argv);
	perror("execve");
	exit(EXIT_FAILURE);
}

void	try_exec_in_path(const char *file, char *const argv[])
{
	char	*path;

	path = getenv("PATH");
	char *path_dup, *dir, *full_path;
	if (path)
	{
		path_dup = strdup(path);
		dir = strtok(path_dup, ":");
		while (dir)
		{
			full_path = construct_full_path(dir, file);
			if (full_path)
			{
				execve(full_path, argv, environ);
				free(full_path);
			}
			dir = strtok(NULL, ":");
		}
		free(path_dup);
	}
}

char	*construct_full_path(const char *dir, const char *file)
{
	int		dir_len;
	int		file_len;
	char	*full_path;

	dir_len = strlen(dir);
	file_len = strlen(file);
	if (dir_len + 1 + file_len + 1 > 1024)
		return (NULL);
	full_path = malloc(dir_len + 1 + file_len + 1);
	if (!full_path)
		return (NULL);
	memcpy(full_path, dir, dir_len);
	full_path[dir_len] = '/';
	memcpy(full_path + dir_len + 1, file, file_len);
	full_path[dir_len + 1 + file_len] = '\0';
	return (full_path);
}

void	execute_execlp(const char *command)
{
	char *const argv[] = {"/bin/sh", "-c", (char *)command, NULL};
	my_execlp("/bin/sh", argv);
}

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
	handle_input_redirection(params);
	handle_output_redirection(params);
	if (params->heredoc_delimiter)
		handle_heredoc(params);
	execlp("/bin/sh", "sh", "-c", params->command, (char *)NULL);
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

void	handle_heredoc(t_command *params)
{
	int		pipe_fd[2];
	char	*line;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	close(pipe_fd[0]);
	while (1)
	{
		line = readline("> ");
		if (strcmp(line, params->heredoc_delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(pipe_fd[1], line, strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
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
			params->heredoc_delimiter = strtok(NULL, " ");
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

void	cleanup_and_exit(int exit_code)
{
	// Free things we didnt yet
	rl_clear_history();
	exit(exit_code);
}

int	main(void)
{
	char	*input;
	int		exit_code;

	while (1)
	{
		input = readline("baking_classes> ");
		if (input == NULL)
			cleanup_and_exit(EXIT_SUCCESS);
		if (*input)
			add_history(input);
		parse_and_execute(input);
		free(input);
	}
	return (EXIT_SUCCESS);
}
