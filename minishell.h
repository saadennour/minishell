/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 23:01:57 by sfarhan           #+#    #+#             */
/*   Updated: 2022/08/08 18:48:29 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# define BLUE    "\e[0;34m"
# define RED     "\e[0;31m"
# define GREEN   "\e[0;32m"
# define YELLOW  "\e[1;33m"
# define RESET   "\e[0m"

enum e_define
{
	EXEC,
	PIPE,
	REDIR,
} ;

typedef struct t_list
{
	char			*name;
	char			*value;
	struct t_list	*next;
}	t_list;

typedef struct t_cmd
{
	int	type;
}	t_cmd;

typedef struct t_tool
{
	char	*limiter;
	int		c;
	int		stdin_copy;
	int		stdout_copy;
	int		fd;
}	t_tool;

typedef struct t_pipe
{
	int				type;
	struct t_cmd	*left;
	struct t_cmd	*right;
}	t_pipe;

//exec in case running a program
//args for filename
//and eargs for argv
typedef struct t_exec
{
	int		type;
	char	**args;
}	t_exec;

typedef struct t_redir
{
	int				type;
	struct t_cmd	*exe;
	char			*file;
	int				mode;
	int				fd;
	int				token;
}	t_redir;

typedef struct t_quote
{
	int	*quote;
	int	start;
}	t_quote;

int		ft_strlen(char *str);
char	*clean(char *str);
int		ft_limites(char *str);
t_cmd	*end_it(t_cmd *cmd);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char const *s, char c, int access);
char	**ft_advanced(char const *s, char *buf);
char	*get_path(t_exec *exe, char **envp);
int		lets_check(char *str);
char	*ft_path(char *line);
int		followed(char **s);
t_cmd	*piping(t_cmd *left, t_cmd *right);
t_cmd	*redirect(t_cmd	*exe, char *file, int mode, int fd, int token);
t_cmd	*exelior(char *s);
int		ft_strchr(char s, char *scan);
int		ft_skip(char *s, char *skip);
int		exist(char **ps, char *token);
int		get_token(char **ps, char **q);
t_cmd	*parsecmd(char *str, char **env);
t_cmd	*parsepipe(char	**ps, char **env, t_quote quote);
t_cmd	*parsered(t_cmd	*cmd, char **ps, char **env, t_quote quote);
void	run_cmd(t_cmd *cmd, char **envp, t_tool *tools, t_list **data);
int		ft_strncmp(const char *first, const char *second, size_t length);
int		if_builtins(char **inpt, char **envp, t_list **data);
int		ft_skip_spaces(char *inpt);
char	*if_dsigne(char *inpt, char **env, t_quote quote, int *x);
char	*quotes(char *str, t_quote *quote);
void	handle_c(int sig);
char	*get_next_line(int fd);
char	**if_echo(char *str);
int		wd_count(const char *str, char c, int access);
int		tokenizer(char *str, int *x);
char	*no_space(char *str);
int		ft_echo(char **cmd, t_list *data);
char	**ft_splito(char const *s, char c);
int		spaces_still(char *str);
int		ft_strcmp(char *s1, char *s2);
int		num_quotes(const char *str, char c);
void	accountant(char **str, int i, int *dollar);
char	**cashier(char *str);
char	*after_world(char *str);
char	*exdsigne(char *op, char **env);
char	**forenv(char **env);
int		exec_args(t_exec **exec, int i, char **ps);
char	*corrected(char *line, char *str);

#endif