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


void	my_execlp(const char *file, char *const argv[])
{
	pid_t	pid;
	char	*path;
	char	*path_dup;
	char	*dir;
	char 	full_path[1024];
 	int		dir_len;
	int		file_len;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		execve(file, argv, environ);
		if (errno == ENOENT)
		{
			path = getenv("PATH");
			if (path)
			{
				path_dup = strdup(path);
				dir = strtok(path_dup, ":");
				while (dir)
				{
					dir_len = strlen(dir);
					file_len = strlen(file);
					if (dir_len + 1 + file_len + 1 <= 1024)
					{
						memcpy(full_path, dir, dir_len);
						full_path[dir_len] = '/';
						memcpy(full_path + dir_len + 1, file, file_len);
						full_path[dir_len + 1 + file_len] = '\0';
						execve(full_path, argv, environ);
					}
					dir = strtok(NULL, ":");
				}
				free(path_dup);
			}
		}
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
		waitpid(pid, &status, 0);
}

void	execute_execlp(const char *command)
{
	char	*argv[] = {"/bin/sh", "-c", (char *)command, NULL};

	my_execlp("/bin/sh", argv);
}

int	main(void)
{
	execute_execlp("ls -l");
	execlp("ls", "ls", "-l", NULL);
	return (0);
}
