/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 23:01:57 by sfarhan           #+#    #+#             */
/*   Updated: 2022/07/19 16:37:05 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

// #define	EXEC 1
// #define	PIPE 2
// #define	REDIR 3

enum e_define
{
	EXEC,
	PIPE,
	REDIR,
} ;

typedef struct t_cmd
{
	int	type;
}	t_cmd;

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
	char	*args[10];
}	t_exec;

//fd is gonna be either 0 or 1
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
	int	quote;
	int	start;
}	t_quote;

int	    ft_strlen(char *str);
char	*clean(char *str);
t_cmd	*end_it(t_cmd *cmd);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char const *s, char c);
char	**ft_advanced(char const *s, char *buf);
char	*get_path(t_exec *exe, char **envp);
int		lets_check(char *str);
char	*ft_path(char *line);
int		followed(char **s);
t_cmd	*piping(t_cmd *left, t_cmd *right);
t_cmd	*redirect(t_cmd	*exe, char *file, int mode, int fd, int token);
t_cmd	*exelior();
int		ft_strchr(char s, char *scan);
int		ft_skip(char *s, char *skip);
int		exist(char **ps, char *es, char *token);
int		get_token(char **ps, char *es, char **q, char **eq);
t_cmd	*parsecmd(char *str, char **env);
t_cmd	*parsepipe(char	**ps, char *es, char **env, t_quote quote);
t_cmd	*parsered(t_cmd	*cmd, char **ps, char *es);
void	run_cmd(t_cmd *cmd, char **envp, int *c);
int		ft_strncmp(const char *first, const char *second, size_t length);
int 	if_builtins(char *buf);
char	*ft_skip_spaces(char *inpt);
char	*if_dsigne(char *inpt,char **env);
char	*quotes(char *str, t_quote *quote);
void	handle_C(int sig);

#endif