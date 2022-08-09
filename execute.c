/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 18:54:07 by sfarhan           #+#    #+#             */
/*   Updated: 2022/08/09 18:17:49 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	followed(char *s, int *i)
{
	int		token;

	if (s[(*i)] == '<')
	{
		token = '<';
		(*i)++;
		if (s[(*i)] == '<')
		{
			(*i)++;
			token = '-';
		}
		return (token);
	}
	else if (s[(*i)] == '>')
	{
		token = '>';
		(*i)++;
		if (s[(*i)] == '>')
		{
			(*i)++;
			token = '+';
		}
		return (token);
	}
	return (0);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			write (fd, &s[i], 1);
			i++;
		}
	}
}

static char	*get_cmd(t_exec *exe, char **envp, int i)
{
	int		j;
	char	*path;
	char	**cmd;

	j = -1;
	path = envp[i];
	cmd = ft_split(&path[5], ':', 0);
	if (access(exe->args[0], F_OK | X_OK) != -1)
		return (exe->args[0]);
	while (cmd[++j])
	{
		cmd[j] = ft_strjoin(cmd[j], "/");
		cmd[j] = ft_strjoin(cmd[j], exe->args[0]);
		if (access(cmd[j], F_OK) != -1)
			return (cmd[j]);
	}
	printf ("minishell: %s: command not found\n", exe->args[0]);
	exit (1);
}

char	*get_path(t_exec *exe, char **envp)
{
	int	i;

	i = -1;
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

void	run_cmd(t_cmd *cmd, char **envp, t_tool *tools, t_list **data)
{
	if (cmd == 0)
		exit (1);
	if (cmd->type == EXEC)
		type_exec(cmd, envp, tools, data);
	else if (cmd->type == PIPE)
		type_pipe(cmd, envp, tools, data);
	else if (cmd->type == REDIR)
		type_redir(cmd, envp, tools, data);
}
