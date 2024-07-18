NAME	=	minishell
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
LDFLAGS	=	-lreadline
RM		=	rm -f

SRCDIR	=	src
SRCS	=	src/minishell.c

OBJDIR	=	obj
OBJS	=	$(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(NAME): $(OBJS) | $(OBJDIR)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME) $(OBJDIR)

re: fclean all

.PHONY: all clean fclean re
