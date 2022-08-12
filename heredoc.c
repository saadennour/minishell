/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 19:30:48 by sfarhan           #+#    #+#             */
/*   Updated: 2022/08/12 19:36:12 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc(t_redir *red, t_tool *tools)
{
	t_exec	*exe;
	char	*ar;
	char	**end;
	int		i;

	i = 0;
	red->file = ft_strjoin(red->file, " ");
	tools->fd = open("/tmp/ ", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (tools->fd < 0)
	{
		printf ("Error\n");
		exit(1);
	}
	dup2(tools->stdin_copy, 0);
	tools->limiter = ft_strjoin(red->file, tools->limiter);
	if (red->exe->type == EXEC)
	{
		exe = (t_exec *)red->exe;
		if (exe->args[0] == 0)
		{
			end = ft_splito(tools->limiter, ' ');
			i = 0;
			while ((ar = get_next_line(0)))
			{
				if (ft_strcmp(ft_strjoin(end[i], "\n"), ar) == 0)
				{
					i++;
					if (end[i] == 0)
					{
						close(0);
						exit(1);
					}
				}
				else
					ft_putstr_fd(ar, tools->fd);
			}
		}
	}
}

void	exe_doc(char *buf, t_exec *exe, t_tool *tools)
{
	char	**end;
	char	*ar;
	int		i;

	i = 0;
	end = ft_splito(tools->limiter, ' ');
	while ((ar = get_next_line(0)))
	{
		if (ft_strcmp(ft_strjoin(end[i], "\n"), ar) == 0)
		{
			i++;
			if (end[i] == 0)
			{
				close(tools->fd);
				tools->fd = open("/tmp/ ", O_RDONLY, 0644);
				dup2(tools->fd, STDIN_FILENO);
				execve(buf, exe->args, tools->envp);
			}
		}
		else
			ft_putstr_fd(ar, tools->fd);
	}
}
