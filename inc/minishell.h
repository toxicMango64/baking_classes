#ifndef MINISHELL_H
# define MINISHELL_H

# define MAX_INPUT 262144
# define MAX 2048

# include "parse.h"
# include <unistd.h>
# include <stdio.h>
# include <ctype.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
#include "exec.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


/* --------------------------------- minishell ------------------------------ */

# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>

/* --------------------------------- minishell ------------------------------ */

int				ft_atoi(const char *nptr);
char			*ft_strdup(const char *s1);
size_t			ft_strlen(const char *s);
char			*ft_substr(char const *s, unsigned int start, size_t len);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);


/* --------------------------------- parser --------------------------------- */
/* --------------------------------- parser --------------------------------- */

#endif
