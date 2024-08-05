#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

extern char **environ;

/* to understand 

int main()
{
    printf("Before execlp\n");
    execlp("/bin/ls", "ls", "-l", "-a", NULL);
    printf("After execlp\n");  // This line will not be executed
    return (0);
}

int	main(void)
{
	char *args[] = {"ls", "-la", NULL};
	char *envp[] = {NULL};

	execve("/bin/ls", args, envp);
	printf("After execve\n"); // This line will not be executed
	return (0);
}


*/
#include "minishell.h"

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
	char *const argv[] = {"/bin/sh", "sh", "-c", (char *)command, NULL};
	my_execlp("/bin/sh", argv);
}