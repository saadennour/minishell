/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 19:30:48 by sfarhan           #+#    #+#             */
/*   Updated: 2022/08/22 02:18:06 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	doc_nocmd(t_tool *tools)
{
	int		i;
	char	**end;
	char	*ar;

	i = 0;
	end = ft_splito(tools->limiter, ' ');
	while (1)
	{
		write(2, "> ", 2);
		ar = get_next_line(0);
		if (ft_strcmp(ft_strjoin(end[i], "\n"), ar) == 0)
		{
			i++;
			if (end[i] == 0)
			{
				free (ar);
				free_tab(end, 0);
				close(0);
				exit(1);
			}
		}
		else
			ft_putstr_fd(ar, tools->fd);
		free (ar);
	}
}

void	heredoc(t_redir *red, t_tool *tools)
{
	t_exec	*exe;

	red->file = ft_strjoin(red->file, " ");
	tools->fd = open("/tmp/ ", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (tools->fd < 0)
	{
		printf ("Error in opening file descriptor\n");
		exit(1);
	}
	dup2(tools->stdin_copy, 0);
	tools->limiter = ft_strjoin(red->file, tools->limiter);
	if (red->exe->type == EXEC)
	{
		exe = (t_exec *)red->exe;
		if (exe->args[0] == 0)
			doc_nocmd(tools);
	}
}

static void	exec_part(char *buf, t_exec *exe, t_tool *tools, t_list **data)
{
	close(tools->fd);
	tools->fd = open("/tmp/ ", O_RDONLY, 0644);
	dup2(tools->fd, STDIN_FILENO);
	buf = get_path(exe, data);
	if (buf == NULL)
		exit (127);
	execve(buf, exe->args, tools->envp);
}

void	exe_doc(char *buf, t_exec *exe, t_tool *tools, t_list **data)
{
	char	**end;
	char	*ar;
	int		i;

	i = 0;
	end = ft_splito(tools->limiter, ' ');
	while (1)
	{
		write(2, "> ", 2);
		ar = get_next_line(0);
		if (ft_strcmp(ft_strjoin(end[i], "\n"), ar) == 0)
		{
			i++;
			if (end[i] == 0)
			{
				free (ar);
				free_tab(end, 0);
				exec_part(buf, exe, tools, data);
			}
		}
		else
			ft_putstr_fd(ar, tools->fd);
		free (ar);
	}
}
