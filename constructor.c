/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:36:30 by sfarhan           #+#    #+#             */
/*   Updated: 2022/07/28 05:52:18 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*piping(t_cmd *left, t_cmd *right)
{
	t_pipe	*cmd;

	cmd = malloc(sizeof(t_pipe) + 1);
	cmd->type = PIPE;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}

t_cmd	*redirect(t_cmd	*exe, char *file, int mode, int fd, int token)
{
	t_redir	*cmd;

	cmd = malloc(sizeof(t_redir) + 1);
	cmd->type = REDIR;
	cmd->exe = exe;
	cmd->file = file;
	cmd->mode = mode;
	cmd->fd = fd;
	cmd->token = token;
	return ((t_cmd *)cmd);
}

t_cmd	*exelior(char *s)
{
	t_exec	*cmd;
	int		i;
	int		words;

	i = 0;
	words = 0;
	while (!exist(&s, "|<>") && *s)
	{
		s++;
		if (*s == ' ' || *s == '\0')
			words++;
	}
	//printf ("lwords dzeb = %d\n", words);
	cmd = malloc (sizeof(t_exec) + 1);
	cmd->args = malloc (sizeof(char *) * (words + 1));
	cmd->type = EXEC;
	while (i < words)
	{
		cmd->args[i] = 0;
		i++;
	}
	cmd->args[i] = 0;
	return ((t_cmd *)cmd);
}

int	ft_strchr(char s, char *scan)
{
	int	i;

	i = 0;
	while (scan[i] && scan[i] != s)
		i++;
	if (i == ft_strlen(scan))
		return (0);
	return (1);
}

int	ft_skip(char *s, char *skip)
{
	int	i;
	int	j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (skip[j])
		{
			if (skip[j] == s[i])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	exist(char **ps, char *token)
{
	char	*s;
	int		i;

	i = 0;
	s = *ps;
	while (s[i] != '\0' && s[i] == 2)
		s++;
	*ps = &s[i];
	//printf ("%c\n", s[i]);
	// if (s[i] == '|')
	// 	printf ("hna\n");
	return (s[i] && ft_strchr(s[i], token));
}
