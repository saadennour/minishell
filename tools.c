/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 18:54:07 by sfarhan           #+#    #+#             */
/*   Updated: 2022/06/29 21:57:20 by sfarhan          ###   ########.fr       */
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

static char	*get_cmd(t_exec *exe, char **envp, int i)
{
	int		j;
	char	*path;
	char	**cmd;
	char	**exec;

	j = -1;
	path = envp[i];
	//printf ("hello 2\n");
	cmd = ft_split(&path[5], ':');
	//printf ("hello 2\n");
	exec = ft_split((char*)*exe->args, ' ');
	//printf ("hello 4\n");
	if (access(exec[0], F_OK) != -1)
		return (exec[0]);
	while (cmd[++j])
	{
		cmd[j] = ft_strjoin(cmd[j], "/");
		cmd[j] = ft_strjoin(cmd[j], exec[0]);
		if (access(cmd[j], F_OK) != -1)
			return (cmd[j]);
	}
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

void	run_cmd(t_cmd *cmd, char **envp)
{
	//int 	p[2];
	char	*buf;
	char	**ar;
	t_exec	*exe;
	// t_pipe	*pip;
	// t_redir	*red;

	if (cmd == 0)
		exit (1);
	if (cmd->type == EXEC)
	{
		exe = (t_exec*)cmd;
		if (exe->args[0] == 0)
			exit (1);
		//printf ("hello\n");
		buf = get_path(exe, envp);
		//printf ("hello\n");

		ar = ft_split(exe->args[0], ' ');
		//printf ("%s, %s\n", buf, ar[1]);
		//exe->eargs should be a double pointer containing the cmd and args.
		execve(buf, ar, envp);
	}
}