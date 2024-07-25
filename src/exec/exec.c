#include "../../inc/exec.h"

void execute_command(t_command *cmd, minishell *shell)
{
	// execute a single command
	if (cmd->cmd == "echo")
		// handle echo builtin
	else if (cmd->cmd == "cd")
		// handle cd builtin
	else if (cmd->cmd == "cd")
		// handle cd builtin
	else if (cmd->cmd == "cd")
		// handle cd builtin
	else
		// execute external command using execve
}
