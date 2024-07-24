# NAME	=	minishell
# CC		=	cc
# CFLAGS	=	-Wall -Wextra -Werror
# LDFLAGS	=	-lreadline
# RM		=	rm -f

# SRCDIR	=	src
# SRCS	=	src/minishell.c

# OBJDIR	=	obj
# OBJS	=	$(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# all: $(NAME)

# $(OBJDIR):
# 	mkdir -p $(OBJDIR)

# $(NAME): $(OBJS) | $(OBJDIR)
# 	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

# $(OBJDIR)/%.o: $(SRCDIR)/%.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# clean:
# 	$(RM) $(OBJS)

# fclean: clean
# 	$(RM) $(NAME) $(OBJDIR)

# re: fclean all

# .PHONY: all clean fclean re


# NAME	=	minishell
# CC		=	cc
# CFLAGS	=	-Wall -Wextra -Werror
# LDFLAGS	=	-lreadline
# LIBFT_DIR	=	libft
# LIBFT	=	$(LIBFT_DIR)/libft.a
# CFLAGS	+=	-I$(LIBFT_DIR)
# RM		=	rm -f

# SRCDIR	=	src
# SRCS	=	src/minishell.c

# OBJDIR	=	obj
# OBJS	=	$(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# all: $(LIBFT) $(NAME)

# $(LIBFT):
# 	make -C $(LIBFT_DIR)

# $(OBJDIR):
# 	mkdir -p $(OBJDIR)

# $(NAME): $(OBJS) | $(OBJDIR)
# 	$(CC) $(CFLAGS) $(LDFLAGS) -L$(LIBFT_DIR) -lft $^ -o $@

# $(OBJDIR)/%.o: $(SRCDIR)/%.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# clean:
# 	$(RM) $(OBJS)
# 	make -C $(LIBFT_DIR) clean

# fclean: clean
# 	$(RM) $(NAME) $(OBJDIR)
# 	make -C $(LIBFT_DIR) fclean

# re: fclean all

# .PHONY: all clean fclean re


# NAME	=	minishell
# CC		=	gcc
# CFLAGS	=	-Wall -Wextra -Werror -Iinc
# LDFLAGS	=	-lreadline
# LIBFT_DIR	=	libft
# LIBFT	=	$(LIBFT_DIR)/libft.a
# CFLAGS	+=	-I$(LIBFT_DIR) -Iinc
# RM		=	rm -f

# SRCDIR	=	src
# BUILTINDIR = src/builtin
# PARSEDIR = src/parse
# OBJDIR	=	obj
# SRCS	=	$(SRCDIR)/minishell.c \
#             $(BUILTINDIR)/cd.c \
#             $(BUILTINDIR)/echo.c \
#             $(BUILTINDIR)/env.c \
#             $(BUILTINDIR)/exit.c \
#             $(BUILTINDIR)/export.c \
#             $(BUILTINDIR)/pwd.c \
#             $(BUILTINDIR)/unset.c \
#             $(SRCDIR)/exec/exec.c \
#             $(PARSEDIR)/parse_utils.c \
#             $(PARSEDIR)/parse.c
# OBJS	=	$(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# all: $(LIBFT) $(NAME)

# $(LIBFT):
# 	make -C $(LIBFT_DIR)

# $(OBJDIR):
# 	mkdir -p $(OBJDIR)
# 	mkdir -p $(OBJDIR)/builtin
# 	mkdir -p $(OBJDIR)/exec
# 	mkdir -p $(OBJDIR)/parse

# $(NAME): $(OBJS) | $(OBJDIR)
# 	$(CC) $(CFLAGS) $(LDFLAGS) -L$(LIBFT_DIR) -lft $^ -o $@

# $(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
# 	$(CC) $(CFLAGS) -c $< -o $@

# clean:
# 	$(RM) $(OBJS)
# 	make -C $(LIBFT_DIR) clean

# fclean: clean
# 	$(RM) $(NAME) $(OBJDIR)
# 	make -C $(LIBFT_DIR) fclean

# re: fclean all

# .PHONY: all clean fclean re


NAME    =   minishell
CC      =   gcc
CFLAGS  =   -Wall -Wextra -Werror -Iinc -I$(LIBFT_DIR)/includes
LDFLAGS =   -L$(LIBFT_DIR) -lft -lreadline
LIBFT_DIR   =   libft
LIBFT   =   $(LIBFT_DIR)/libft.a
RM      =   rm -f

SRCDIR  =   src
BUILTINDIR = src/builtin
PARSEDIR = src/parse
OBJDIR  =   obj
SRCS    =   $(SRCDIR)/minishell.c \
            $(BUILTINDIR)/cd.c \
            $(BUILTINDIR)/echo.c \
            $(BUILTINDIR)/env.c \
            $(BUILTINDIR)/exit.c \
            $(BUILTINDIR)/export.c \
            $(BUILTINDIR)/pwd.c \
            $(BUILTINDIR)/unset.c \
            $(SRCDIR)/exec/exec.c \
            $(PARSEDIR)/parse_utils.c \
            $(PARSEDIR)/parse.c
OBJS    =   $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)
	mkdir -p $(OBJDIR)/builtin
	mkdir -p $(OBJDIR)/exec
	mkdir -p $(OBJDIR)/parse

$(NAME): $(OBJS) | $(OBJDIR)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ -L$(LIBFT_DIR) -lft -lreadline

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) -r $(OBJDIR)
	$(RM) $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re