NAME = minishell
FLAGS = -Wall -Wextra -Werror -lreadline -L /Users/sfarhan/homebrew/opt/readline/lib -I/Users/sfarhan/homebrew/opt/readline/include

SRCS =	main.c \
		echo.c \
		ft_split.c \
		ft_strjoin.c \
		path.c \
		constructor.c \
		tools.c \
		execute.c \
		parse.c \
		builtins.c \
		ft_dsigne.c \
		advanced.c \
		get_next_line.c \
		ft_splito.c \
		expand_tools.c \
		correction.c \

all : $(NAME)

$(NAME) : $(SRCS)
	@gcc $(FLAGS) $(SRCS) -o $(NAME)

clean :
	@rm -rf $(NAME)
fclean :
	@rm -rf $(NAME)

re: fclean all