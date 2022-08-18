/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 17:09:37 by sfarhan           #+#    #+#             */
/*   Updated: 2022/08/17 20:27:21 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	should_open(t_redir *red)
{
	t_redir	*red2;
	int		fd;

	while (red->exe)
	{
		if (red->exe->type == REDIR)
		{
			red2 = (t_redir *)red->exe;
			if (ft_strcmp(red->file, red2->file) == 0 && red2->fd == 1)
			{
				fd = open(red2->file, red2->mode, 0644);
				return (fd);
			}
			red = (t_redir *)red->exe;
		}
		else
			break ;
	}
	return (-1);
}

void	inside_quotes(char *str, int *i)
{
	if (str[(*i)] == 1)
	{
		(*i)++;
		while (str[(*i)] && !((str[(*i)] == 1 && str[(*i) + 1] == ' ')))
		{
			if (str[(*i)] == 1)
			{
				while (str[(*i)] && str[(*i)] != ' ')
					(*i)++;
				break ;
			}
			(*i)++;
		}
		if (str[(*i)])
			(*i)++;
	}
}
