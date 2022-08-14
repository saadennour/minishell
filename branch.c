/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   branch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 17:02:59 by sfarhan           #+#    #+#             */
/*   Updated: 2022/08/13 15:23:56 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	right_pipe(t_pipe *pip, t_tool *tools, t_list **data, int *p)
{
	if (pip->left->type == REDIR)
		wait(0);
	dup2(p[0], STDIN_FILENO);
	close(p[0]);
	close(p[1]);
	run_cmd(pip->right, tools, data);
	if (pip->right->type == EXEC)
		exit (1);
}

void	type_pipe(t_cmd *cmd, t_tool *tools, t_list **data)
{
	int		p[2];
	t_pipe	*pip;

	pip = (t_pipe *)cmd;
	if (pipe(p) == -1)
	{
		printf ("An error occured in the pipe function\n");
		exit (1);
	}
	if (fork() == 0)
	{
		dup2(p[1], STDOUT_FILENO);
		close(p[0]);
		close(p[1]);
		run_cmd(pip->left, tools, data);
		if (pip->left->type == EXEC)
			exit (1);
	}
	else
		right_pipe(pip, tools, data, p);
	close(p[0]);
	close(p[1]);
	wait(0);
}

void	type_exec(t_cmd *cmd, t_tool *tools, t_list **data)
{
	t_exec	*exe;
	char	*buf;
	int		bult;

	exe = (t_exec *)cmd;
	if (exe->args[0] == 0)
		exit (0);
	signal(SIGQUIT, handle_s);
	bult = if_builtins(exe->args, data, &tools->path);
	if (bult)
	{
		if (bult == 2)
			exit(0);
		exit(bult);
	}
	buf = get_path(exe, data);
	if (tools->limiter != NULL)
		exe_doc(buf, exe, tools);
	execve(buf, exe->args, tools->envp);
}

static void	multi_red(t_redir *red, t_tool *tools)
{
	t_redir	*red2;

	if (tools->c != 1)
	{
		dup2(tools->fd, red->fd);
		if (red->exe->type == REDIR)
		{
			red2 = (t_redir *)red->exe;
			if (red->fd == red2->fd)
				(tools->c) = 1;
		}
	}
	if (red->exe->type == REDIR)
	{
		red2 = (t_redir *)red->exe;
		if (red->fd != red2->fd)
		(tools->c) = 0;
	}
}

void	type_redir(t_cmd *cmd, t_tool *tools, t_list **data)
{	
	t_redir	*red;

	red = (t_redir *)cmd;
	if (red->mode == 3)
		heredoc(red, tools);
	else
	{
		tools->fd = open(red->file, red->mode, 0644);
		if (tools->fd < 0)
		{
			printf ("Errooor\n");
			exit (1);
		}
		multi_red(red, tools);
	}
	run_cmd(red->exe, tools, data);
}
