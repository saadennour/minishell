/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:36:30 by sfarhan           #+#    #+#             */
/*   Updated: 2022/06/28 12:53:08 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*piping(t_cmd *left, t_cmd *right)
{
	t_pipe	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->type = PIPE;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd*)cmd);
}

t_cmd	*redirect(t_cmd	*exe, char *file, char *efile, int mode, int fd)
{
	t_redir	*cmd;
	
	cmd = malloc(sizeof(t_cmd));
	cmd->type = REDIR;
	cmd->exe = exe;
	cmd->file = file;
	cmd->efile = efile;
	cmd->mode = mode;
	cmd->fd = fd;
	return ((t_cmd*)cmd);
}

t_cmd	*exelior()
{
	t_exec	*cmd;
	cmd = malloc (sizeof(t_cmd));
	cmd->type = EXEC;
	return ((t_cmd*)cmd);
}

int	ft_strchr(char *s, char *skip)
{
	int	i; 

	i = 0;
	while (skip[i] && skip[i] != *s)
		i++;
	if (i == ft_strlen(skip))
		return (0);
	return (1);
}

int	exist(char **ps, char *es, char *token)
{
	char	*s;

	s = *ps;
	while (s < es && ft_strchr(s, " \t\n\v\f\r"))
		s++;
	*ps = s;
	return *s && ft_strchr(s, token);
}