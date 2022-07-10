/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 18:54:07 by sfarhan           #+#    #+#             */
/*   Updated: 2022/07/05 23:42:43 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	followed(char **s)
{
	int		token;
	char	*p;
	
	p = *s;
	if (*p == '<')
	{
		token = '<';	
		p++;
		if (*p == '<')
		{
			p++;
			token = '-';
			*s = p;
			return (token);
		}
		*s = p;
		return (token);
	}
	else if (*p == '>')
	{
		token = '>';
		p++;
		if (*p == '>')
		{
			p++;
			token = '+';
			*s = p;
			return (token);
		}
		*s = p;
		return (token);
	}
	return (0);
}

char	*clean(char *str)
{
	int		i;
	char	*clean;

	i = 0;
	while (str[i] != '\0' && !ft_strchr(str[i], " \t\n\f\v\r"))
		i++;
	clean = malloc (sizeof(char) * i);
	i = 0;
	while (str[i] != '\0' && !ft_strchr(str[i], " \t\n\f\v\r"))
	{
		clean[i] = str[i];
		i++;
	}
	clean[i] = '\0';
	return (clean);
}

char	*quotes(char *str, int *quote)
{
	int		i;
	int		j;
	int		len;
	char	*buf;

	i = 0;
	j = 0;
	len = 0;
	while (str[i])
	{
		//print until u find the same quote and so on
		if (str[i] == 34)
		{
			if ((*quote) == 0)
				(*quote)++;
			str[i] = 1;
			while (str[i] && str[i] != 34)
			{
				len++;
				i++;
			}
			if (str[i] == '\0')
			{
				printf ("minishell: quotation error\n");
				exit (1);
			}
			str[i] = 1;
		}
		if (str[i] == 39)
		{
			if ((*quote) == 0)
				(*quote) += 2;
			str[i] = 1;
			while (str[i] && str[i] != 39)
			{
				len++;
				i++;
			}
			if (str[i] == '\0')
			{
				printf ("minishell: quotation error\n");
				exit (1);
			}
			str[i] = 1;
		}
		i++;
		len++;
	}
	buf = malloc (sizeof(char) * len + 1);
	i = 0;
	while (str[i])
	{
		if (str[i] == 1)
			i++;
		buf[j] = str[i];
		i++;
		j++;
	}
	buf[j] = '\0';
	//return char allocated with the right size and quote by reference
	return (buf);
}

static char	*get_cmd(t_exec *exe, char **envp, int i)
{
	int		j;
	char	*path;
	char	**cmd;
	char	**exec;

	j = -1;
	path = envp[i];
	cmd = ft_split(&path[5], ':');
	exec = ft_split(*exe->args, ' ');
	//printf ("%s , %s\n", exec[0], exec[1]);
	if(if_builtins(exec[0]) == 0)
		exit(0);
	if (access(exec[0], F_OK) != -1)
		return (exec[0]);
	while (cmd[++j])
	{
		cmd[j] = ft_strjoin(cmd[j], "/");
		cmd[j] = ft_strjoin(cmd[j], exec[0]);
		if (access(cmd[j], F_OK) != -1)
			return (cmd[j]);
	}
	printf ("minishell: %s: command not found\n", exec[0]);
	return (0);
}

char	*get_path(t_exec *exe, char **envp)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (envp[++i])
	{
		if (envp[i][0] == 'P')
		{
			if (ft_strncmp(envp[i], "PATH=", 5) == 0)
				return (get_cmd(exe, envp, i));
		}
	}
	return (0);
}

void	run_cmd(t_cmd *cmd, char **envp, int *c)
{
	int		fd;
	int 	p[2];
	char	*buf;
	char	**ar;
	t_exec	*exe;
	t_pipe	*pip;
	t_redir	*red;
	t_redir	*red2;

	if (cmd == 0)
		exit (1);
	if (cmd->type == EXEC)
	{
		//printf ("hello\n");
		exe = (t_exec*)cmd;
		if (exe->args[0] == 0)
			exit (1);
		buf = get_path(exe, envp);
		if (*c != 0)
		{
			ar = ft_split(exe->args[0], ' ');
			//printf ("%s %s\n", ar[0], ar[1]);
			execve(buf, ar, envp);
		}
		execve(buf, exe->args, envp);
		//printf ("%s, %s, %s\n", buf, exe->args[0], exe->args[1]);
		//exe->eargs should be a double pointer containing the cmd and args.
	}
	else if (cmd->type == PIPE)
	{
		//(*c)++;
		pip = (t_pipe*)cmd;
		if (pipe(p) == -1)
		{
			printf ("An error occured in the pipe function\n");
			exit (1);
		}
		if (fork() == 0)
		{
			if (pip->left->type == EXEC)
				*c = 1;
			close(p[0]);
			dup2(p[1], STDOUT_FILENO);
			run_cmd(pip->left, envp, c);
		}
		else
		{
			if (pip->right->type == EXEC)
				*c = 0;
			close(p[1]);
			dup2(p[0], STDIN_FILENO);
			run_cmd(pip->right, envp, c);
		}
		close(p[0]);
		close(p[1]);
		wait(0);
	}
	else if (cmd->type == REDIR)
	{
		red = (t_redir*)cmd;
		fd = open(red->file, red->mode, 777);
		if (*c == 0)
		{
			//printf ("hello\n");
			dup2(fd, red->fd);
			if (red->exe->type == REDIR)
			{
				red2 = (t_redir*)red->exe;
				if (red->token == red2->token)
					(*c)++;
			}
		}
		run_cmd(red->exe, envp, c);
	}
}

char	*ft_skip_spaces(char *inpt)
{
	while (*inpt != '\0' && ft_strchr(*inpt, " \t\n\f\v\r"))
			inpt++;
	return(inpt);
}