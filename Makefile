NAME = minishell
FLAGS = -Wall -Wextra -Werror -lreadline -L /Users/sfarhan/homebrew/opt/readline/lib -I/Users/sfarhan/homebrew/opt/readline/include

SRCS =	main.c \
		ft_split.c \
		ft_strjoin.c \
		path.c \
		constructor.c \
		tools.c \
		parse.c \
		builtins.c \
		ft_dsigne.c \
		advanced.c \
		get_next_line.c \

all : $(NAME)

$(NAME) : $(SRCS)
	@gcc $(FLAGS) $(SRCS) -o $(NAME)

clean :
	@rm -rf $(NAME)
fclean :
	@rm -rf $(NAME)

re: fclean all
